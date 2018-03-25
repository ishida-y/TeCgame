#include"Player.h"
#include"Enemy.h"
#include"GameSystem.h"

const Vec2 Player::PLAYER_SIZE = Vec2(64.0 / 100.0, 128.0 / 100.0);
const Vec2 Player::FOOT_SIZE = Vec2(32.0 / 100.0, 32.0 / 100.0);

Player::Player(PhysicsWorld& world) :
	body(world.createRect(Vec2(0, 0), RectF(PLAYER_SIZE), PhysicsMaterial(1.0, 0.0, 0.0), none, PhysicsBodyType::Dynamic)),
	range(RectF(body.getPos(), PLAYER_SIZE)),
	hp(100),
	dir(1),
	pos(range._get_center()),
	foot_range(RectF(Vec2(pos.x, range.y + range.h), FOOT_SIZE)) {

	body.setGravityScale(2.0);
	body.setFixedRotation(true);

}

void Player::update(const EnemyManager& enemymanager) {
	static double yspeed_prev = 0; //前フレームのy速度

	body.setVelocity(Vec2(4.0 * GameSystem::get().input.stick.L.x, body.getVelocity().y));
	if (body.getVelocity().y == 0 && yspeed_prev >= 0 && GameSystem::get().input.janp.clicked) {
		body.applyForce(Vec2(0.0, -600.0));
	}

	yspeed_prev = body.getVelocity().y; //本フレームのy速度を保存

	if (body.getVelocity().x > 0 && dir == -1) {
		dir = 1;
	}
	if (body.getVelocity().x < 0 && dir == 1) {
		dir = -1;
	}
	//rangeとかbodyのpos(getPos)は長方形の左上
	range.pos = body.getPos();
	//こいつだけ中心座標
	pos = range._get_center();//range.pos + Vec2(range.w / 2.0, range.h / 2.0);

	foot_range.setCenter(pos.x, range.y + range.h + foot_range.h / 2.0);

}

void Player::draw() const {
	range.draw();
	Circle(pos, 0.05).draw(Palette::Red);
	foot_range.draw(Palette::Orange);

}