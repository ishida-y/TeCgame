#include "UseOperator.h"
#include"GameSystem.h"

UseOperator::UseOperator() {

}

void UseOperator::init(PhysicsWorld &pworld) {
	Pworld = &pworld;
}

void UseOperator::draw() {
	for (auto i : useObjs) {
		i->draw();
	}
	if (GameSystem::get().debug) {
		Print(L"useObjs:");
		Println(useObjs.size());
	}
}

void UseOperator::addUsing(std::shared_ptr<Object> obj) {
	useObjs.emplace_back(obj);
	obj->use(*Pworld);
}

void UseOperator::cheackUsing(Vec2 player) {
	for (auto i : useObjs) {
		if (0) {//‚à‚µƒvƒŒƒCƒ„[‚Æ‰“‚©‚Á‚½‚ç
			i->disuse();
		}
	}

	auto rmvIter = std::remove_if(useObjs.begin(), useObjs.end(), [](const std::shared_ptr<Object>& a) {
		return a->isUsing;
	});
	useObjs.erase(rmvIter, useObjs.end());
}