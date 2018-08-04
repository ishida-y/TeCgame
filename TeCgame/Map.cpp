#include "Map.h"

Object::Object(PhysicsWorld& world, RectF _range) :
	range(_range),
	pos(_range._get_center()),
	body(world.createRect(Vec2(0, 0), _range, PhysicsMaterial(1.0, 0.0, 0.0), none, PhysicsBodyType::Static)) {

}

void Object::draw() const {
	range.draw();
	Circle(pos, 5.0/100.0).draw(Palette::Red);
}



Map::Map() {
	//“K“–‚Éobj‚ð’Ç‰Á
	obj.emplace_back(std::make_shared<Object>(Pworld, RectF((Vec2(-100, 600) / 100.0), Vec2(10100, 10) / 100.0)));
	obj.emplace_back(std::make_shared<Object>(Pworld, RectF((Vec2(-90, -300) / 100.0), Vec2(10, 1000) / 100.0)));
	obj.emplace_back(std::make_shared<Object>(Pworld, RectF((Vec2(500, 300) / 100.0), Vec2(100, 300) / 100.0)));

	Pworld.setGravity(Vec2(0.0, 9.8));

	TextureAsset::Register(L"Dview", L"Data/DistantView.png");
	TextureAsset::Register(L"Mview", L"Data/MiddleView.png");
}

void Map::update(double& time_speed) {
	Pworld.update(1.0 / 60.0 * time_speed);
}

void Map::draw(Vec2 camera) const {
	//”wŒi‚Ì•`‰æ
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

	//obj‚Ì•`‰æ
	for (const auto& i : obj) {
		i->draw();
	}
}
