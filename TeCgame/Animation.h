#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

class Animation {
public:
	int count;
	Vec2 pos;


	static const int VANISH_LIMIT;

	Animation();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ~Animation() = default;
};