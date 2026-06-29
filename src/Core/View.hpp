#pragma once
#include "ViewMode.hpp"

#include <Raylib/raylib.h>
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
	float m_zoomScale;
};