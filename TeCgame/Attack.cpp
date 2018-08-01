#include"Attack.h"

//const int Slash1::VANISH_LIMIT = 30;
//const int Slash2::VANISH_LIMIT = 30;
//const int Slash3::VANISH_LIMIT = 30;
//
//const Vec2 Slash1::SIZE = Vec2(32.0, 64.0) / 100;
//const Vec2 Slash2::SIZE = Vec2(48.0, 48.0) / 100;
//const Vec2 Slash3::SIZE = Vec2(64.0, 64.0) / 100;
//
//const int Slash1::POWER = 10;
//const int Slash2::POWER = 10;
//const int Slash3::POWER = 10;

Attack::Attack(Vec2 _pos, RectF _range) :
	count(0),
	pos(_pos),
	range(_range),
	isDead(false) {

}

Slash::Slash(Vec2 _pos, int _VANISH_LIMIT, Vec2 _SIZE, int _POWER) :
	VANISH_LIMIT(_VANISH_LIMIT),
	//SIZE(_SIZE),
	POWER(_POWER),
	Attack(_pos, RectF(_pos - (_SIZE / 2.0), _SIZE)) {

}
Slash1::Slash1(Vec2 _pos) :
	Slash(_pos,
		5/*VANISH_LIMIT*/,
		Vec2(32.0, 64.0) / 100/*SIZE*/,
		10/*POWER*/) {

}
Slash2::Slash2(Vec2 _pos) :
	Slash(_pos,
		5/*VANISH_LIMIT*/,
		Vec2(48.0, 48.0) / 100/*SIZE*/,
		10/*POWER*/) {

}
Slash3::Slash3(Vec2 _pos) :
	Slash(_pos,
		8/*VANISH_LIMIT*/,
		Vec2(64.0, 64.0) / 100/*SIZE*/,
		10/*POWER*/) {

}

void Slash::update() {
	count++;
	if (count > VANISH_LIMIT) {
		isDead = true;
	}
}

void Slash1::draw() {
	range.draw(Palette::Red);
}
void Slash2::draw() {
	range.draw(Palette::Orange);
}
void Slash3::draw() {
	range.draw(Palette::Yellow);
}
