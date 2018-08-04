#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>
#include <memory>
#include <algorithm>
#include "ObjectManager.h"
#include "BackGround.h"

class Map {
public:
	ObjectManager obj;
	BackGround Dview;
	BackGround Mview;

	PhysicsWorld Pworld;
	//PhysicsWorld Eworld;
	Map();
	void update(double& time_speed);
	void draw(Vec2 camera) const;
};
