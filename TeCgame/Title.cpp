#include"Title.h"
#include"GameSystem.h"

void Title::init() {
	TextureAsset::Register(L"title", L"Data/title.png");
}

void Title::update() {
	if (GameSystem::get().input.enter.get_clicked() == true) {
		changeScene(L"Action");
	}
}

void Title::draw() const {
	TextureAsset(L"title").draw();
	if (GameSystem::get().debug) {
		Println(L"Title (click space)");
	}
}
