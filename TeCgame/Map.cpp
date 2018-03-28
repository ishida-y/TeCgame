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
	//�K����obj��ǉ�
	obj.emplace_back(std::make_shared<Object>(Pworld, RectF((Vec2(-100, 600) / 100.0), Vec2(10100, 10) / 100.0)));
	obj.emplace_back(std::make_shared<Object>(Pworld, RectF((Vec2(-100, 500) / 100.0), Vec2(100, 100) / 100.0)));
	obj.emplace_back(std::make_shared<Object>(Pworld, RectF((Vec2(500, 300) / 100.0), Vec2(100, 300) / 100.0)));

	Pworld.setGravity(Vec2(0.0, 9.8));

	TextureAsset::Register(L"Dview", L"Data/DistantView.png");
	TextureAsset::Register(L"Mview", L"Data/MiddleView.png");
}

void Map::update() {
	Pworld.update(1.0 / 60.0);
}

void Map::draw(Vec2 camera) const {
	//�w�i�̕`��
	Vec2 temp(Window::Center() - camera);
	Println(temp);
	double tmp = 80;//0.4
	double tmp2 = 80;
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(temp.x * tmp2, temp.y * tmp - 200) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(temp.x * tmp2 + 1280, temp.y * tmp - 200) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(temp.x * tmp2 - 1280, temp.y * tmp - 200) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(temp.x * tmp2 + 2560, temp.y * tmp - 200) / 100.0);
	TextureAsset(L"Dview").scale(0.01).draw(Vec2(temp.x * tmp2 - 2560, temp.y * tmp - 200) / 100.0);
	double tmp_y = 40;//0.2
	double tmp_x = 40;
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(temp.x * tmp_x, temp.y*tmp_y - 200) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(temp.x * tmp_x + 2560, temp.y*tmp_y - 200) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(temp.x * tmp_x - 2560, temp.y*tmp_y - 200) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(temp.x * tmp_x + 5120, temp.y*tmp_y - 200) / 100.0);
	TextureAsset(L"Mview").scale(0.01).draw(Vec2(temp.x * tmp_x - 5120, temp.y*tmp_y - 200) / 100.0);

	//obj�̕`��
	for (const auto& i : obj) {
		i->draw();
	}
}
