#include"Ui.h"

Ui::Ui() :
	hp(100),
	time(1){
	TextureAsset::Register(L"hp", L"Data/UI/hp.png");
	TextureAsset::Register(L"ui", L"Data/UI/ui.png");
	TextureAsset::Register(L"time", L"Data/UI/time.png");
}

void Ui::update(Player player, double time_speed) {
	time = time_speed;
	hp = player.hp;
}

void Ui::draw() const{
	TextureAsset(L"hp")(0, 0, 5.2 * hp + 100, 220).draw();
	TextureAsset(L"time").rotate(Pi / 2.0 * (1 - (time - 0.2) / 0.8)).draw(Vec2(-70, -70));
	TextureAsset(L"ui").draw();
}