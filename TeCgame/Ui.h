#pragma once
#include "Player.h"

class Ui {
public:
	Ui();
	void update(Player player, double time_speed);
	void draw() const;
	double hp;
	double time;
};