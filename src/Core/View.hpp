#pragma once
#include "ViewMode.hpp"

#include <Raylib/raylib.h>
#include <Raylib/rlgl.h>
#include <Raylib/raymath.h>
#include <Imgui/imgui.h>

class View
{
public :
	View() = default;
	View(ViewMode mode);
	void update();
	void gui();

	ViewMode mode;

	Camera2D camera2D;
	Camera3D camera3D;

private :
	void updateOrbitalPosition();

	float m_zoomScale;
	float m_sensitivity;

	float m_observationDist;	
	float m_yaw;
	float m_pitch;
};