#include"Player.h"
#include"Enemy.h"
#include"GameSystem.h"

const Vec2 Player::PLAYER_SIZE = Vec2(64.0 / 100.0, 128.0 / 100.0);
const Vec2 Player::FOOT_SIZE = Vec2(64.0 / 100.0, 8.0 / 100.0);
const int Player::JUMP_LIMIT = 5;
const int Player::SLASH_LIMIT = 20;


Player::Player(PhysicsWorld& world) :
	body(world.createRect(Vec2(0, 0), RectF(PLAYER_SIZE), PhysicsMaterial(1.0, 0.0, 0.02), none, PhysicsBodyType::Dynamic)),
	range(RectF(body.getPos(), PLAYER_SIZE)),
	hp(100),
	dir(1),
	pos(range._get_center()),
	foot_range(RectF(Vec2(pos.x, range.y + range.h), FOOT_SIZE)),
	flag(),
	jumpCount(0) {

	body.setGravityScale(2.0);
	body.setFixedRotation(true);

}

Player::Flag::Flag() :
	jump(false),
	attack(false) {

}

void Player::update(const EnemyManager& enemymanager, const std::vector<std::shared_ptr<Object>>& obj, double& time_speed) {
	
	time_control(time_speed);
	move(obj, time_speed);
	attack();

	//body.setVelocity(Vec2(4.0 * GameSystem::get().input.stick.L.x, body.getVelocity().y));
	//
	//for (auto elem : obj) {
	//	if (foot_range.intersects(elem->range)) {
	//		if (GameSystem::get().input.jump.clicked) {
	//			body.applyForce(Vec2(0.0, -250.0) / time_speed);
	//			jumpFlag = true;
	//		}
	//	}
	//}
	//
	//if (jumpFlag) {
	//	if ((jumpCount < JUMP_LIMIT) && GameSystem::get().input.jump.pressed) {
	//		if ((jumpCount > 0) && (jumpCount % 2 == 0)) {
	//			body.applyForce(Vec2(0.0, -150.0) / time_speed);
	//		}
	//		jumpCount++;
	//	}
	//	else {
	//		jumpFlag = false;
	//		jumpCount = 0;
	//	}
	//}
	//if (body.getVelocity().x > 0 && dir == -1) {
	//	dir = 1;
	//}
	//if (body.getVelocity().x < 0 && dir == 1) {
	//	dir = -1;
	//}
	////rangeとかbodyのpos(getPos)は長方形の左上
	//range.pos = body.getPos();
	////こいつだけ中心座標
	//pos = range._get_center();//range.pos + Vec2(range.w / 2.0, range.h / 2.0);
	//
	//foot_range.setCenter(pos.x, range.y + range.h + foot_range.h / 2.0);


	
}

void Player::time_control(double& time_speed) {
	time_speed = 1.0 - GameSystem::get().input.triggerL * 0.8;
}

void Player::attack() {
	if (!flag.attack) {
		if (GameSystem::get().input.slash.get_clicked()) {
			attacks.emplace_back(std::make_shared<Slash>(pos + Vec2(dir*32.0 / 100.0, 0)));
		}
	}
	

	//attackManager.update();
	for (auto elem : attacks) {
		elem->update();
	}
	auto rmvIter = std::remove_if(attacks.begin(), attacks.end(), [](const std::shared_ptr<Attack>& a) {
		return a->isDead;
	});
	attacks.erase(rmvIter, attacks.end());


}

void Player::move(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed) {
	body.setVelocity(Vec2(4.0 * GameSystem::get().input.stick.L.x, body.getVelocity().y));

	for (auto elem : obj) {
		if (foot_range.intersects(elem->range)) {
			if (GameSystem::get().input.jump.get_clicked()) {
				body.applyForce(Vec2(0.0, -250.0) / time_speed);
				flag.jump = true;
				
			}
			break;
		}
	}
	if (flag.jump) {
		if ((jumpCount < JUMP_LIMIT) && GameSystem::get().input.jump.get_pressed()) {
			if ((jumpCount > 0) && (jumpCount % 2 == 0)) {
				body.applyForce(Vec2(0.0, -150.0) / time_speed);
				//body.setVelocity(Vec2(body.getVelocity().x, -5.0) / time_speed);
			}
			jumpCount++;
		}
		else {
			flag.jump = false;
			jumpCount = 0;
		}
	}

	if (body.getVelocity().x > 0 && dir == -1) {
		dir = 1;
	}
	if (body.getVelocity().x < 0 && dir == 1) {
		dir = -1;
	}
	//rangeとかbodyのpos(getPos)は長方形の左上
	range.pos = body.getPos();
	//こいつだけ中心座標
	pos = range._get_center();//range.pos + Vec2(range.w / 2.0, range.h / 2.0);

	foot_range.setCenter(pos.x, range.y + range.h + foot_range.h / 2.0);
}

void Player::draw() const {
	range.draw();
	Circle(pos, 0.05).draw(Palette::Red);
	foot_range.draw(Palette::Orange);

	for (auto elem : attacks) {
		elem->draw();
	}
}