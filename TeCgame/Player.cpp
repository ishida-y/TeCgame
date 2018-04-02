#include"Player.h"
#include"Enemy.h"
#include"GameSystem.h"

const Vec2 Player::PLAYER_SIZE = Vec2(64.0 / 100.0, 128.0 / 100.0);
const Vec2 Player::FOOT_SIZE = Vec2(32.0 / 100.0, 32.0 / 100.0);
const int Player::JUMP_LIMIT = 5;

Player::Player(PhysicsWorld& world) :
	body(world.createRect(Vec2(0, 0), RectF(PLAYER_SIZE), PhysicsMaterial(1.0, 0.0, 0.02), none, PhysicsBodyType::Dynamic)),
	range(RectF(body.getPos(), PLAYER_SIZE)),
	hp(100),
	dir(1),
	pos(range._get_center()),
	foot_range(RectF(Vec2(pos.x, range.y + range.h), FOOT_SIZE)),
	jumpFlag(false),
	jumpCount(0) {

	body.setGravityScale(2.0);
	body.setFixedRotation(true);

}

void Player::update(const EnemyManager& enemymanager, const std::vector<std::shared_ptr<Object>>& obj, double& time_speed) {
	
	time_control(time_speed);

	body.setVelocity(Vec2(4.0 * GameSystem::get().input.stick.L.x, body.getVelocity().y));

	for (auto elem : obj) {
		if (foot_range.intersects(elem->range)) {
			if (GameSystem::get().input.jump.get_clicked()) {
				body.applyForce(Vec2(0.0, -250.0) / time_speed);
				jumpFlag = true;
			}
		}
	}
	if (jumpFlag) {
		if ((jumpCount < JUMP_LIMIT) && GameSystem::get().input.jump.get_pressed()) {
			if ((jumpCount > 0) && (jumpCount % 2 == 0)) {
				body.applyForce(Vec2(0.0, -150.0) / time_speed);
			}
			jumpCount++;
		}
		else {
			jumpFlag = false;
			jumpCount = 0;
		}
	}

	if (body.getVelocity().x > 0 && dir == -1) {
		dir = 1;
	}
	if (body.getVelocity().x < 0 && dir == 1) {
		dir = -1;
	}
	//range‚Æ‚©body‚Ìpos(getPos)‚Í’·•ûŒ`‚Ì¶ã
	range.pos = body.getPos();
	//‚±‚¢‚Â‚¾‚¯’†SÀ•W
	pos = range._get_center();//range.pos + Vec2(range.w / 2.0, range.h / 2.0);

	foot_range.setCenter(pos.x, range.y + range.h + foot_range.h / 2.0);

}

void Player::time_control(double& time_speed) {
	time_speed = 1.0 - GameSystem::get().input.triggerL * 0.8;
}

void Player::draw() const {
	range.draw();
	Circle(pos, 0.05).draw(Palette::Red);
	foot_range.draw(Palette::Orange);

}