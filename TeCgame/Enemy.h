#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>

#include "Block.h"

class Player;

class Enemy {
public:
	Object obj;
	std::shared_ptr<PhysicsBody> body;
	RectF range;
	int hp;
	RectF atc_range;
	int atc_c;
	int dir;
	bool isDead;
	bool disPlayer;
	bool hit;
	int c_move;
	int c_hit;
	int atc_damage;
	int hit_damage;


	Enemy(String _name, Vec2 _pos, double _rot = 0.0, Vec2 _scale = Vec2(1.0, 1.0), int _alpha = 255);
	void update(const Player& player, const std::vector<std::shared_ptr<Block>>& obj);
	virtual void draw() const = 0;
	virtual ~Enemy() = default;
	void use(PhysicsWorld& world);
	void disuse();
	void init(); //èâä˙âª

private:
	virtual void move(const Player& player) = 0;
	void check_dir();
	virtual void slash(const Player& player) = 0;
	virtual void check_hit(const Player& player) = 0;
	void check_dead();
};


class SampleEnemy : public Enemy {
public:
	SampleEnemy(String _name, Vec2 _pos, double _rot = 0.0, Vec2 _scale = Vec2(1.0, 1.0), int _alpha = 255);
	void draw() const;
private:
	void move(const Player& player);
	void slash(const Player& player);
	void check_hit(const Player& player);
};
