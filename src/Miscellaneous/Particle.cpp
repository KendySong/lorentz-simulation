#include "Particle.hpp"

Particle::Particle(Vector3 position, float charge, float mass)
{
	this->position = position;
	this->charge = charge;
	this->mass = mass;
	this->velocity = { 0, 0, 0 };
	this->acceleration = { 0, 0, 0 };
	this->accelerationBack = { 0, 0, 0 };
	this->ray = 0.9f;

	m_color = charge < 0 ? BLUE : RED;
}

void Particle::draw()
{
	//DrawPoint3D(position, m_color);
	DrawSphere(position, this->ray, m_color);
}

void Particle::gui()
{
	ImGui::DragFloat3("Position", &position.x, 0.01f);
	ImGui::DragFloat3("Velocity", &velocity.x, 0.01f);
	ImGui::DragFloat("Charge", &charge, 0.1f);
}

void Particle::addForce(const Vector3& force)
{
	this->acceleration += force / mass;
}