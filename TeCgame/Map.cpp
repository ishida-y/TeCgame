#include "Map.h"
#include "UseOperator.h"


Map::Map() :
	blockmanager(L"obj1"), 
	Dview(L"DistantView", Vec2(0.2, 0.2)),
	Mview(L"MiddleView", Vec2(0.4, 0.3)),
	enemymanager(L"obj2"){
	Pworld.setGravity(Vec2(0.0, 9.8));
	Eworld.setGravity(Vec2(0.0, 9.8));
	blockmanager.useUpdate(Pworld, Eworld);
}

void Map::update(double& time_speed) {
	Pworld.update(1.0 / 60.0 * time_speed);
	Eworld.update(1.0 / 60.0 * time_speed);
	blockmanager.useUpdate(Pworld, Eworld);//�g��obj�̌v�Z
	enemymanager.useUpdate(Eworld);
}

void Map::draw(Vec2 camera) const {
	//�w�i�̕`��
	Dview.draw(camera);
	Mview.draw(camera);
}
