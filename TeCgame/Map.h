#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>
#include <memory>
#include <algorithm>
#include "BlockManager.h"
#include "BackGround.h"
#include"EnemyManager.h"

class Map {
public:
	BlockManager blockmanager;
	EnemyManager enemymanager;
	BackGround Dview;
	BackGround Mview;

	PhysicsWorld Pworld;
	PhysicsWorld Eworld;
	Map();
	void update(double& time_speed);
	void draw(Vec2 camera) const;
	void init();
};
