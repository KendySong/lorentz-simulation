#include "View.hpp"

View::View(ViewMode mode)
{
	this->mode = mode;

	camera2D.target = { 0, 0 };
	camera2D.offset = { 0, 0 };
	camera2D.rotation = 0;
	camera2D.zoom = 1.0f;

	camera3D.position = { 0, 0, 0};
	camera3D.target = { 0, 0, 0 };
	camera3D.up = { 0, 1, 0 };
	camera3D.fovy = 90;
	camera3D.projection = CAMERA_PERSPECTIVE;

	m_zoomScale			= 1.2f;
	m_sensitivity		= 0.5f;
	m_observationDist	= 20;
	m_yaw				= 0.3;
	m_pitch				= 0.7;

	switch (mode)
	{	
	case ViewMode::FREE:
		DisableCursor();
		break;

	case ViewMode::FPS:
		DisableCursor();
		break;

	case ViewMode::ORBITAL:
		DisableCursor();
		updateOrbitalPosition();
		break;
	}
}

void View::update() 
{
	float wheel = GetMouseWheelMove();
	Vector2 mouseDelta = GetMouseDelta() * m_sensitivity;

	switch (mode)
	{
	case ViewMode::Drag2D:	
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			camera2D.target -= mouseDelta / camera2D.zoom;
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
		if (wheel != 0)
		{
			m_observationDist = wheel > 0 ? m_observationDist / m_zoomScale : m_observationDist * m_zoomScale;
		}
	
		//Update camera position around origin
		mouseDelta *= DEG2RAD;
		m_yaw	+= mouseDelta.x;
		m_pitch += mouseDelta.y;

		m_pitch = m_pitch > PI / 2 ? PI / 2 : m_pitch < -PI / 2 ? -PI / 2 : m_pitch;
		this->updateOrbitalPosition();
		
		UpdateCameraPro(&camera3D, { 0, 0, 0 }, { 0, 0, 0 }, 0.0f);
		break;
	}
}

void View::gui()
{
	if (ImGui::TreeNode("Camera"))
	{
		ImGui::DragFloat("Sensitivity", &m_sensitivity, 0.01f);
		ImGui::DragFloat("Zoom scale", &m_zoomScale);

		ImGui::SeparatorText("Camera 2D");
		ImGui::SliderFloat("Zoom", &camera2D.zoom, 0, 10);

		ImGui::SeparatorText("Camera 3D");
		ImGui::DragFloat("FOV", &camera3D.fovy);
		ImGui::TreePop();
	}
	
}

void View::updateOrbitalPosition()
{
	camera3D.position.x = cos(m_yaw) * cos(m_pitch);
	camera3D.position.y = sin(m_pitch);
	camera3D.position.z = sin(m_yaw) * cos(m_pitch);
	camera3D.position *= m_observationDist;
}