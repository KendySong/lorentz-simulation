#pragma once
template<typename T>
struct Minimax
{
public :
	Minimax() = default;
	Minimax(T min, T max)
    {
        this->min = min;
        this->max = max;
    }

	T min;
	T max;
};