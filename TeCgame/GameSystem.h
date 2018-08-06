#pragma once
#include <Siv3D.hpp>


class Button {
public:
	Button(s3d::Key _Xcon, s3d::Key _pad, s3d::Key _key);
	void update();

	bool get_clicked();
	bool get_pressed();
	int32  get_pressedDuration();
	bool get_released();

private:
	bool clicked;
	bool pressed;
	int32  pressedDuration;
	bool released;
	s3d::Key Xcon;
	s3d::Key pad;
	s3d::Key key;

};



class Stick {
public:
	Vec2 R;
	Vec2 L;
	Stick();
	void update(s3d::Key Rup, s3d::Key Rdown, s3d::Key Rright, s3d::Key Rleft, s3d::Key Lup, s3d::Key Ldown, s3d::Key Lright, s3d::Key Lleft);
};



//ボタンを増やすときはBottonのインスタンスを増やし、
//コンストラクタでキー設定を行いアップデートを追加する
class KeyInput {
public:
	Button enter;
	Button back;
	Button jump;
	Button slash;
	Button shoot;
	Button zoomIn;
	Button zoomOut;
	Button menu;
	double triggerR;
	double triggerL;
	Stick stick;

	KeyInput();
	void update();
};



class SoundManager {
public:
	int bgm;
	int se;
	SoundManager();
};



class GameSystem {
public:
	static GameSystem& get() {
		static GameSystem inst;
		return inst;
	}
	void update();
	void drawMenu();
	void updateMenu();

	bool openMenu;

	KeyInput input;
	SoundManager sound;

	static const bool debug;

private:
	GameSystem();
	GameSystem(const GameSystem& r) {}
	GameSystem& operator=(const GameSystem& r) {}
};