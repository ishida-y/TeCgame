#pragma once
#include<Siv3D.hpp>
#include<Siv3D.hpp>
#include<HamFramework.hpp>
/*
配置する物体のクラス
*/

class Object {
public:
	Object(String _name, Vec2 _pos, double _rot = 0.0, Vec2 _scale = Vec2(1.0, 1.0), int _alpha = 255);
	virtual ~Object() {
	}
	/*
	void draw();
	void update();
	void use();
	void disuse();
	*/
	bool isUsing;

	const Vec2 pos;		//位置
	const String name;	//名前
	const double rot;		//回転角度
	const Vec2 scale;		//拡大縮小
	const int alpha;		//アルファ値
	//RectF range;	//範囲
};
