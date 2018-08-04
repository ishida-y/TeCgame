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
		if (GameSystem::get().debug) {
			Print(L"FPS:");
			Println(Profiler::FPS());
		}
		GameSystem::get().update();
		manager.updateAndDraw();
	}
}
