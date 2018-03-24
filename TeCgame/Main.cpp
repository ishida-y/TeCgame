
#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Title.h"
#include"Action.h"
#include"Select.h"
#include"GameSystem.h"


void Main()
{
	Window::Resize(1280, 720);

	SceneManager<String> manager;

	manager.add<Title>(L"Title");
	manager.add<Action>(L"Action");
	manager.add<Select>(L"Select");

	while (System::Update())
	{
		ClearPrint();
		GameSystem::get().update();
		manager.updateAndDraw();
	}
}