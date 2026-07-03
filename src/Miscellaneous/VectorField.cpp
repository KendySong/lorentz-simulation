#include "VectorField.hpp"

VectorField::VectorField(Vector3 position, float size, int resolution)
{
	m_resolution = resolution;
	arrowLength  = 5;
	m_size = size;

	float spacing = m_size / m_resolution;
	float halfSize = m_size / 2;

	//Init vectors to 0
	field = std::vector<std::vector<std::vector<Arrow>>>(
		m_resolution + 1,
		std::vector<std::vector<Arrow>>(
			m_resolution + 1,
			std::vector<Arrow>(
				m_resolution + 1,
				Arrow())
		)
	);
	
	//Create vectors
	for (size_t z = 0; z <= m_resolution; z++)
	{
		for (size_t y = 0; y <= m_resolution; y++)
		{
			for (size_t x = 0; x <= m_resolution; x++)
			{
				field[x][y][z].position = {
					-halfSize + x * spacing,
					-halfSize + y * spacing,
					-halfSize + z * spacing
				};

				field[x][y][z].position += position;
				field[x][y][z].direction = Math::normalize(field[x][y][z].position);
			}
		}
	}
}

void VectorField::draw()
{
	for (size_t z = 0; z <= m_resolution; z++)
	{
		for (size_t y = 0; y <= m_resolution; y++)
		{
			for (size_t x = 0; x <= m_resolution; x++)
			{				
				DrawLine3D(field[x][y][z].position, field[x][y][z].position + field[x][y][z].direction * arrowLength, GREEN);
			}
		}
	}
}

void VectorField::initGlobalDirection(const Vector3& globalDirection)
{
	float halfSize = m_size / 2;
	float spacing = m_size / m_resolution;

	for (size_t z = 0; z <= m_resolution; z++)
	{
		for (size_t y = 0; y <= m_resolution; y++)
		{
			for (size_t x = 0; x <= m_resolution; x++)
			{
				field[x][y][z].position = {
					-halfSize + x * spacing,
					-halfSize + y * spacing,
					-halfSize + z * spacing
				};

				field[x][y][z].position += position;
				field[x][y][z].direction = Math::normalize(globalDirection);
			}
		}
	}
}

Vector3 VectorField::getField(const Vector3& position)
{


	return { 0, 0, 0 };
}

void VectorField::gui()
{
	ImGui::SeparatorText("Vector field");
	ImGui::DragFloat("Vector length", &arrowLength, 0.1f);
}