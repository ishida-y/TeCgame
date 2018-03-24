#pragma once
#include<Siv3D.hpp>

class CameraManager {
public:
	CameraManager(Vec2 player);
	void update(Vec2 player);

	Vec2 pos;
	double scale;

private:
	Vec2 t_pos;
	double t_scale;
	double ease;
};