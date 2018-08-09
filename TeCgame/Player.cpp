#include"Player.h"
#include"EnemyManager.h"
#include"GameSystem.h"
#include"BlockManager.h"

#include<cmath>

const Vec2 Player::PLAYER_SIZE = Vec2(64.0 / 100.0, 128.0 / 100.0);
const Vec2 Player::FOOT_SIZE_MAIN = Vec2(Player::PLAYER_SIZE.x, 8.0 / 100.0);
const Vec2 Player::SIDE_SIZE = Vec2(8.0 / 100.0, 8.0 / 100.0);
const double Player::MAX_SPEED_GROUND = 4.0;
const double Player::MAX_SPEED_AIR = MAX_SPEED_GROUND * 2.0 / 3.0;
const double Player::FORCE_AIR = 12.0;
const double Player::FORCE_JUMP = -4.0;
const int Player::JUMP_LIMIT = 5;
const int Player::SLASH_LIMIT = 30;
const int Player::SLASH_COOLTIME = 15;
const int Player::SHOOT_COOLTIME = 15;



Player::Player(PhysicsWorld& world) :
	body(world.createRect(Vec2(0, 0), RectF(PLAYER_SIZE), PhysicsMaterial(1.0, 0.0, 0.02), none, PhysicsBodyType::Dynamic)),
	range(body),
	hp(100),
	dir(1),
	pos(range.body._get_center()),
	velocity(0, 0),
	flag(),
	jumpCount(0.0),
	slashCount(0.0),
	shootCount(0.0),
	hitCount(0.0) {

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
	onRightWall(false),
	inRising(false),
	notDoubleJumpYet(true),
	notSlashInAirYet(true),
	slash(false),
	shoot(false),
	hit(false),
	slashPhase(0) {

}

void Player::update(/*const EnemyManager& enemymanager*/const std::vector<std::shared_ptr<Enemy>>& enemys, const std::vector<std::shared_ptr<Block>>& obj, double& time_speed) {
	timeControl(time_speed);
	reflectPhysics();
	checkHit(/*enemymanager*/enemys, time_speed);
	attack(obj, time_speed);
	move(obj, time_speed);
	checkDir();
}

void Player::timeControl(double& time_speed) {

	static const double easeRate = 0.9;
	static double time_speed_ease;
	time_speed_ease = 1.0 - GameSystem::get().input.triggerL * 0.8;

	//time_speed = 1.0 - GameSystem::get().input.triggerL * 0.8;
	time_speed = easeRate*time_speed + (1 - easeRate)*time_speed_ease;
	if (time_speed > 0.999) {
		time_speed = 1.0;
	}
	else if (time_speed < 0.201) {
		time_speed = 0.2;
	}
}

void Player::reflectPhysics() {
	//range‚Æ‚©body‚Ìpos(getPos)‚Í’·•ûŒ`‚Ì¶ã
	range.body.pos = body.getPos();
	//‚±‚¢‚Â‚¾‚¯’†SÀ•W
	pos = range.body._get_center();

	velocity = body.getVelocity();

	range.foot_main.setCenter(pos.x, range.body.y + range.body.h + range.foot_main.h / 2.0);
	range.bottomRight.setPos(range.body.pos + Vec2(range.body.w, range.body.h - SIDE_SIZE.y));
	range.bottomLeft.setPos(range.body.pos + Vec2(-SIDE_SIZE.x, range.body.h - SIDE_SIZE.y));
	range.upperRight.setPos(range.body.pos + Vec2(range.body.w, 0.0));
	range.upperLeft.setPos(range.body.pos + Vec2(-SIDE_SIZE.x, 0.0));

}

void Player::checkHit(/*const EnemyManager& enemymanager*/const std::vector<std::shared_ptr<Enemy>>& enemys, const double& time_speed) {
	if (flag.hit) {
		hitCount += time_speed;
		if (hitCount > 15) {
			hitCount = 0;
			flag.hit = false;
		}
	}
	for (auto enemy : enemys) {
		for (auto eAttack : enemy->attacks) {
			if (range.body.intersects(eAttack->range)) {
				bool hitAttackContainEAttack = false;
				for (auto hitAttack : hitEnemyAttack) {
					if (eAttack == hitAttack.lock()) {
						hitAttackContainEAttack = true;
						break;
					}
				}
				if (!hitAttackContainEAttack) {
					flag.hit = true;
					hitCount = 0;
					hitEnemyAttack.emplace_back(eAttack);
					dir = -eAttack->DIR;
					hp -= eAttack->POWER;
				}
			}
		}
	}

	auto rmvIter = std::remove_if(attacks.begin(), attacks.end(), [](const std::weak_ptr<Attack>& a) {
		return a.expired();
	});
	attacks.erase(rmvIter, attacks.end());


}

void Player::attack(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {
	if (flag.hit) {
		slashCount = 0;
		flag.slash = false;
		flag.slashPhase = 0;
	}
	else {
		slash(time_speed);
		if (!flag.slash) {
			shoot(time_speed);
		}
	}
	for (auto elem : attacks) {
		elem->update(obj, time_speed);
	}
	auto rmvIter = std::remove_if(attacks.begin(), attacks.end(), [](const std::shared_ptr<Attack>& a) {
		return a->isDead;
	});
	attacks.erase(rmvIter, attacks.end());

}

void Player::slash(const double& time_speed) {
	if (flag.slash) {
		slashCount += time_speed;
		if (slashCount > SLASH_LIMIT) {
			slashCount = 0;
			flag.slash = false;
			flag.slashPhase = 0;
		}
		if (GameSystem::get().input.slash.get_clicked() && slashCount > SLASH_COOLTIME && flag.slashPhase < 3) {
			addSlash();
		}
	}
	else if (GameSystem::get().input.slash.get_clicked()) {
		if (flag.onGround) {
			addSlash();
			flag.slash = true;
		}
		else if (flag.notSlashInAirYet) {
			addSlash();
			flag.slash = true;
			flag.notSlashInAirYet = false;
		}
	}
	if (flag.onGround) {
		flag.notSlashInAirYet = true;
	}
}

void Player::addSlash() {
	switch (flag.slashPhase) {
	case 0:
		attacks.emplace_back(std::make_shared<Slash1>(pos + Vec2(dir*(PLAYER_SIZE.x * 1.5), 0), dir));
		break;
	case 1:
		attacks.emplace_back(std::make_shared<Slash2>(pos + Vec2(dir*(PLAYER_SIZE.x * 1.5), 0), dir));
		break;
	case 2:
		attacks.emplace_back(std::make_shared<Slash3>(pos + Vec2(dir*(PLAYER_SIZE.x * 1.5), 0), dir));
		break;
	}
	slashCount = 0;
	flag.slashPhase++;
}

void Player::shoot(const double& time_speed) {
	if (flag.shoot) {
		shootCount += time_speed;
		if (shootCount > SHOOT_COOLTIME) {
			shootCount = 0;
			flag.shoot = false;
		}
	}
	else if (GameSystem::get().input.shoot.get_clicked()) {
		attacks.emplace_back(std::make_shared<Shoot>(pos + Vec2(dir*PLAYER_SIZE.x, 0.0), dir));
		flag.shoot = true;
	}
}

void Player::move(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {

	if (flag.hit) {
		if (hitCount == 0) {
			body.setVelocity(Vec2(-dir*5.0, -5.0));
		}

		body.setGravityScale(2.0);
	}
	else {
		if (flag.slash) {
			body.setVelocity(Vec2(0.0, 0.0));
			if (slashCount == 0) {
				body.setVelocity(Vec2(dir*30.0, 0.0));
			}
			body.setGravityScale(0.0);

		}
		else {
			body.setGravityScale(2.0);
			checkTouch(obj);

			//*Œ»ÝAŠR‚©‚ç~‚è‚é‚Æ‚«‚É”ò‚Ño‚³‚´‚é‚ð“¾‚È‚¢ó‘Ô
			if (flag.onGround) {
				if (abs(GameSystem::get().input.stick.L.x) > 0.1) {
					body.setVelocity(Vec2(MAX_SPEED_GROUND * GameSystem::get().input.stick.L.x, velocity.y));
				}
				else {
					body.setVelocity(Vec2(0.0, velocity.y));
				}
			}
			else {
				if (velocity.x > -MAX_SPEED_AIR && velocity.x < MAX_SPEED_AIR) {
					if (abs(GameSystem::get().input.stick.L.x) > 0.1) {
						body.applyForce(Vec2(FORCE_AIR * GameSystem::get().input.stick.L.x, 0));
						if (body.getVelocity().x < -MAX_SPEED_AIR) {
							body.setVelocity(Vec2(-MAX_SPEED_AIR, velocity.y));
						}
						else if (body.getVelocity().x > MAX_SPEED_AIR) {
							body.setVelocity(Vec2(MAX_SPEED_AIR, velocity.y));
						}
					}
					else {
						body.applyForce(Vec2(0, 0)); //‚±‚ê‚ª–³‚¢‚Æ‰½ŒÌ‚©slash‚Ì‚ ‚Æ–³‘€ì‚Ì‚Æ‚«‹ó’†‚ÅŽ~‚Ü‚é
					}
				}
				else {
					if (velocity.x > 0 && GameSystem::get().input.stick.L.x < -0.1) {
						body.applyForce(Vec2(FORCE_AIR * GameSystem::get().input.stick.L.x, 0));
					}
					if (velocity.x < 0 && GameSystem::get().input.stick.L.x > 0.1) {
						body.applyForce(Vec2(FORCE_AIR * GameSystem::get().input.stick.L.x, 0));
					}
				}
			}
			jump(obj, time_speed);
		}
	}
}

void Player::checkTouch(const std::vector<std::shared_ptr<Block>>& obj) {

	flag.onGround = false;
	flag.onRightWall = false;
	flag.onLeftWall = false;

	for (auto elem : obj) {
		//’n–Ê‚Ö‚ÌÚ’n”»’è‚ð—Dæ
		if (range.foot_main.intersects(elem->range)) {
			flag.onGround = true;
			break;
		}
		else if (range.bottomLeft.intersects(elem->range)) {
			flag.onRightWall = true;
			break;
		}
		else if (range.bottomRight.intersects(elem->range)) {
			flag.onLeftWall = true;
			break;
		}
	}
}

void Player::jump(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {

	if (flag.onGround) {
		if (GameSystem::get().input.jump.get_clicked()) {
			body.setVelocity(Vec2(velocity.x, FORCE_JUMP));
			flag.inRising = true;
			jumpCount = 0;
		}
		flag.notDoubleJumpYet = true;
	}
	else if (GameSystem::get().input.jump.get_clicked()) {
		if (flag.onRightWall) {
			body.setVelocity(Vec2(5.0, FORCE_JUMP));
			flag.inRising = true;
			flag.notDoubleJumpYet = false;
			jumpCount = 0;

		}
		else if (flag.onLeftWall) {
			body.setVelocity(Vec2(-5.0, FORCE_JUMP));
			flag.inRising = true;
			flag.notDoubleJumpYet = false;
			jumpCount = 0;
		}
		else if (flag.notDoubleJumpYet) {
			body.setVelocity(Vec2(velocity.x, FORCE_JUMP));
			flag.inRising = true;
			flag.notDoubleJumpYet = false;
			jumpCount = 0;
		}
	}
	if (flag.inRising) {
		if ((jumpCount < JUMP_LIMIT) && GameSystem::get().input.jump.get_pressed()) {

			if (jumpCount > 3) {
				body.applyForce(Vec2(0.0, -150.0) / time_speed);
				flag.inRising = false;
				jumpCount = 0;
			}
			jumpCount += time_speed;

		}
		else {
			flag.inRising = false;
			jumpCount = 0;
		}
	}

}

void Player::checkDir() {
	if (!flag.hit) {
		if (GameSystem::get().input.stick.L.x > 0.1 && dir == -1) {
			dir = 1;
		}
		else if (GameSystem::get().input.stick.L.x < -0.1 && dir == 1) {
			dir = -1;
		}
	}
}

void Player::draw() const {

	if (GameSystem::get().debug) {
		range.body.draw();
		Circle(pos, 0.05).draw(Palette::Red);
		Triangle(pos + Vec2((range.body.size.x + 5)*dir, -5) / 100.0, pos + Vec2((range.body.size.x + 10)*dir, 0) / 100.0, pos + Vec2((range.body.size.x + 5)*dir, 5) / 100.0).draw(Palette::Red);
		//range.bottomRight.draw(Palette::Yellow);
		//range.bottomLeft.draw(Palette::Yellow);
		//range.upperRight.draw(Palette::Yellow);
		//range.upperLeft.draw(Palette::Yellow);
		//range.foot_main.draw(Palette::Orange);
		Println(L"player.hp:", hp);


		for (auto elem : attacks) {
			elem->draw();
		}
	}
}