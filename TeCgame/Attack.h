#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

class Attack {
public:

	RectF range;
	Vec2 pos;
	int count;
	bool isDead;

	Attack(Vec2 _pos, RectF _range);
	virtual void update() = 0;
	virtual ~Attack() = default;

	virtual void draw() = 0;//�Ƃ肠�����f�o�b�O�p
private:
};

class Slash : public Attack {
public:
	Slash(Vec2 _pos);
	static const int VANISH_LIMIT;
	static const Vec2 SIZE;
	static const int POWER;

	void update() override;
	void draw() override;//�Ƃ肠�����f�o�b�O�p
};

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

//class AttackManager {
//public:
//	std::vector<std::shared_ptr<Attack>> attacks;
//
//	AttackManager();
//	void update();
//	void draw();
//
//};