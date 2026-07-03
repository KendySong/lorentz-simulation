#include "Scene.hpp"
#include "../Settings.hpp"

Scene::Scene()
{
	m_view = View(ViewMode::ORBITAL);
	m_vectorfield = VectorField({ 0, 0, 0 }, 100, 3);
	m_drawGrid = false;

	//Create a cloud of particle inside a sphere
	for (size_t i = 0; i < Settings::nbParticles; i++)
	{
		float yaw		= Math::random(0.0f, 2 * PI);
		float pitch		= Math::random(0.0f, 2 * PI);

		Vector3 position = { cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch) };
		position *= Math::random(0.0f, Settings::particleCloudSize);

		m_particles.emplace_back(Particle(position, Math::random(-10, 10), Settings::particleMass));
	}

	//Create static big mass
	m_particles[0].mass = 900;
	m_particles[0].position = { 0, 0, 0 };
	m_particles[0].ray = 1.0f;
}

void Scene::update()
{
	float dt = GetFrameTime();
	handleInput();

	//Add forces
	for (size_t i = 0; i < m_particles.size(); i++)
	{
		for (size_t j = 0; j < m_particles.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			Vector3 direction = Math::normalize(m_particles[j].position - m_particles[i].position);
			m_particles[i].accelerationBack = m_particles[i].acceleration;
			m_particles[i].acceleration += direction * Settings::G * (m_particles[i].mass * m_particles[j].mass) / Math::clamp(1000, 10000, pow(Math::distance(m_particles[i].position, m_particles[j].position), 2));
		}
	}

	//Update position
	for (size_t i = 1; i < m_particles.size(); i++)
	{
		m_particles[i].position += dt * m_particles[i].velocity + ((dt * dt) / 2) * m_particles[i].acceleration;
		m_particles[i].velocity += (dt / 2) * (m_particles[i].acceleration + m_particles[i].accelerationBack);

		//Add limit sphere
		if (Math::length(m_particles[i].position) >= 100)
		{		
			m_particles[i].position = Math::normalize(m_particles[i].position) * (100.0f - m_particles[i].ray);
			//m_particles[i].velocity = Math::reflect(m_particles[i].velocity, m_particles[i].position);
			m_particles[i].velocity = -m_particles[i].velocity * 0.8f;
		}
	}
}


void Scene::render()
{
	ClearBackground({ 30, 30, 30 });

	BeginMode3D(m_view.camera3D);
		if (m_drawGrid)
		{
			DrawGrid(20, 25.0f);
		}

		for (size_t i = 0; i < m_particles.size(); i++)
		{
			m_particles[i].draw();
		}

		m_vectorfield.draw();
	EndMode3D();
}

void Scene::gui()
{
	ImGui::Begin("Settings");
	ImGui::Text("FPS : %i", GetFPS());
	m_vectorfield.gui();
	m_particles[0].gui();
	m_particles[1].gui();
	m_view.gui();
	ImGui::End();
}

void Scene::handleInput()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		DisableCursor();
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		m_view.update();
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
	{
		EnableCursor();
	}
}