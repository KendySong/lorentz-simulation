#include "settings.hpp"

Settings Settings::instance;

Settings::Settings()
{

}

const std::uint32_t Settings::width = 1600;
const std::uint32_t Settings::height = 900;

const std::uint32_t Settings::nbParticles	= 90;
const float Settings::particleCloudSize		= 10.0f;
const float Settings::minCharge				=-10.0f;
const float Settings::maxCharge				= 10.0f;
const float Settings::particleMass			= 1.0f;
const float Settings::G						= 1.0f;