#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Enemy.h"
#include"Attack.h"


class Player {
public:
	PhysicsBody body;
	RectF range;
	RectF foot_range;
	int hp;
	int dir;
	Vec2 pos;
	bool jumpFlag;
	int jumpCount;

	//std::vector<std::shared_ptr<Attack>> attacks;

	const static int JUMP_LIMIT;
	const static Vec2 PLAYER_SIZE;
	const static Vec2 FOOT_SIZE;



	Player(PhysicsWorld& world);

	void update(const EnemyManager& enemymanager, const std::vector<std::shared_ptr<Object>>& obj);
	void draw() const;
};