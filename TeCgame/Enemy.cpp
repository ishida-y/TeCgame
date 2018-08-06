#include"Enemy.h"
#include"Player.h"
#include "UseOperator.h"

Enemy::Enemy(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	obj(_name, _pos, _rot, _scale, _alpha),
	hp(100),
	atc_range(RectF(0, 0, 0, 0)),
	atc_c(0),
	dir(1),
	isDead(false),
	disPlayer(false),
	hit(false),
	c_move(0),
	c_hit(0),
	atc_damage(0),
	hit_damage(0) {
	range = RectF((obj.pos - TextureAsset(obj.name).size / 2.0) / 100.0, TextureAsset(obj.name).size / 100.0);
}


void Enemy::use(PhysicsWorld& world) {
	obj.isUsing = true;
	range = RectF((obj.pos - TextureAsset(obj.name).size / 2.0) / 100.0, TextureAsset(obj.name).size / 100.0);
	body.reset(new PhysicsBody(world.createRect(Vec2(0, 0), range, PhysicsMaterial(1.0, 0.0, 0.0), none, PhysicsBodyType::Dynamic)));
	body->setGravityScale(2.0);
	body->setFixedRotation(true);
}

void Enemy::disuse() {
	obj.isUsing = false;
	body.reset();
}

void Enemy::update(const Player& player, const std::vector<std::shared_ptr<Block>>& obj) {
	check_dir();
	move(player);
	slash(player);
	check_hit(player);
	check_dead();
}

void Enemy::check_dir() {
	if (c_hit == 0) {
		if (body->getVelocity().x > 0 && dir == -1) {
			dir = 1;
		}
		if (body->getVelocity().x < 0 && dir == 1) {
			dir = -1;
		}
	}
}

void Enemy::check_dead() {
	if (range.pos.y > 1000) {
		isDead = true;
	}
	if (hp <= 0) {
		isDead = true;
	}
}


SampleEnemy::SampleEnemy(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	Enemy(_name, _pos, _rot, _scale, _alpha) {

}

void SampleEnemy::draw() const {
	//TextureAsset(obj.name).scale(obj.scale / 100.0).rotate(obj.rot).draw(obj.pos / 100.0 - TextureAsset(obj.name).size / 2.0 / 100.0, Color(255, 255, 255, obj.alpha));
	body->draw(Palette::Gray);
}

void SampleEnemy::move(const Player& player){

}

void SampleEnemy::slash(const Player& player){

}

void SampleEnemy::check_hit(const Player& player){

}