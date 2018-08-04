#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include"Object.h"

class UseOperator {
public:
	UseOperator();
	UseOperator(const UseOperator& r) {}
	UseOperator& operator=(const UseOperator& r) {}

	std::vector<std::shared_ptr<Object>> useObjs;

	PhysicsWorld *Pworld;

	static UseOperator& get() {
		static UseOperator inst;
		return inst;
	}
	void init(PhysicsWorld &pworld);
	void addUsing(std::shared_ptr<Object> obj);
	void cheackUsing(Vec2 player);
	//void update();
	void draw();
};