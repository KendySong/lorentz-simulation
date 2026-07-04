#include "Scene.hpp"
#include "../Settings.hpp"

Scene::Scene()
{
	m_view = View(ViewMode::ORBITAL);
	m_vectorfield = VectorField({ 0, 0, 0 }, Settings::sphereBoundRay * 2, 10);
	m_drawGrid = true;
	m_drawBoundaries = true;
	m_drawVectorField = false;

	m_newton = false;
	m_electricField = false;
	m_magneticField = true;

	//Init magnetic field
	m_vectorfield.initGlobalDirection({ 0, 1, 0 });

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

		//Magnetic field
		if (m_magneticField)
		{
			Vector3 lorentz = m_particles[i].charge * Math::cross(m_particles[i].velocity, Math::normalize(m_vectorfield.getField(m_particles[i].position)) * Settings::magneticForce);
			m_particles[i].addForce(lorentz);
		}
	}

	//Update position
	for (size_t i = 0; i < m_particles.size(); i++)
	{
		m_particles[i].position += dt * m_particles[i].velocity + ((dt * dt) / 2) * m_particles[i].acceleration;
		m_particles[i].velocity += (dt / 2) * (m_particles[i].acceleration + m_particles[i].accelerationBack);

		if (Math::length(m_particles[i].velocity) > 200)
		{
			m_particles[i].velocity = Math::normalize(m_particles[i].velocity) * 200;
		}

		if (Math::length(m_particles[i].acceleration) > 200)
		{
			m_particles[i].acceleration = Math::normalize(m_particles[i].acceleration) * 200;
		}

		//Add limit sphere
		if (Math::length(m_particles[i].position) + m_particles[i].ray >= Settings::sphereBoundRay)
		{
			m_particles[i].position = Math::normalize(m_particles[i].position) * (Settings::sphereBoundRay - m_particles[i].ray);

			m_particles[i].velocity = -m_particles[i].velocity * Settings::boundRestitution;
			//m_particles[i].velocity = Math::reflect(m_particles[i].velocity, -m_particles[i].position) * Settings::boundRestitution;
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

		if (m_drawVectorField)
		{
			m_vectorfield.draw();
		}

		if (m_drawBoundaries)
		{
			DrawCircle3D({ 0, 0, 0 }, Settings::sphereBoundRay, { 0, 0, 0 }, 0,   PURPLE);
			DrawCircle3D({ 0, 0, 0 }, Settings::sphereBoundRay, { 0, 1, 0 }, 90,  PURPLE);
			DrawCircle3D({ 0, 0, 0 }, Settings::sphereBoundRay, { 0, 1, 0 }, 45,  PURPLE);
			DrawCircle3D({ 0, 0, 0 }, Settings::sphereBoundRay, { 0, 1, 0 }, 135, PURPLE);
		}

		for (size_t i = 0; i < m_particles.size(); i++)
		{
			m_particles[i].draw();
		}	
		
	EndMode3D();
}

void Scene::gui()
{
	ImGui::Begin("Settings");
		ImGui::Text("FPS : %i", GetFPS());

	ImGui::SeparatorText("Simulation");
		ImGui::DragFloat("G", &Settings::G, 0.1f);
		ImGui::DragFloat("Epsilon", &Settings::epsilon, 0.1f);
		ImGui::DragFloat("Magnetic intensity", &Settings::magneticForce, 0.01f);
		ImGui::DragFloat("Bound ray", &Settings::sphereBoundRay);
		ImGui::DragFloat("Bound restitution", &Settings::boundRestitution, 0.1f);
		ImGui::SeparatorText("Forces");
		ImGui::Checkbox("Newton", &m_newton);
		ImGui::Checkbox("Electric field", &m_electricField);
		ImGui::Checkbox("Magnetic field", &m_magneticField);
		ImGui::SeparatorText("Rendering");
		ImGui::Checkbox("Draw magnetic vector field", &m_drawVectorField);
		ImGui::Checkbox("Draw grid", &m_drawGrid);
		ImGui::Checkbox("Draw boundaries", &m_drawBoundaries);
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