#include"UseOperator.h"
#include"Player.h"
#include"GameSystem.h"

Enemy::Enemy(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	obj(_name, _pos, _rot, _scale, _alpha),
	hp(100),
	range(RectF((obj.pos - TextureAsset(obj.name).size / 2.0) / 100.0, TextureAsset(obj.name).size / 100.0)),
	pos(range._get_center()),
	velocity(0, 0),
	dir(-1),
	flag(),
	attackCount(0.0),
	hitCount(0.0) {

}

Enemy::Flag::Flag() :
	isDead(false),
	hit(false),
	attack(false),
	nearPlayer(false) {

}


void Enemy::use(PhysicsWorld& world) {
	obj.isUsing = true;
	init();
	range = RectF((obj.pos - TextureAsset(obj.name).size / 2.0) / 100.0, TextureAsset(obj.name).size / 100.0);
	body.reset(new PhysicsBody(world.createRect(range.pos, RectF(range.size), PhysicsMaterial(1.0, 0.0, 0.0), none, PhysicsBodyType::Dynamic)));
	body->setGravityScale(2.0);
	body->setFixedRotation(true);
}

void Enemy::disuse() {
	obj.isUsing = false;
	body.reset();
}

void Enemy::update(const Player& player, const std::vector<std::shared_ptr<Block>>& obj, const double time_speed) {

	reflectPhysics();
	checkDistance(player);
	checkHit(player, time_speed);
	attack(obj, time_speed);
	move(player, time_speed);
	checkDir(player);
	checkDead();
}

void Enemy::reflectPhysics() {
	range.pos = body->getPos();
	pos = range._get_center();
	velocity = body->getVelocity();
}

void Enemy::checkDistance(const Player& player) {
	if (pos.distanceFrom(player.pos) < 6) {
		flag.nearPlayer = true;
	}
	else {
		flag.nearPlayer = false;
	}
}

void Enemy::checkHit(const Player& player, const double time_speed) {
	if (flag.hit) {
		hitCount += time_speed;
		if (hitCount > 30) {
			hitCount = 0;
			flag.hit = false;
		}
	}
	for (auto pAttack : player.attacks) {
		if (range.intersects(pAttack->range)) {
			bool hitAttackContainPAttack = false;
			for (auto hitAttack : hitPlayerAttack) {
				if (pAttack == hitAttack.lock()) {
					hitAttackContainPAttack = true;
					break;
				}
			}
			if (!hitAttackContainPAttack) {
				flag.hit = true;
				hitCount = 0;
				hitPlayerAttack.emplace_back(pAttack);
				dir = -pAttack->DIR;
				hp -= pAttack->POWER;
			}
		}
	}

	auto rmvIter = std::remove_if(attacks.begin(), attacks.end(), [](const std::weak_ptr<Attack>& a) {
		return a.expired();
	});
	attacks.erase(rmvIter, attacks.end());

}

void Enemy::checkDir(const Player& player) {
	if (flag.nearPlayer && !flag.hit) {
		if (pos.x < player.pos.x - 1) {
			dir = 1;
		}
		else if (pos.x > player.pos.x + 1) {
			dir = -1;
		}
	}
}

void Enemy::checkDead() {
	if (range.pos.y > 1000) {
		flag.isDead = true;
	}
	if (hp <= 0) {
		flag.isDead = true;
	}
}

void Enemy::init() {

}



Tank::Tank(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Enemy(_name, _pos, _rot, _scale, _alpha) {

	TextureAsset::Register(L"tank_01", L"Data/enemy/pen_01.png");
	TextureAsset::Register(L"tank_02", L"Data/enemy/pen_02.png");
	TextureAsset::Register(L"tank_hit", L"Data/enemy/hit_pen.png");
}

void Tank::attack(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {
	if (flag.hit) {
		attackCount = 0;
		flag.attack = false;
	}
	else {
		if (flag.attack) {
			attackCount += time_speed;
			if (attackCount > 30) {
				attackCount = 0.0;
				flag.attack = false;
			}
		}
		else if(flag.nearPlayer) {
			attacks.emplace_back(std::make_shared<TankShoot>(pos + Vec2(dir*range.size.x / 2.0, -range.size.y / 5), dir));
			flag.attack = true;
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

void Tank::move(const Player& player, const double time_speed) {
	if (flag.hit) {
		if (hitCount == 0) {
			body->setVelocity(Vec2(-dir*3.0, -3.0));
		}
	}
	else {
		if (flag.nearPlayer) {
			body->setVelocity(Vec2(dir * 0.5, velocity.y));
		}
		else {
			body->setVelocity(Vec2(0.0, velocity.y));
		}
	}
}

void Tank::draw() const {

	if (GameSystem::get().debug) {
		range.draw(Palette::Darkviolet);

		Circle(pos, 0.1).draw(Palette::Orange);
		Triangle(pos + Vec2(0, -5) / 100.0, pos + Vec2(10 * dir, 0) / 100.0, pos + Vec2(0, 5) / 100.0).draw();


		Println(L"hp:", hp);

	}

	if (flag.nearPlayer) {
		if (dir == 1) {
			TextureAsset(L"tank_02").scale(range.size.y / (TextureAsset(L"tank_02").height - 15)).mirror().drawAt(pos);
		}
		else if (dir == -1) {
			TextureAsset(L"tank_02").scale(range.size.y / (TextureAsset(L"tank_02").height - 15)).drawAt(pos);
		}
	}
	else {
		if (dir == 1) {
			TextureAsset(L"tank_01").scale(range.size.y / (TextureAsset(L"tank_01").height - 15)).mirror().drawAt(pos);
		}
		else if (dir == -1) {
			TextureAsset(L"tank_01").scale(range.size.y / (TextureAsset(L"tank_01").height - 15)).drawAt(pos);
		}

	}
	for (auto elem : attacks) {
		elem->draw();
	}

	if (flag.hit) {
		static Vec2 effectPos;
		if (hitCount == 0) {
			effectPos = Vec2(Random<double>(-range.size.x / 4, range.size.x / 4), Random<double>(-range.size.y / 4, range.size.y / 4));
		}
		TextureAsset(L"tank_hit").scale(1.0 / TextureAsset(L"tank_hit").height).drawAt(pos + effectPos);

	}

}



Dog::Dog(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Enemy(_name, _pos, _rot, _scale, _alpha) {
	//body->setVelocity(Vec2(-1.0, 0));
}


void Dog::attack(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {
	if (flag.attack) {
		attackCount += time_speed;
		if (attackCount > 30) {
			attackCount = 0.0;
			flag.attack = false;
		}
	}
	else if (Random(60) == 0) {
		attacks.emplace_back(std::make_shared<DogSlash>(pos + Vec2(dir*range.size.x, 0), dir));
		flag.attack = true;
	}


	for (auto elem : attacks) {
		elem->update(obj, time_speed);
	}
	auto rmvIter = std::remove_if(attacks.begin(), attacks.end(), [](const std::shared_ptr<Attack>& a) {
		return a->isDead;
	});
	attacks.erase(rmvIter, attacks.end());
}

void Dog::move(const Player& player, const double time_speed) {
	//body->setPos(body->getPos() + Vec2(1.0, 0.0) / 100.0);
	//body->setVelocity(Vec2(-1, body->getVelocity().y));
}

void Dog::draw() const {
	if (GameSystem::get().debug) {
		//TextureAsset(obj.name).scale(obj.scale / 100.0).rotate(obj.rot).draw(obj.pos / 100.0 - TextureAsset(obj.name).size / 2.0 / 100.0, Color(255, 255, 255, obj.alpha));
		range.draw(Palette::Black);
		//body->draw(Palette::Gray);

		Circle(pos, 0.1).draw(Palette::Red);
		Triangle(pos + Vec2(0, -5) / 100.0, pos + Vec2(10 * dir, 0) / 100.0, pos + Vec2(0, 5) / 100.0).draw();

		for (auto elem : attacks) {
			elem->draw();
		}
	}
}




Drone::Drone(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Enemy(_name, _pos, _rot, _scale, _alpha) {

}

void Drone::attack(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {


	for (auto elem : attacks) {
		elem->update(obj, time_speed);
	}
	auto rmvIter = std::remove_if(attacks.begin(), attacks.end(), [](const std::shared_ptr<Attack>& a) {
		return a->isDead;
	});
	attacks.erase(rmvIter, attacks.end());

}

void Drone::move(const Player& player, const double time_speed) {

}

void Drone::draw() const {

	if (GameSystem::get().debug) {
		//TextureAsset(obj.name).scale(obj.scale / 100.0).rotate(obj.rot).draw(obj.pos / 100.0 - TextureAsset(obj.name).size / 2.0 / 100.0, Color(255, 255, 255, obj.alpha));
		range.draw(Palette::Darkgreen);
		//body->draw(Palette::Green);

		Circle(pos, 0.1).draw(Palette::Yellow);
		Triangle(pos + Vec2(0, -5) / 100.0, pos + Vec2(10 * dir, 0) / 100.0, pos + Vec2(0, 5) / 100.0).draw();


		for (auto elem : attacks) {
			elem->draw();
		}
	}
}




SampleEnemy::SampleEnemy(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Enemy(_name, _pos, _rot, _scale, _alpha) {

}

void SampleEnemy::draw() const {
	if (GameSystem::get().debug) {
		//TextureAsset(obj.name).scale(obj.scale / 100.0).rotate(obj.rot).draw(obj.pos / 100.0 - TextureAsset(obj.name).size / 2.0 / 100.0, Color(255, 255, 255, obj.alpha));
		body->draw(Palette::Gray);
	}
}

void SampleEnemy::attack(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {

}

void SampleEnemy::move(const Player& player, const double time_speed) {

}
