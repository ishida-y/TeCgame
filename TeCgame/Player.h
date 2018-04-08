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
	int jumpCount;
	int slashCount;

	class Flag {
	public:
		bool jump;
		bool attack;

		Flag();
	} flag;

	//AttackManager attackManager;
	std::vector<std::shared_ptr<Attack>> attacks;

	const static int JUMP_LIMIT;
	const static int SLASH_LIMIT;

	const static Vec2 PLAYER_SIZE;
	const static Vec2 FOOT_SIZE;

	Player(PhysicsWorld& world);
	void update(const EnemyManager& enemymanager, const std::vector<std::shared_ptr<Object>>& obj, double& time_speed);
	void draw() const;

private:
	void move(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed);
	void time_control(double& time_speed);
	void attack();
};