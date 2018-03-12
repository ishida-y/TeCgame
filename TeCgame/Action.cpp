#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Action.h"
#include"GameSystem.h"

void Action::init() {

}

void Action::update() {
	if (GameSystem::get().input.enter.clicked == true) {
		changeScene(L"Title");
	}
}

void Action::draw() const {
	Println(L"Action (click space)");
}
