#include"Enemy.h"
#include"Player.h"
#include "UseOperator.h"

Enemy::Enemy(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	obj(_name, _pos, _rot, _scale, _alpha),
	hp(100),
	range(RectF((obj.pos - TextureAsset(obj.name).size / 2.0) / 100.0, TextureAsset(obj.name).size / 100.0)),
	pos(range._get_center()),
	atc_c(0),
	dir(1),
	flag(),
	c_move(0),
	c_hit(0),
	atc_damage(0),
	hit_damage(0),
	attackCount(0.0) {
	//range = RectF((obj.pos - TextureAsset(obj.name).size / 2.0) / 100.0, TextureAsset(obj.name).size / 100.0);
}

Enemy::Flag::Flag() :
	isDead(false),
	hit(false),
	attack(false) {

}
	

void Enemy::use(PhysicsWorld& world) {
	obj.isUsing = true;
	init();
	range = RectF((obj.pos - TextureAsset(obj.name).size / 2.0) / 100.0, TextureAsset(obj.name).size / 100.0);
	body.reset(new PhysicsBody(world.createRect(Vec2(0, 0), range, PhysicsMaterial(1.0, 0.0, 0.0), none, PhysicsBodyType::Dynamic)));
	body->setGravityScale(2.0);
	body->setFixedRotation(true);
}

void Enemy::disuse() {
	obj.isUsing = false;
	body.reset();
}

void Enemy::update(const Player& player, const std::vector<std::shared_ptr<Block>>& obj, const double time_speed) {
	check_dir();
	attack(time_speed);
	check_hit(player);
	move(player, time_speed);
	check_dead();
}

void Enemy::check_dir() {
	if (c_hit == 0) {
		if (body->getVelocity().x > 0 && dir == -1) {
			dir = 1;
		}
		else if (body->getVelocity().x < 0 && dir == 1) {
			dir = -1;
		}
	}
}

void Enemy::check_dead() {
	if (range.pos.y > 1000) {
		flag.isDead = true;
	}
	if (hp <= 0) {
		flag.isDead = true;
	}
}

void Enemy::init() {

}

SampleEnemy::SampleEnemy(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Enemy(_name, _pos, _rot, _scale, _alpha) {

}

void SampleEnemy::draw() const {
	//TextureAsset(obj.name).scale(obj.scale / 100.0).rotate(obj.rot).draw(obj.pos / 100.0 - TextureAsset(obj.name).size / 2.0 / 100.0, Color(255, 255, 255, obj.alpha));
	body->draw(Palette::Gray);
}

void SampleEnemy::attack(const double time_speed) {

}

void SampleEnemy::move(const Player& player, const double time_speed) {

}

void SampleEnemy::check_hit(const Player& player) {

}




Dog::Dog(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Enemy(_name, _pos, _rot, _scale, _alpha) {
	//body->setVelocity(Vec2(-1.0, 0));
}

void Dog::draw() const {
	//TextureAsset(obj.name).scale(obj.scale / 100.0).rotate(obj.rot).draw(obj.pos / 100.0 - TextureAsset(obj.name).size / 2.0 / 100.0, Color(255, 255, 255, obj.alpha));
	body->draw(Palette::Black);
}

void Dog::attack(const double time_speed) {
	if (flag.attack) {
		attackCount += time_speed;
		if (attackCount > 30) {
			attackCount = 0.0;
			flag.attack = false;
		}
	}
	else/* if (Random(60) == 0)*/ {
		attacks.emplace_back(std::make_shared<DogSlash>(pos + Vec2(dir*range.size.x, 0), dir));
		flag.attack = true;
	}
}

void Dog::move(const Player& player, const double time_speed) {

}

void Dog::check_hit(const Player& player) {

}



Drone::Drone(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Enemy(_name, _pos, _rot, _scale, _alpha) {

}

void Drone::draw() const {
	//TextureAsset(obj.name).scale(obj.scale / 100.0).rotate(obj.rot).draw(obj.pos / 100.0 - TextureAsset(obj.name).size / 2.0 / 100.0, Color(255, 255, 255, obj.alpha));
	body->draw(Palette::Green);
}

void Drone::attack(const double time_speed) {

}

void Drone::move(const Player& player, const double time_speed) {

}

void Drone::check_hit(const Player& player) {

}



Tank::Tank(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Enemy(_name, _pos, _rot, _scale, _alpha) {

}

void Tank::draw() const {
	//TextureAsset(obj.name).scale(obj.scale / 100.0).rotate(obj.rot).draw(obj.pos / 100.0 - TextureAsset(obj.name).size / 2.0 / 100.0, Color(255, 255, 255, obj.alpha));
	body->draw(Palette::Violet);
}

void Tank::attack(const double time_speed) {

}

void Tank::move(const Player& player, const double time_speed) {

}

void Tank::check_hit(const Player& player) {

}