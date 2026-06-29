#include "Window.hpp"
#include "../settings.hpp"

Window Window::s_window;

Window& Window::instance()
{
	return s_window;
}

Window::Window()
{
	InitWindow(Settings::width, Settings::height, "Lorentz Simulation");
	rlImGuiSetup(true);
}

void Window::run()
{
	while (!WindowShouldClose())
	{
		//Update
		m_scene.update();		

		//Render
		BeginDrawing();

		m_scene.render();

		//Gui
		rlImGuiBegin();
			m_scene.gui();
		rlImGuiEnd();
		
		EndDrawing();		
	}

	rlImGuiShutdown();
	CloseWindow();
}