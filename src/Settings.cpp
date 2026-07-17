#include "settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const std::uint32_t Settings::width = 1600;
const std::uint32_t Settings::height = 900;

const std::uint32_t Settings::nbParticles	= 40;
const float Settings::particleCloudSize		= 10.0f;
const float Settings::minCharge				=-10.0f;
const float Settings::maxCharge				= 10.0f;
const float Settings::particleMass			= 2.0f;
float Settings::G							= 5.0f;
float Settings::sphereBoundRay				= 100.0f;
float Settings::boundRestitution			= 0.1f;
float Settings::epsilon						= 1.0f;
float Settings::minClamp					= 90000;
float Settings::maxClamp					= 100000;
float Settings::magneticForce				= 1.0f;