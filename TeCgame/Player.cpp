#include"Player.h"
#include"Enemy.h"
#include"GameSystem.h"

const Vec2 Player::PLAYER_SIZE = Vec2(64.0 / 100.0, 128.0 / 100.0);
const Vec2 Player::FOOT_SIZE_MAIN = Vec2(Player::PLAYER_SIZE.x, 8.0 / 100.0);
const Vec2 Player::FOOT_SIZE_SIDE = /*Player::FOOT_SIZE_MAIN + */Vec2(8.0 / 100.0, 0);
const int Player::JUMP_LIMIT = 5;
const int Player::SLASH_LIMIT = 30;
const int Player::SLASH_COOLTIME = 15;


Player::Player(PhysicsWorld& world) :
	body(world.createRect(Vec2(0, 0), RectF(PLAYER_SIZE), PhysicsMaterial(1.0, 0.0, 0.02), none, PhysicsBodyType::Dynamic)),
	range(body),
	hp(100),
	dir(1),
	pos(range.body._get_center()),
	flag(),
	jumpCount(0),
	slashCount(0) {

	body.setGravityScale(2.0);
	body.setFixedRotation(true);

}

Player::Range::Range(PhysicsBody Pbody) :
	body(RectF(Pbody.getPos(), PLAYER_SIZE)),
	foot_main(RectF(Vec2(body._get_center().x, body.y + body.h), FOOT_SIZE_MAIN)),
	foot_side(foot_main.pos - FOOT_SIZE_SIDE, FOOT_SIZE_MAIN + 2 * FOOT_SIZE_SIDE) {

}

Player::Flag::Flag() :
	jump(false),
	slash(false),
	slashStage(0) {

}

void Player::update(const EnemyManager& enemymanager, const std::vector<std::shared_ptr<Object>>& obj, double& time_speed) {
	timeControl(time_speed);
	move(obj, time_speed);
	checkDir();
	slash();
}

void Player::timeControl(double& time_speed) {
	time_speed = 1.0 - GameSystem::get().input.triggerL * 0.8;
}

void Player::slash() {
	if (flag.slash) {
		slashCount++;
		if (slashCount > SLASH_LIMIT) {
			slashCount = 0;
			flag.slash = false;
			flag.slashStage = 0;
		}
	}
	else {
		if (GameSystem::get().input.slash.get_clicked()) {
			addSlash();
			flag.slash = true;
		}
	}
	if (GameSystem::get().input.slash.get_clicked() && slashCount > SLASH_COOLTIME) {
		addSlash();
	}

	for (auto elem : attacks) {
		elem->update();
	}
	auto rmvIter = std::remove_if(attacks.begin(), attacks.end(), [](const std::shared_ptr<Attack>& a) {
		return a->isDead;
	});
	attacks.erase(rmvIter, attacks.end());
}

void Player::addSlash() {
	switch (flag.slashStage) {
	case 0:
		attacks.emplace_back(std::make_shared<Slash1>(pos + Vec2(dir*32.0 / 100.0, 0)));
		flag.slashStage++;
		break;
	case 1:
		attacks.emplace_back(std::make_shared<Slash2>(pos + Vec2(dir*32.0 / 100.0, 0)));
		slashCount = 0;
		flag.slashStage++;
		break;
	case 2:
		attacks.emplace_back(std::make_shared<Slash3>(pos + Vec2(dir*32.0 / 100.0, 0)));
		slashCount = 0;
		flag.slashStage++;
		break;
	}
}

void Player::move(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed) {

	body.setVelocity(Vec2(4.0 * GameSystem::get().input.stick.L.x, body.getVelocity().y));

	jump(obj, time_speed);

	//rangeÇ∆Ç©bodyÇÃpos(getPos)ÇÕí∑ï˚å`ÇÃç∂è„
	range.body.pos = body.getPos();
	//Ç±Ç¢Ç¬ÇæÇØíÜêSç¿ïW
	pos = range.body._get_center();

	range.foot_main.setCenter(pos.x, range.body.y + range.body.h + range.foot_main.h / 2.0);
	range.foot_side.setCenter(pos.x, range.body.y + range.body.h + range.foot_main.h / 2.0);
}

void Player::jump(const std::vector<std::shared_ptr<Object>>& obj, const double& time_speed) {

	for (auto elem : obj) {
		if (range.foot_main.intersects(elem->range)) {
			if (GameSystem::get().input.jump.get_clicked()) {
				body.applyForce(Vec2(0.0, -250.0) / time_speed);
				flag.jump = true;

			}
			break;
		}
		else if (range.foot_side.intersects(elem->range)) {
			if (GameSystem::get().input.jump.get_clicked()) {
				body.applyForce(Vec2(-100.0*dir, -200.0) / time_speed);
				flag.jump = true;
			}
		}
	}
	if (flag.jump) {
		if ((jumpCount < JUMP_LIMIT) && GameSystem::get().input.jump.get_pressed()) {
			if ((jumpCount > 0) && (jumpCount % 2 == 0)) {
				body.applyForce(Vec2(0.0, -150.0) / time_speed);
			}
			jumpCount++;
		}
		else {
			flag.jump = false;
			jumpCount = 0;
		}
	}

}

void Player::checkDir() {
	if (body.getVelocity().x > 0 && dir == -1) {
		dir = 1;
	}
	if (body.getVelocity().x < 0 && dir == 1) {
		dir = -1;
	}
}

void Player::draw() const {

	if (GameSystem::get().debug) {
		range.body.draw();
		Circle(pos, 0.05).draw(Palette::Red);
		range.foot_side.draw(Palette::Yellow);
		range.foot_main.draw(Palette::Orange);
		Print(L"player.pos:");
		Println(pos);
		Print(L"slashCount:");
		Println(slashCount);
		Print(L"flag.slashStage:");
		Println(flag.slashStage);
		Print(L"flag.slash:");
		Println(flag.slash);

		for (auto elem : attacks) {
			elem->draw();
		}
	}
}