#include"Player.h"
#include"EnemyManager.h"
#include"GameSystem.h"

#include<cmath>

const Vec2 Player::PLAYER_SIZE = Vec2(64.0 / 100.0, 128.0 / 100.0);
const Vec2 Player::FOOT_SIZE_MAIN = Vec2(Player::PLAYER_SIZE.x, 8.0 / 100.0);
const Vec2 Player::SIDE_SIZE = Vec2(8.0 / 100.0, 8.0 / 100.0);
const double Player::MAX_SPEED_GROUND = 4.0;
const double Player::MAX_SPEED_AIR = MAX_SPEED_GROUND * 2.0 / 3.0;
const double Player::FORCE_AIR = 12.0;
const int Player::JUMP_LIMIT = 5;
const int Player::SLASH_LIMIT = 30;
const int Player::SLASH_COOLTIME = 15;



Player::Player(PhysicsWorld& world) :
	body(world.createRect(Vec2(0, 0), RectF(PLAYER_SIZE), PhysicsMaterial(1.0, 0.0, 0.02), none, PhysicsBodyType::Dynamic)),
	range(body),
	hp(100),
	dir(1),
	pos(range.body._get_center()),
	velocity(0,0),
	flag(),
	jumpCount(0),
	slashCount(0) {

	body.setGravityScale(2.0);
	body.setFixedRotation(true);

}

Player::Range::Range(PhysicsBody Pbody) :
	body(RectF(Pbody.getPos(), PLAYER_SIZE)),
	foot_main(RectF(Vec2(body._get_center().x, body.y + body.h), FOOT_SIZE_MAIN)),
	bottomRight(RectF(body.pos + Vec2(body.w, body.h - SIDE_SIZE.y), SIDE_SIZE)),
	bottomLeft(RectF(body.pos + Vec2(-SIDE_SIZE.x, body.h - SIDE_SIZE.y), SIDE_SIZE)),
	upperRight(RectF(body.pos + Vec2(body.w, 0.0), SIDE_SIZE)),
	upperLeft(RectF(body.pos + Vec2(-SIDE_SIZE.x, 0.0), SIDE_SIZE)) {

}

Player::Flag::Flag() :
	onGround(false),
	onWall(false),
	//grab(false),
	jump(false),
	slash(false),
	slashStage(0) {

}

void Player::update(const EnemyManager& enemymanager, const std::vector<std::shared_ptr<Block>>& obj, double& time_speed) {
	timeControl(time_speed);
	reflectPhysics();
	//grab(obj, time_speed);//つかまり
	slash(time_speed);
	move(obj, time_speed);
	checkDir();
}

void Player::timeControl(double& time_speed) {
	time_speed = 1.0 - GameSystem::get().input.triggerL * 0.8;
}

//void Player::grab(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed) {
//	static Vec2 cliff;
//
//	flag.grab = false;
//	body.setGravityScale(2);
//	for (auto elem : obj) {
//		if (range.upperLeft.intersects(cliff = elem->range._get_tr() + Vec2(1,0))) {
//			flag.grab = true;
//			dir = -1;
//			break;
//		}
//		else if (range.upperRight.intersects(cliff = elem->range._get_tl())) {
//			flag.grab = true;
//			dir = 1;
//			break;
//		}
//	}
//
//	if (flag.grab) {
//		body.setGravityScale(0);
//		if (dir == -1) {
//			body.setPos(cliff);
//		}
//		else if (dir == 1) {
//			body.setPos(cliff + Vec2(-range.body.w, 0.0));
//		}
//	}
//}

void Player::slash(const double& time_speed) {
	if (flag.slash) {
		slashCount += time_speed;
		if (slashCount > SLASH_LIMIT) {
			slashCount = 0;
			flag.slash = false;
			flag.slashStage = 0;
		}
	}
	else {
		if (GameSystem::get().input.slash.get_clicked()) {
			addSlash();
			flag.slash = true;
		}
	}
	if (GameSystem::get().input.slash.get_clicked() && slashCount > SLASH_COOLTIME) {
		addSlash();
	}

	for (auto elem : attacks) {
		elem->update(time_speed);
	}
	auto rmvIter = std::remove_if(attacks.begin(), attacks.end(), [](const std::shared_ptr<Attack>& a) {
		return a->isDead;
	});
	attacks.erase(rmvIter, attacks.end());
}

void Player::addSlash() {
	switch (flag.slashStage) {
	case 0:
		attacks.emplace_back(std::make_shared<Slash1>(pos + Vec2(dir*PLAYER_SIZE.x, 0), dir));
		flag.slashStage++;
		break;
	case 1:
		attacks.emplace_back(std::make_shared<Slash2>(pos + Vec2(dir*PLAYER_SIZE.x, 0), dir));
		slashCount = 0;
		flag.slashStage++;
		break;
	case 2:
		attacks.emplace_back(std::make_shared<Slash3>(pos + Vec2(dir*PLAYER_SIZE.x, 0), dir));
		slashCount = 0;
		flag.slashStage++;
		break;
	}
}

void Player::reflectPhysics() {
	//rangeとかbodyのpos(getPos)は長方形の左上
	range.body.pos = body.getPos();
	//こいつだけ中心座標
	pos = range.body._get_center();

	velocity = body.getVelocity();

	range.foot_main.setCenter(pos.x, range.body.y + range.body.h + range.foot_main.h / 2.0);
	range.bottomRight.setPos(range.body.pos + Vec2(range.body.w, range.body.h - SIDE_SIZE.y));
	range.bottomLeft.setPos(range.body.pos + Vec2(-SIDE_SIZE.x, range.body.h - SIDE_SIZE.y));
	range.upperRight.setPos(range.body.pos + Vec2(range.body.w, 0.0));
	range.upperLeft.setPos(range.body.pos + Vec2(-SIDE_SIZE.x, 0.0));

}

void Player::move(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {
	
	if (flag.slash) {
		//今は止まるだけだが、前に進むようにする
		body.setVelocity(Vec2(0.0, 0.0));
		body.setGravityScale(0.0);
		
	}
	else {
		body.setGravityScale(2);
		checkTouch(obj);

		//*現在、崖から降りるときに飛び出さざるを得ない状態
		if (flag.onGround) {
			body.setVelocity(Vec2(MAX_SPEED_GROUND * GameSystem::get().input.stick.L.x, velocity.y));
		}
		else {
			if (velocity.x > -MAX_SPEED_AIR && velocity.x < MAX_SPEED_AIR) {
				body.applyForce(Vec2(FORCE_AIR * GameSystem::get().input.stick.L.x, 0));
				if (body.getVelocity().x < -MAX_SPEED_AIR) {
					body.setVelocity(Vec2(-MAX_SPEED_AIR, velocity.y));
				}
				else if (body.getVelocity().x > MAX_SPEED_AIR) {
					body.setVelocity(Vec2(MAX_SPEED_AIR, velocity.y));
				}
			}
			else {
				if (velocity.x > 0 && GameSystem::get().input.stick.L.x < 0) {
					body.applyForce(Vec2(FORCE_AIR * GameSystem::get().input.stick.L.x, 0));
				}
				if (velocity.x < 0 && GameSystem::get().input.stick.L.x > 0) {
					body.applyForce(Vec2(FORCE_AIR * GameSystem::get().input.stick.L.x, 0));
				}
			}
		}
		jump(obj, time_speed);
	}
}

void Player::checkTouch(const std::vector<std::shared_ptr<Block>>& obj) {

	flag.onGround = false;
	flag.onWall = false;

	for (auto elem : obj) {
		//地面への接地判定を優先
		if (range.foot_main.intersects(elem->range)) {
			flag.onGround = true;
			break;
		}
		else if (range.bottomLeft.intersects(elem->range) || range.bottomRight.intersects(elem->range)) {
			flag.onWall = true;
			break;
		}
	}
}

void Player::jump(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {

	//if (flag.grab) {
	//	flag.jump = false;
	//}
	if (flag.onGround/* || flag.grab*/) {
		if (GameSystem::get().input.jump.get_clicked()) {
			body.setVelocity(Vec2(velocity.x, -5.0));
			flag.jump = true;
			jumpCount = 0;
		}
	}
	else {
		for (auto elem : obj){
			if (range.bottomLeft.intersects(elem->range)) {
				if (GameSystem::get().input.jump.get_clicked()) {
					body.setVelocity(Vec2(5.0, -5.0));
					flag.jump = true;
					jumpCount = 0;
				}
			}
			else if (range.bottomRight.intersects(elem->range)) {
				if (GameSystem::get().input.jump.get_clicked()) {
					body.setVelocity(Vec2(-5.0, -5.0));
					flag.jump = true;
					jumpCount = 0;
				}
			}
		}
	}
	if (flag.jump) {
		if ((jumpCount < JUMP_LIMIT) && GameSystem::get().input.jump.get_pressed()) {
			if ((jumpCount > 3)) {
				body.applyForce(Vec2(0.0, -200.0));
			}
			jumpCount += time_speed;
		}
		else {
			flag.jump = false;
			jumpCount = 0;
		}
	}

}

void Player::checkDir() {
	if (velocity.x > 0.1 && dir == -1) {
		dir = 1;
	}
	else if (velocity.x < -0.1 && dir == 1) {
		dir = -1;
	}
}

void Player::draw() const {

	if (GameSystem::get().debug) {
		range.body.draw();
		Circle(pos, 0.05).draw(Palette::Red);
		range.bottomRight.draw(Palette::Yellow);
		range.bottomLeft.draw(Palette::Yellow);
		range.upperRight.draw(Palette::Yellow);
		range.upperLeft.draw(Palette::Yellow);
		range.foot_main.draw(Palette::Orange);
		Print(L"player.pos:");
		Println(pos);
		Print(L"player.dir:");
		Println(dir);
		//Print(L"player.flag.grab:");
		//Println(flag.grab);
		//Print(L"player.velocity:");
		//Println(velocity);
		//Print(L"player.body.getVelocity():");
		//Println(body.getVelocity());
		//Print(L"player.body.getGravityScale():");
		//Println(body.getGravityScale());
		Print(L"slashCount:");
		Println(slashCount);
		Print(L"flag.slashStage:");
		Println(flag.slashStage);
		Print(L"flag.slash:");
		Println(flag.slash);

		for (auto elem : attacks) {
			elem->draw();
		}
	}
}