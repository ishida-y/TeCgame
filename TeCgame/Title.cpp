#include"Title.h"
#include"GameSystem.h"

void Title::init() {
	TextureAsset::Register(L"title", L"Data/title.png");
	SoundAsset::Register(L"title_bgm", L"Data/music/title_bgm.mp3");
	SoundAsset(L"title_bgm").setLoop(true);
	SoundAsset(L"title_bgm").play();
}

void Title::update() {
	if (GameSystem::get().input.enter.get_clicked() == true) {
		changeScene(L"Action");
		SoundAsset(L"title_bgm").pause(3.0s);
	}
}

void Title::draw() const {
	TextureAsset(L"title").draw();
	if (GameSystem::get().debug) {
		Println(L"Title (click space)");
	}
}
