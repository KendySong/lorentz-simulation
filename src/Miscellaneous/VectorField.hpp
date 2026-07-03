#pragma once
#include <vector>
#include <Raylib/raylib.h>
#include <Raylib/raymath.h>

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

#include "../Core/Math.hpp"
#include "Arrow.hpp"

class VectorField
{
public :
	VectorField() = default;
	VectorField(Vector3 position, float size, int resolution);
	void draw();
	void initGlobalDirection(const Vector3& globalDirection);
	Vector3 getField(const Vector3& position);
	void gui();

	std::vector<std::vector<std::vector<Arrow>>> field;
	Vector3 position;
	float arrowLength;

private :
	int m_resolution;
	float m_size;
};