#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Action.h"
#include"GameSystem.h"

Action::Action() :
	map(),
	player(map.Pworld),
	enemymanager(),
	camera(player.pos) {

}

void Action::init() {

}

//void Action::updateFadeIn() {
//
//}

void Action::update() {
	if (GameSystem::get().input.enter.clicked == true) {
		changeScene(L"Title");
		return;
	}

	map.update();

	player.update(enemymanager);
	enemymanager.update(player);

	camera.update(player.pos);
}

void Action::draw() const {

	//ç¿ïWïœä∑
	const Transformer2D transformer(Mat3x2::Translate(camera.pos).scale(100.0 * camera.scale, { 640, 360 }), true);

	Println(L"Action (click space)");
	map.draw(camera.pos);
	player.draw();
	enemymanager.draw();
}
