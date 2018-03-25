#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Enemy.h"


class Player {
public:
	PhysicsBody body;
	RectF range;
	RectF foot_range;
	int hp;
	int dir;
	Vec2 pos;

	const static Vec2 PLAYER_SIZE;
	const static Vec2 FOOT_SIZE;



	Player(PhysicsWorld& world);

	void update(const EnemyManager& enemymanager);
	void draw() const;
};