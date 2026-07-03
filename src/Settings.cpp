#include "settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const std::uint32_t Settings::width = 1600;
const std::uint32_t Settings::height = 900;

const std::uint32_t Settings::nbParticles	= 90;
const float Settings::particleCloudSize		= 1.0f;
const float Settings::minCharge				=-1.0f;
const float Settings::maxCharge				= 10.0f;
const float Settings::particleMass			= 1.0f;
float Settings::G							= 0.25f;
float Settings::sphereBoundRay				= 100.0f;
float Settings::boundRestitution			= 0.1f;
float Settings::epsilon						= 1.0f;
float Settings::minClamp					= 90000;
float Settings::maxClamp					= 100000;