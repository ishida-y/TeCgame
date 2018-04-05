#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Select.h"
#include"GameSystem.h"

void Select::init() {

}

void Select::update() {
	if (GameSystem::get().input.enter.get_clicked() == true) {
		changeScene(L"Action");
	}
}

void Select::draw() const {
	Println(L"Select (click space)");
}
