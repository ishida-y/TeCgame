#pragma once

#include<Siv3D.hpp>
#include<HamFramework.hpp>
#include "Player.h"
#include"Camera.h"
#include"Map.h"


class Action : public SceneManager<String>::Scene {
public:
	Map map;
	Player player;
	CameraManager camera;

	double time_speed;

	Action();
	void init() override;
	//void updateFadeIn() override;
	void update() override;

	void draw() const override;

};