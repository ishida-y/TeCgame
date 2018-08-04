#pragma once
#include <Siv3D.hpp>
#include"Object.h"
/*
ループ背景用のクラス
Objectクラスから派生
*/
class BackGround{
public:
	BackGround(String _type, Vec2 _moveRate);
	void draw(Vec2 camera)const;
	Vec2 pos;		//位置
	String name;	//名前
	double rot;		//回転角度
	Vec2 scale;		//拡大縮小
	int alpha;		//アルファ値
private:
	Vec2 moveRate;	//カメラに対する移動割合
};
