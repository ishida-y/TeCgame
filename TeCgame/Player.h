#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Enemy.h"

//pos‚ğ“K“–‚É’Ç‰Á‚µ‚½i’¼‚µ‚Æ‚¢‚Äj
class Player {
public:
	PhysicsBody body;
	RectF range;
	int hp;
	int dir;
	Vec2 pos;

	const static Vec2 PLAYER_SIZE;



	Player(PhysicsWorld& world);

	void update(const EnemyManager& enemymanager);
	void draw() const;
};