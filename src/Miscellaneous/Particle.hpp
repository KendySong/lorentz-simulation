#pragma once
#include <Raylib/raylib.h>
#include <Raylib/raymath.h>

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

class Particle
{
public :
	Particle(Vector3 position, float charge, float mass);
	void draw();
	void gui();

	float charge;
	Vector3 position;
	Vector3 velocity;
	Vector3 accelerationBack;
	Vector3 acceleration;
	float mass;
	float ray;
	

private :
	Color m_color;
};