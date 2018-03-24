#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>
#include <memory>
#include <algorithm>

class Object {
public:
	Vec2 pos;
	RectF range;
	PhysicsBody body;

	Object(PhysicsWorld& world, RectF _range);
	void draw() const;
};

class Map {
public:
	PhysicsWorld Pworld;
	//PhysicsWorld Eworld;
	std::vector<std::shared_ptr<Object>> obj;
	PhysicsBody ground_kari; //‰¼‚Ì’n–Ê

	Map();
	void update();
	void draw(Vec2 camera) const;
};
