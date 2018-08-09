#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

extern class Block;

class Attack {
public:
	const int VANISH_LIMIT;
	const int POWER;
	const int DIR;

	RectF range;
	Vec2 pos;
	double count;
	bool isDead;

	Attack(Vec2 _pos, RectF _range, int _DIR, int _VANISH_LIMIT, int _POWER);
	virtual void update(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) = 0;
	virtual ~Attack() = default;

	virtual void draw() = 0;//�Ƃ肠�����f�o�b�O�p
private:
};

class Slash : public Attack {
public:
	Slash(Vec2 _pos, int _DIR, int _VANISH_LIMIT, Vec2 _SIZE, int _POWER);

	void update(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) override;
	virtual ~Slash() = default;

	virtual void draw() = 0;
};
class Slash1 : public Slash {
public:
	Slash1(Vec2 _pos, int _DIR);

	void draw() override;
};
class Slash2 : public Slash {
public:
	Slash2(Vec2 _pos, int _DIR);

	void draw() override;
};
class Slash3 : public Slash {
public:
	Slash3(Vec2 _pos, int _DIR);

	void draw() override;
};

class DogSlash : public Slash {
public:
	DogSlash(Vec2 _pos, int _DIR);

	void draw() override;
};

class Shoot : public Attack {
public:
	Shoot(Vec2 _pos, int _DIR);

	void update(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) override;
	void draw() override;
};

class TankShoot : public Attack {
public:
	TankShoot(Vec2 _pos, int _DIR);

	void update(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) override;
	void draw() override;
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