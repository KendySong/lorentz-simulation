#pragma once
#include <Raylib/raymath.h>

struct Arrow
{
public :
    Arrow();
    Arrow(Vector3 position, Vector3 direction);
    Vector3 position;
    Vector3 direction;

private :
};