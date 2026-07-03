#include "Arrow.hpp"

Arrow::Arrow()
{
    this->position  = { 0, 0, 0 };
    this->direction = { 0, 0, 0 };
}

Arrow::Arrow(Vector3 position, Vector3 direction)
{
    this->position = position;
    this->direction = direction;
}