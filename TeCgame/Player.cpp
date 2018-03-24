#include"Player.h"
#include"Enemy.h"
#include"GameSystem.h"

const Vec2 Player::PLAYER_SIZE = Vec2(64.0 / 100.0, 128.0 / 100.0);

Player::Player(PhysicsWorld& world) :
	body(world.createRect(Vec2(0, 0), RectF(PLAYER_SIZE), PhysicsMaterial(1.0, 0.01, 0.0), none, PhysicsBodyType::Dynamic)),
	range(RectF(body.getPos(), PLAYER_SIZE)),
	hp(100),
	dir(1),
	pos(body.getPos()){

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
	range.pos = body.getPos();

	pos = body.getPos();
}

void Player::draw() const {
	range.draw();
}