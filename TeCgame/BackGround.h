#pragma once
#include <Siv3D.hpp>
#include"Object.h"
/*
���[�v�w�i�p�̃N���X
Object�N���X����h��
*/
class BackGround{
public:
	BackGround(String _type, Vec2 _moveRate);
	void draw(Vec2 camera)const;
	Vec2 pos;		//�ʒu
	String name;	//���O
	double rot;		//��]�p�x
	Vec2 scale;		//�g��k��
	int alpha;		//�A���t�@�l
private:
	Vec2 moveRate;	//�J�����ɑ΂���ړ�����
};
