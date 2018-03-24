#include "Map.h"

Object::Object(PhysicsWorld& world, RectF _range) :
	pos(_range.pos + range.size / 2.0),
	range(_range),
	body(world.createRect(Vec2(0, 0), _range, PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Static)) {

}

void Object::draw() const {
	range.draw();
}



Map::Map() :
	ground_kari(Pworld.createLineString(Vec2(0, 0), Array<Vec2>{Vec2(-100, 600) / 100.0, Vec2(10000, 600) / 100.0}, none, none, PhysicsBodyType::Static)) {
	//“K“–‚Éobj‚ð’Ç‰Á
	obj.emplace_back(std::make_shared<Object>(Pworld, RectF((Vec2(-100, 500) / 100.0), Vec2(100, 100) / 100.0)));

	Pworld.setGravity(Vec2(0.0, 9.8));

	TextureAsset::Register(L"Dview", L"Data/DistantView.png");
	TextureAsset::Register(L"Mview", L"Data/MiddleView.png");
}

void Map::update() {
	Pworld.update(1.0 / 60.0);
}

void Map::draw(Vec2 camera) const {
	//”wŒi‚Ì•`‰æ
	Vec2 temp(Window::Center() - camera);
	//Println(temp);
	double tmp = 20;//0.4
	double tmp2 = -80;
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(-temp.x * tmp2, -temp.y * tmp) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(-temp.x * tmp2 + 1280, -temp.y * tmp) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(-temp.x * tmp2 - 1280, -temp.y * tmp) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(-temp.x * tmp2 + 2560, -temp.y * tmp) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(-temp.x * tmp2 - 2560, -temp.y * tmp) / 100.0);
	double tmp_y = 10;//0.2
	double tmp_x = -40;
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(-temp.x * tmp_x, -temp.y*tmp_y) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(-temp.x * tmp_x + 2560, -temp.y*tmp_y) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(-temp.x * tmp_x - 2560, -temp.y*tmp_y) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(-temp.x * tmp_x + 5120, -temp.y*tmp_y) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(-temp.x * tmp_x - 5120, -temp.y*tmp_y) / 100.0);

	//obj‚Ì•`‰æ
	ground_kari.draw();
	for (const auto& i : obj) {
		i->draw();
	}
}
