#include"Attack.h"
#include"BlockManager.h"

Attack::Attack(Vec2 _pos, RectF _range, int _DIR, int _VANISH_LIMIT, int _POWER) :
	count(0),
	pos(_pos),
	range(_range),
	DIR(_DIR),
	VANISH_LIMIT(_VANISH_LIMIT),
	POWER(_POWER),
	isDead(false) {

}

Slash::Slash(Vec2 _pos, int _DIR, int _VANISH_LIMIT, Vec2 _SIZE, int _POWER) :
	Attack(_pos, RectF(_pos - (_SIZE / 2.0), _SIZE), _DIR, _VANISH_LIMIT, _POWER) {

}
Slash1::Slash1(Vec2 _pos, int _DIR) :
	Slash(_pos,
		_DIR,
		5/*VANISH_LIMIT*/,
		Vec2(32.0, 64.0) / 100/*SIZE*/,
		10/*POWER*/) {

}
Slash2::Slash2(Vec2 _pos, int _DIR) :
	Slash(_pos,
		_DIR,
		5/*VANISH_LIMIT*/,
		Vec2(48.0, 48.0) / 100/*SIZE*/,
		10/*POWER*/) {

}
Slash3::Slash3(Vec2 _pos, int _DIR) :
	Slash(_pos,
		_DIR,
		8/*VANISH_LIMIT*/,
		Vec2(64.0, 64.0) / 100/*SIZE*/,
		10/*POWER*/) {

}

DogSlash::DogSlash(Vec2 _pos, int _DIR) :
	Slash(_pos,
		_DIR,
		10,
		Vec2(64.0, 48.0) / 100.0,
		10) {

}


Shoot::Shoot(Vec2 _pos, int _DIR) :
	Attack(_pos,
		RectF(_pos - (Vec2(16.0, 16.0) / 2.0 / 100.0), Vec2(16.0, 16.0) / 100.0),
		_DIR,
		60,
		5) {

}

TankShoot::TankShoot(Vec2 _pos, int _DIR) :
	Attack(_pos,
		RectF(_pos - (Vec2(32.0, 32.0) / 2.0 / 100.0), Vec2(32.0, 16.0) / 100.0),
		_DIR,
		120,
		5) {

}

void Slash::update(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {
	count += time_speed;
	if (count > VANISH_LIMIT) {
		isDead = true;
	}
}

void Shoot::update(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {
	count += time_speed;
	if (count > VANISH_LIMIT) {
		isDead = true;
	}
	for (auto elem : obj) {
		if (range.intersects(elem->range)) {
			isDead = true;
			break;
		}
	}
	range.setPos(range.pos + time_speed*DIR*Vec2(10.0, 0.0) / 100.0);
	pos = range._get_center();
}

void TankShoot::update(const std::vector<std::shared_ptr<Block>>& obj, const double& time_speed) {
	count += time_speed;
	if (count > VANISH_LIMIT) {
		isDead = true;
	}
	for (auto elem : obj) {
		if (range.intersects(elem->range)) {
			isDead = true;
			break;
		}
	}
	range.setPos(range.pos + time_speed*DIR*Vec2(5.0, 0.0) / 100.0);
	pos = range._get_center();
}

void Slash1::draw() {
	range.draw(Palette::Red);
	Triangle(pos + Vec2(0, -5)/100.0, pos + Vec2(10 * DIR, 0) / 100.0, pos + Vec2(0, 5) / 100.0).draw();
}
void Slash2::draw() {
	range.draw(Palette::Orange);
	Triangle(pos + Vec2(0, -5) / 100.0, pos + Vec2(10 * DIR, 0) / 100.0, pos + Vec2(0, 5) / 100.0).draw();
}
void Slash3::draw() {
	range.draw(Palette::Yellow);
	Triangle(pos + Vec2(0, -5) / 100.0, pos + Vec2(10 * DIR, 0) / 100.0, pos + Vec2(0, 5) / 100.0).draw();
}

void DogSlash::draw() {
	range.draw(Palette::Orange);
	Triangle(pos + Vec2(0, -5) / 100.0, pos + Vec2(10 * DIR, 0) / 100.0, pos + Vec2(0, 5) / 100.0).draw();
}

void Shoot::draw() {
	range.draw(Palette::Blue);
	Triangle(pos + Vec2(0, -5) / 100.0, pos + Vec2(10 * DIR, 0) / 100.0, pos + Vec2(0, 5) / 100.0).draw();
}

void TankShoot::draw() {
	range.draw(Palette::Cornflowerblue);
	Triangle(pos + Vec2(0, -5) / 100.0, pos + Vec2(10 * DIR, 0) / 100.0, pos + Vec2(0, 5) / 100.0).draw();
}
