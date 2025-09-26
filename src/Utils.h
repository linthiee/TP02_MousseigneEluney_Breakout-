#pragma once
#include <iostream>
#include "raylib.h"

namespace utils
{
	float Clamp(float value, float min, float max);
	float Magnitude(float x, float y);
	void Normalize(float& x, float& y);
	void Scale(float& x, float& y, float scalar);
}
