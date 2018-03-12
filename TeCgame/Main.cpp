
#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Title.h"
#include"Action.h"
#include"Select.h"
#include"GameSystem.h"


void Main()
{

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
