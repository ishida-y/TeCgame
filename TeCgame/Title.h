#pragma once

#include<Siv3D.hpp>
#include<HamFramework.hpp>

class Title : public SceneManager<String>::Scene
{
public:
	void init() override;

	void update() override;

	void draw() const override;

};