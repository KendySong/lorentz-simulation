#include "Scene.hpp"

Scene::Scene()
{
	m_view = View(ViewMode::FREE);
}

void Scene::update()
{
	handleInput();
}


void Scene::render()
{
	ClearBackground(BLACK);
	BeginMode3D(m_view.camera3D);
		DrawGrid(100, 1.0f);
	EndMode3D();
}

void Scene::gui()
{
	ImGui::Begin("Settings");
	ImGui::Text("FPS : %i", GetFPS());
	ImGui::SliderFloat("Zoom", &m_view.camera2D.zoom, 0, 10);

	m_view.gui();
	ImGui::End();
}

void Scene::handleInput()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		DisableCursor();
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		m_view.update();
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
	{
		EnableCursor();
	}
}