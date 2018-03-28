#include"Enemy.h"
#include"Player.h"

Enemy::Enemy() :
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

}

void Enemy::update(const Player& player, const std::vector<std::shared_ptr<Object>>& obj) {
	//check_dir();
	move(player);
	attack(player);
	check_hit(player);
	check_dead();
}

void Enemy::check_dir() {
	if (c_hit == 0) {
		if (body.getVelocity().x > 0 && dir == -1) {
			dir = 1;
		}
		if (body.getVelocity().x < 0 && dir == 1) {
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


EnemyManager::EnemyManager() {

}

void EnemyManager::update(const Player& player, const std::vector<std::shared_ptr<Object>>& obj) {
	world.update();
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update(player, obj);
	}
	dead();
}

void EnemyManager::dead() {
	auto rmvIter = std::remove_if(enemies.begin(), enemies.end(), [](const std::shared_ptr<Enemy>& a) {
		return a->isDead;
	});
	enemies.erase(rmvIter, enemies.end());
}

void EnemyManager::draw() const {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->draw();
	}
}