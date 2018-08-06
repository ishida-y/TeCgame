#include "Object.h"
/*
TODO:ägëÂèkè¨èàóù
*/
Object::Object(String _name, Vec2 _pos, double _rot, Vec2 _scale, int _alpha) :
	name(_name),
	pos(_pos),
	rot(_rot),
	scale(_scale),
	alpha(_alpha),
	isUsing(false){
}
/*
void Object::draw() {

}

void Object::update() {

}

void Object::use() {
	isUsing = true;
}

void Object::disuse() {
	isUsing = false;
}
*/