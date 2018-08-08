#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"Block.h"
#include "Enemy.h"

class UseOperator {
private:
	UseOperator();
	UseOperator(const UseOperator& r) {}
	UseOperator& operator=(const UseOperator& r) {}
public:
	std::vector<std::shared_ptr<Block>> useBlocks;
	std::vector<std::shared_ptr<Enemy>> useEnemies;

	static UseOperator& get() {
		static UseOperator inst;
		return inst;
	}
	void addUsingBlock(std::shared_ptr<Block> obj, PhysicsWorld& Pworld, PhysicsWorld& Eworld);
	void addUsingEnemy(std::shared_ptr<Enemy> obj, PhysicsWorld &Eworld);
	void checkUsing(Vec2 player);
	void update(Player& player, const double time_speed);
	void draw();
};