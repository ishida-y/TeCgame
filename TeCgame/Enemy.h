#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>

#include "Block.h"
#include "Attack.h"

class Player;

class Enemy {
public:
	Object obj;
	std::shared_ptr<PhysicsBody> body;
	RectF range;
	Vec2 pos;
	Vec2 velocity;
	int hp;
	int atc_c;
	int dir;
	int c_move;
	int c_hit;
	int atc_damage;
	int hit_damage;

	class Flag {
	public:
		bool isDead;
		bool hit;
		bool attack;

		Flag();
	} flag;

	std::vector<std::shared_ptr<Attack>> attacks;

	Enemy(String _name, Vec2 _pos, double _rot = 0.0, Vec2 _scale = Vec2(1.0, 1.0), int _alpha = 255);
	void update(const Player& player, const std::vector<std::shared_ptr<Block>>& obj, const double time_speed);
	virtual void draw() const = 0;
	virtual ~Enemy() = default;
	void use(PhysicsWorld& world);
	void disuse();
	void init(); //èâä˙âª

protected:
	double attackCount;

	virtual void attack(const double time_speed) = 0;
	virtual void move(const Player& player, const double time_speed) = 0;
	void reflectPhysics();
	void check_dir();
	virtual void check_hit(const Player& player) = 0;
	void check_dead();
};


class SampleEnemy : public Enemy {
public:
	SampleEnemy(String _name, Vec2 _pos, double _rot = 0.0, Vec2 _scale = Vec2(1.0, 1.0), int _alpha = 255);
	void draw() const;
private:
	void attack(const double time_speed);
	void move(const Player& player, const double time_speed);
	void check_hit(const Player& player);
};

class Dog :public Enemy {
public:
	Dog(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha);
	void draw() const;
private:
	void attack(const double time_speed);
	void move(const Player& player, const double time_speed);
	void check_hit(const Player& player);
};

class Drone :public Enemy {
public:
	Drone(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha);
	void draw() const;
private:
	void attack(const double time_speed);
	void move(const Player& player, const double time_speed);
	void check_hit(const Player& player);
};

class Tank :public Enemy {
public:
	Tank(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha);
	void draw() const;
private:
	void attack(const double time_speed);
	void move(const Player& player, const double time_speed);
	void check_hit(const Player& player);
};