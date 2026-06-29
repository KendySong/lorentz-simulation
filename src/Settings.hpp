#pragma once
#include <cstdint>

class Settings
{
public :
    static Settings instance;

    static const std::uint32_t width;
    static const std::uint32_t height;

private :
    Settings();
};