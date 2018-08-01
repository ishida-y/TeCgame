#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Enemy.h"
#include"Attack.h"


class Player {
public:
	PhysicsBody body;

	class Range {
	public:
		//あとで手とかも追加するはず(崖つかまりとかのために)
		RectF body;
		RectF foot_main;
		RectF foot_side; //壁キック用

		Range(PhysicsBody Pbody);
	} range;

	int hp;
	int dir;
	Vec2 pos;

	std::vector<std::shared_ptr<Attack>> attacks;
	//std::vector<std::shared_ptr<Animation>> animations;

	const static Vec2 PLAYER_SIZE;
	const static Vec2 FOOT_SIZE_MAIN;
	const static Vec2 FOOT_SIZE_SIDE;

	Player(PhysicsWorld& world);
	void update(const EnemyManager& enemymanager, const std::vector<std::shared_ptr<Object>>& obj, double& time_speed);
	void draw() const;

private:
	int jumpCount;
	int slashCount;

	class Flag {
	public:
		bool jump;
		bool slash;
		int slashStage;

		Flag();

	} flag;


	const static int JUMP_LIMIT;
	const static int SLASH_LIMIT; //slash状態解除までのフレーム数
	const static int SLASH_COOLTIME; //次の攻撃が入力できるまでのフレーム数
	//つまり SLASH_LIMIT > SLASH_COOLTIME

	void move(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed);
	void jump(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed);
	void checkDir();
	void timeControl(double& time_speed);
	void slash();
	void addSlash();
};