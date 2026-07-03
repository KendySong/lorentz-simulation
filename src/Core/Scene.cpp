#include "Scene.hpp"
#include "../Settings.hpp"

Scene::Scene()
{
	m_view = View(ViewMode::ORBITAL);
	m_vectorfield = VectorField({ 0, 0, 0 }, 100, 3);
	m_drawGrid = false;

	m_newton = true;
	m_electricField = true;
	m_magneticField = true;

	//Create a cloud of particle inside a sphere
	for (size_t i = 0; i < Settings::nbParticles; i++)
	{
		float yaw = Math::random(0.0f, 2 * PI);
		float pitch = Math::random(0.0f, 2 * PI);

		Vector3 position = { cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch) };
		position *= Math::random(0.0f, Settings::particleCloudSize);

		m_particles.emplace_back(Particle(position, Math::random(Settings::minCharge, Settings::maxCharge), Settings::particleMass));
	}

	m_distClamp = Minimax<float>(Settings::minClamp, Settings::maxClamp);

	m_particles[0].ray = 1.2f;
	m_particles[0].charge = 3000;
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
			float r = Math::distance(m_particles[i].position, m_particles[j].position);
			m_particles[i].accelerationBack = m_particles[i].acceleration;
			float rSquare = pow(r, 2);

			//Newton
			if (m_newton)
			{
				float newtonForce = Settings::G * (m_particles[i].mass * m_particles[j].mass) /
					Math::clamp(
						m_distClamp.min,
						m_distClamp.max,
						rSquare
					);
				m_particles[i].addForce(direction * newtonForce);
			}
			
			//Electric field
			if (m_electricField)
			{
				float electricField = m_particles[j].charge / 
					Math::clamp(
						m_distClamp.min,
						m_distClamp.max,
						(4 * PI * Settings::epsilon * rSquare)
					);
				float electricForce = m_particles[i].charge * electricField;
				m_particles[i].addForce(electricForce * (-direction));
			}
			

		}
	}

	//Update position
	for (size_t i = 0; i < m_particles.size(); i++)
	{
		m_particles[i].position += dt * m_particles[i].velocity + ((dt * dt) / 2) * m_particles[i].acceleration;
		m_particles[i].velocity += (dt / 2) * (m_particles[i].acceleration + m_particles[i].accelerationBack);

		//Add limit sphere
		if (Math::length(m_particles[i].position) >= Settings::sphereBoundRay)
		{		
			m_particles[i].position = Math::normalize(m_particles[i].position) * (Settings::sphereBoundRay - m_particles[i].ray);
			m_particles[i].velocity = -m_particles[i].velocity * Settings::boundRestitution;
			m_particles[i].acceleration = -m_particles[i].acceleration * Settings::boundRestitution;
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

	ImGui::SeparatorText("Simulation");
		ImGui::DragFloat("G", &Settings::G, 0.1f);
		ImGui::DragFloat("Epsilon", &Settings::epsilon, 0.1f);
		ImGui::DragFloat("Bound ray", &Settings::sphereBoundRay);
		ImGui::DragFloat("Bound restitution", &Settings::boundRestitution, 0.1f);
		ImGui::Checkbox("Newton", &m_newton);
		ImGui::Checkbox("Electric field", &m_electricField);
		ImGui::Checkbox("Magnetic field", &m_magneticField);
		m_vectorfield.gui();
		m_particles[0].gui();

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