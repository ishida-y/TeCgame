#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

class Attack {
public:

	RectF range;
	int count;

	static const int ATTACK_POWER;
	static const int VANISH_LIMIT;

	Attack();
	virtual void update() = 0;
	virtual ~Attack();

private:
};

class Animation {

	int count;

	static const int VANISH_LIMIT;

	Animation();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ~Animation();
};