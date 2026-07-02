#pragma once
#include <Raylib/raylib.h>
#include <Raylib/raymath.h>
#include <Raylib/rlgl.h>

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include "View.hpp"

class Scene
{
public :
	Scene();

	void update();
	void gui();
	void render();
	void handleInput();

private :
	View m_view;

	Vector3 m_cubePosition;
};