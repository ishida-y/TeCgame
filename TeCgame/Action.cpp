#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Action.h"
#include"GameSystem.h"

Action::Action() :
	map(),
	player(map.Pworld),
	enemymanager(),
	camera(player.pos),
	time_speed(1.0){

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
	Println(time_speed);
	map.update(time_speed);

	player.update(enemymanager, map.obj, time_speed);
	enemymanager.update(player, map.obj);

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
