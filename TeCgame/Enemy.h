#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>

#include"Map.h"

class Player;

class Enemy {
public:
	ham::PhysicsBody body;
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


	Enemy();
	void update(const Player& player, const std::vector<std::shared_ptr<Object>>& obj);
	virtual void move(const Player& player) = 0;
	void check_dir();
	virtual void attack(const Player& player) = 0;
	virtual void check_hit(const Player& player) = 0;
	void check_dead();
	virtual void draw() const = 0;
	virtual ~Enemy() = default;
};


class SampleEnemy : public Enemy {

	SampleEnemy(const PhysicsWorld& world, Vec2 _pos);

};

class EnemyManager {
public:
	std::vector<std::shared_ptr<Enemy>> enemies;

	EnemyManager();

	PhysicsWorld world;

	void update(const Player& player, const std::vector<std::shared_ptr<Object>>& obj);
	void dead();
	void draw() const;
};