#pragma once
#include<Siv3D.hpp>
#include<Siv3D.hpp>
#include<HamFramework.hpp>
/*
�z�u���镨�̂̃N���X
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

	const Vec2 pos;		//�ʒu
	const String name;	//���O
	const double rot;		//��]�p�x
	const Vec2 scale;		//�g��k��
	const int alpha;		//�A���t�@�l
	//RectF range;	//�͈�
};
