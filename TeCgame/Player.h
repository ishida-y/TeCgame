#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Enemy.h"
#include"Attack.h"
//#include"Animation.h"


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
		int slashStage;

		Flag();
	} flag;

	std::vector<std::shared_ptr<Attack>> attacks;
	//std::vector<std::shared_ptr<Animation>> animations;

	const static int JUMP_LIMIT;
	const static int SLASH_LIMIT; //attack状態解除までのフレーム数
	const static int SLASH_COOLTIME; //次の攻撃が入力できるまでのフレーム数
	//つまり SLASH_LIMIT > SLASH_COOLTIME

	const static Vec2 PLAYER_SIZE;
	const static Vec2 FOOT_SIZE;

	Player(PhysicsWorld& world);
	void update(const EnemyManager& enemymanager, const std::vector<std::shared_ptr<Object>>& obj, double& time_speed);
	void draw() const;

private:
	void move(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed);
	void jump(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed);
	void checkDir();
	void timeControl(double& time_speed);
	void attack();
	void addSlash();
};