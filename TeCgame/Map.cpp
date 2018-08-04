#include "Map.h"
#include "UseOperator.h"


Map::Map() :
	obj(L"obj1"), 
	Dview(L"DistantView", Vec2(0.2, 0.2)),
	Mview(L"MiddleView", Vec2(0.4, 0.3)) {
	Pworld.setGravity(Vec2(0.0, 9.8));
	UseOperator::get().init(Pworld);
	//TextureAsset::Register(L"Dview", L"Data/DistantView.png");
	//TextureAsset::Register(L"Mview", L"Data/MiddleView.png");
	obj.useUpdate();
}

void Map::update(double& time_speed) {
	Pworld.update(1.0 / 60.0 * time_speed);
	obj.useUpdate();//Žg‚¤obj‚ÌŒvŽZ
}

void Map::draw(Vec2 camera) const {
	//”wŒi‚Ì•`‰æ
	Dview.draw(camera);
	Mview.draw(camera);
	/*
	double tmp = 80;//0.4
	double tmp2 = 80;
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(camera.x * tmp2, camera.y * tmp - 200) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(camera.x * tmp2 + 1280, camera.y * tmp - 200) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(camera.x * tmp2 - 1280, camera.y * tmp - 200) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(camera.x * tmp2 + 2560, camera.y * tmp - 200) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(camera.x * tmp2 - 2560, camera.y * tmp - 200) / 100.0);
	double tmp_y = 40;//0.2
	double tmp_x = 40;
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(camera.x * tmp_x, camera.y*tmp_y - 200) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(camera.x * tmp_x + 2560, camera.y*tmp_y - 200) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(camera.x * tmp_x - 2560, camera.y*tmp_y - 200) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(camera.x * tmp_x + 5120, camera.y*tmp_y - 200) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(camera.x * tmp_x - 5120, camera.y*tmp_y - 200) / 100.0);
	*/
	//obj‚Ì•`‰æ
	UseOperator::get().draw();
}
