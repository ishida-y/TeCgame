#include "Object.h"
#include "GameSystem.h"
/*
TODO:ägëÂèkè¨èàóù
*/
Object::Object(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	name(_name),
	pos(_pos),
	rot(_rot),
	scale(_scale),
	alpha(_alpha),
	isUsing(false) {
	//ç¿ïWà íu
	range = RectF((pos - TextureAsset(name).size / 2.0) / 100.0, TextureAsset(name).size / 100.0);
}

void Object::draw() {
	TextureAsset(name).scale(scale / 100.0).rotate(rot).draw(pos / 100.0 - TextureAsset(name).size / 2.0 / 100.0, Color(255, 255, 255, alpha));
	if (GameSystem::debug) {
		range.draw(Color(255, 255, 255, 100));
		//Circle(range._get_tl(), 0.1).draw(Palette::Red);
		//Circle(range._get_tr(), 0.1).draw(Palette::Blue);
		range._get_tl().draw(Palette::Red);
		range._get_tr().draw(Palette::Blue);
		
	}
}

void Object::use(PhysicsWorld world) {
	isUsing = true;
	bodyP.reset(new PhysicsBody(world.createRect(Vec2(0, 0), range, PhysicsMaterial(1.0, 0.0, 0.0), none, PhysicsBodyType::Static)));
}

void Object::disuse() {
	isUsing = false;
	bodyP.reset();
}