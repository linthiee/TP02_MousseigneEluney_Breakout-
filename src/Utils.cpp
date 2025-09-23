#include "Utils.h"

float Clamp(float value, float min, float max)
{
	float result = (value < min) ? min : value;

	if (result > max)
	{
		result = max;
	}

	return result;
}

float Magnitude(float x, float y)
{
	float result = sqrtf((x * x) + (y * y));

	return result;
}

void Normalize(float& x, float& y)
{
	float magnitude = Magnitude(x, y);

	x = x / magnitude;
	y = y / magnitude;
}

void Scale(float& x, float& y, float scalar)
{
	x = x * scalar;
	y = y * scalar;
}

