#pragma once
#include <Siv3D.hpp>


class Button {
public:
	bool clicked;
	bool pressed;
	int32  pressedDuration;
	bool released;
	s3d::Key Xcon;
	s3d::Key pad;
	s3d::Key key;

	Button(s3d::Key _Xcon, s3d::Key _pad, s3d::Key _key);
	void update();
private:

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
	Button janp;
	Button zoomIn;
	Button zoomOut;
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

	KeyInput input;
	SoundManager sound;

	static const bool debug;

private:
	GameSystem();
	GameSystem(const GameSystem& r) {}
	GameSystem& operator=(const GameSystem& r) {}
};