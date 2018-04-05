#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Attack.h"

const int Slash::VANISH_LIMIT = 30;

const Vec2 Slash::SIZE = Vec2(32.0, 32.0) / 100;

const int Slash::POWER = 10;

Attack::Attack(Vec2 _pos, RectF _range) :
	count(0),
	pos(_pos),
	range(_range),
	isDead(false) {

}

Slash::Slash(Vec2 _pos) :
	Attack(_pos, RectF(_pos - (SIZE / 2.0), SIZE)) {

}

void Slash::update() {
	count++;
	if (count > VANISH_LIMIT) {
		isDead = true;
	}


}

void Slash::draw() {
	range.draw(Palette::Red);
}

Animation::Animation() {

}