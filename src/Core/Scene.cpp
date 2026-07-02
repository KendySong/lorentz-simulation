#include "Scene.hpp"

Scene::Scene()
{
	m_view = View(ViewMode::ORBITAL);
	m_cubePosition = { 0, 0, 0 };
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
		DrawCube(m_cubePosition, 10, 10, 10, BLUE);
	EndMode3D();
}

void Scene::gui()
{
	ImGui::Begin("Settings");
	ImGui::Text("FPS : %i", GetFPS());
	ImGui::DragFloat3("Cube positoon", &m_cubePosition.x);

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