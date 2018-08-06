#pragma once
#include"Block.h"
#include<Siv3D.hpp>
#include<HamFramework.hpp>

class BlockManager {
public:
	BlockManager(String _type);
	void useUpdate(PhysicsWorld& Pworld, PhysicsWorld& Eworld);
	String type;
	std::vector<String> names;
	std::vector<std::shared_ptr<Block>> objs;
};