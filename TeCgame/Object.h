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
	void draw();
	std::shared_ptr<PhysicsBody> bodyP;
	//std::shared_ptr<PhysicsBody> bodyE;
	void use(PhysicsWorld world);
	void disuse();

	bool isUsing;

	Vec2 pos;		//位置
	const String name;	//名前
	double rot;		//回転角度
	Vec2 scale;		//拡大縮小
	int alpha;		//アルファ値
	RectF range;	//範囲
};
