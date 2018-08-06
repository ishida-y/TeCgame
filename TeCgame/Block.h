#pragma once
#include<Siv3D.hpp>
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "Object.h"
/*
配置する物体のクラス
*/

class Block{
public:
	Block(String _name, Vec2 _pos, double _rot = 0.0, Vec2 _scale = Vec2(1.0, 1.0), int _alpha = 255);
	virtual ~Block() {
	}
	Object obj;
	RectF range;
	void draw();
	std::shared_ptr<PhysicsBody> bodyP;
	std::shared_ptr<PhysicsBody> bodyE;
	void use(PhysicsWorld& Pworld, PhysicsWorld& Eworld);
	void disuse();
};
