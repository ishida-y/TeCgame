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
		RectF body;
		RectF foot_main;
		RectF bottomRight, bottomLeft, upperRight, upperLeft; //�葫

		Range(PhysicsBody Pbody);
	} range;

	int hp;
	int dir;
	Vec2 pos;
	Vec2 velocity;

	std::vector<std::shared_ptr<Attack>> attacks;
	//std::vector<std::shared_ptr<Animation>> animations;


	Player(PhysicsWorld& world);
	void update(const EnemyManager& enemymanager, const std::vector<std::shared_ptr<Object>>& obj, double& time_speed);
	void draw() const;

private:
	int jumpCount;
	int slashCount;

	class Flag {
	public:
		bool onGround;
		bool jump;
		bool slash;
		int slashStage;

		Flag();

	} flag;

	const static Vec2 PLAYER_SIZE;
	const static Vec2 FOOT_SIZE_MAIN;
	const static Vec2 SIDE_SIZE;
	const static double MAX_SPEED_GROUND; //�n��ł̉��ړ��̍ő呬�x
	const static double MAX_SPEED_AIR; //�󒆂ł̉��ړ��̍ő呬�x
	const static double FORCE_AIR; //�󒆉��ړ��̍ۂ̗͂̋���
	const static int JUMP_LIMIT; //�W�����v���͎�t����
	const static int SLASH_LIMIT; //slash��ԉ����܂ł̃t���[����
	const static int SLASH_COOLTIME; //���̍U�������͂ł���܂ł̃t���[����
	//�܂� SLASH_LIMIT > SLASH_COOLTIME

	void move(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed);
	void jump(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed);
	void checkDir();
	void timeControl(double& time_speed);
	void reflectPhysics();
	void slash();
	void addSlash();
};