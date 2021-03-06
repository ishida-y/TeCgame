#include "UseOperator.h"
#include"GameSystem.h"

UseOperator::UseOperator() {

}

void UseOperator::draw() {
	for (auto i : useBlocks) {
		i->draw();
	}
	for (int i = 0; i < useEnemies.size(); i++) {
		useEnemies[i]->draw();
	}
}

void UseOperator::addUsingBlock(std::shared_ptr<Block> obj, PhysicsWorld& Pworld, PhysicsWorld& Eworld) {
	useBlocks.emplace_back(obj);
	obj->use(Pworld, Eworld);
}

void UseOperator::addUsingEnemy(std::shared_ptr<Enemy> obj, PhysicsWorld &world) {
	useEnemies.emplace_back(obj);
	obj->use(world);
}

void UseOperator::checkUsing(Vec2 player) {
	for (auto i : useBlocks) {
		if (0) {//もしプレイヤーと遠かったら
			i->disuse();
		}
	}
	auto rmvIterB = std::remove_if(useBlocks.begin(), useBlocks.end(), [](const std::shared_ptr<Block>& a) {
		return !a->obj.isUsing;
	});
	useBlocks.erase(rmvIterB, useBlocks.end());

	for (auto i : useEnemies) {
		if (i->flag.isDead) {
			i->disuse();
		}
		else if (0) {//もしプレイヤーと遠かったら
			i->disuse();
		}
	}
	auto rmvIterE = std::remove_if(useEnemies.begin(), useEnemies.end(), [](const std::shared_ptr<Enemy>& a) {
		return !a->obj.isUsing;
	});
	useEnemies.erase(rmvIterE, useEnemies.end());
}

void UseOperator::update(Player& player, const double time_speed) {
	for (auto enemy : useEnemies) {
		enemy->update(player, useBlocks, time_speed);
	}
}

void UseOperator::init() {
	for (int i = 0; i < useEnemies.size(); i++) {
		useEnemies[i]->disuse();
	}
	for (int i = 0; i < useBlocks.size(); i++) {
		useBlocks[i]->disuse();
	}
	useEnemies.clear();
	useBlocks.clear();
}