#pragma once
#include <Raylib/raylib.h>
#include <Raylib/raymath.h>
#include <Raylib/rlgl.h>

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include "View.hpp"
#include "../Miscellaneous/VectorField.hpp"
#include "../Miscellaneous/Particle.hpp"

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
	VectorField m_vectorfield;
	std::vector<Particle> m_particles;

	bool m_drawGrid;
};