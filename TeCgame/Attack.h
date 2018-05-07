#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

class Attack {
public:

	RectF range;
	Vec2 pos;
	int count;
	//int dir;
	bool isDead;

	Attack(Vec2 _pos, RectF _range);
	virtual void update() = 0;
	virtual ~Attack() = default;

	virtual void draw() = 0;//とりあえずデバッグ用
private:
};

class Slash : public Attack {
public:
	Slash(Vec2 _pos, int _VANISH_LIMIT, Vec2 _SIZE, int _POWER);
	const int VANISH_LIMIT;
	//const Vec2 SIZE;
	const int POWER;

	void update() override;
	virtual ~Slash() = default;

	virtual void draw() = 0;
};
class Slash1 : public Slash {
public:
	//static const int VANISH_LIMIT;
	//static const Vec2 SIZE;
	//static const int POWER;
	Slash1(Vec2 _pos);

	void draw();
};
class Slash2 : public Slash {
public:
	//static const int VANISH_LIMIT;
	//static const Vec2 SIZE;
	//static const int POWER;
	Slash2(Vec2 _pos);

	void draw();
};
class Slash3 : public Slash {
public:
	//static const int VANISH_LIMIT;
	//static const Vec2 SIZE;
	//static const int POWER;
	Slash3(Vec2 _pos);

	void draw();
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