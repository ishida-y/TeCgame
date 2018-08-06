#include "Block.h"
/*
TODO:ägëÂèkè¨èàóù
*/
Block::Block(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	obj(_name, _pos, _rot, _scale, _alpha){
	//ç¿ïWà íu
	range = RectF((obj.pos - TextureAsset(obj.name).size / 2.0) / 100.0, TextureAsset(obj.name).size / 100.0);
}

void Block::draw() {
	TextureAsset(obj.name).scale(obj.scale / 100.0).rotate(obj.rot).draw(obj.pos / 100.0 - TextureAsset(obj.name).size / 2.0 / 100.0, Color(255, 255, 255, obj.alpha));
}

void Block::use(PhysicsWorld& Pworld, PhysicsWorld& Eworld) {
	obj.isUsing = true;
	bodyP.reset(new PhysicsBody(Pworld.createRect(Vec2(0, 0), range, PhysicsMaterial(1.0, 0.0, 0.0), none, PhysicsBodyType::Static)));
	bodyE.reset(new PhysicsBody(Eworld.createRect(Vec2(0, 0), range, PhysicsMaterial(1.0, 0.0, 0.0), none, PhysicsBodyType::Static)));
}

void Block::disuse() {
	obj.isUsing = false;
	bodyP.reset();
	bodyE.reset();
}