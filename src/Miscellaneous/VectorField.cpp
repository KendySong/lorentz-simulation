#include "VectorField.hpp"

VectorField::VectorField(Vector3 position, float size, int resolution)
{
	this->m_resolution = resolution;
	this->m_size = size;
	this->position = position;
	this->arrowLength = 5;

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
				DrawCircle3D(field[x][y][z].position + field[x][y][z].direction, 1, { 0, 0, 0 }, 0, PURPLE);
				DrawCircle3D(field[x][y][z].position + field[x][y][z].direction, 1, { 0, 1, 0 }, 90, PURPLE);
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
	Vector3 local = position - this->position;

	float spacing = m_size / m_resolution;
	float halfSize = m_size * 0.5f;

	int x = std::round((local.x + halfSize) / spacing);
	int y = std::round((local.y + halfSize) / spacing);
	int z = std::round((local.z + halfSize) / spacing);

	x = Math::clamp(0, m_resolution, x);
	y = Math::clamp(0, m_resolution, y);
	z = Math::clamp(0, m_resolution, z);

	return field[x][y][z].direction;
}

void VectorField::gui()
{
	ImGui::SeparatorText("Vector field");
	ImGui::DragFloat("Vector length", &arrowLength, 0.1f);
}