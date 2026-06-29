#include "View.hpp"

#include <iostream>

View::View(ViewMode mode)
{
	this->mode = mode;

	camera2D.target = { 0, 0 };
	camera2D.offset = { 0, 0 };
	camera2D.rotation = 0;
	camera2D.zoom = 1.0f;

	camera3D.position = { 0, 10, 10 };
	camera3D.target = { 0, 0, 0 };
	camera3D.up = { 0, 1, 0 };
	camera3D.fovy = 90;
	camera3D.projection = CAMERA_PERSPECTIVE;

	m_zoomScale = 1.2f;

	switch (mode)
	{
	case ViewMode::Drag2D:
		break;

	case ViewMode::FREE:
		DisableCursor();
		break;

	case ViewMode::FPS:
		DisableCursor();
		break;
	}
}

void View::update() 
{
	float wheel = GetMouseWheelMove();
	switch (mode)
	{
	case ViewMode::Drag2D:	
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			camera2D.target -= GetMouseDelta() / camera2D.zoom;
		}

		if (wheel != 0)
		{
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera2D);
			
			//Replace the camera
			camera2D.offset = GetMousePosition();
			camera2D.target = mouseWorldPos;
			
			camera2D.zoom = wheel > 0 ? camera2D.zoom * m_zoomScale : camera2D.zoom / m_zoomScale;
		}
		break;

	case ViewMode::FREE:
		UpdateCamera(&camera3D, CAMERA_FREE);
		break;

	case ViewMode::FPS:
		UpdateCamera(&camera3D, CAMERA_FIRST_PERSON);
		break;

	case ViewMode::ORBITAL:
		UpdateCamera(&camera3D, CAMERA_ORBITAL);
		break;
	}
}

void View::gui()
{
	ImGui::SeparatorText("Camera 2D");
	ImGui::InputFloat2("Offset", &camera2D.offset.x);
	ImGui::InputFloat2("Target", &camera2D.target.x);

	ImGui::SeparatorText("Camera 3D");
	ImGui::DragFloat("FOV", &camera3D.fovy);

}