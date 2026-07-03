#pragma once
#include <cstdint>

#include <Raylib/raylib.h>
#include <Raylib/raymath.h>

class Settings
{
public :
    static Settings instance;

    static const std::uint32_t width;
    static const std::uint32_t height;

    static const std::uint32_t nbParticles;
    static const float particleCloudSize;
    static const float minCharge;
    static const float maxCharge;
    static const float particleMass;
    static       float G;

    static       float sphereBoundRay;
    static       float boundRestitution;
    static       float epsilon;

    static       float minClamp;
    static       float maxClamp;
    static       float magneticForce;

private :
    Settings();
};