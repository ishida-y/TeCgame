#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include<vector>

#include "Enemy.h"

class EnemyManager {
public:
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<String> names;
	String type;

	EnemyManager(String _type);

	void useUpdate(PhysicsWorld& world);
};