#include "Utils.h"

float utils::Clamp(float value, float min, float max)
{
	float result = (value < min) ? min : value;

	if (result > max)
	{
		result = max;
	}

	return result;
}

float utils::Magnitude(float x, float y)
{
	float result = sqrtf((x * x) + (y * y));

	return result;
}

void utils::Normalize(float& x, float& y)
{
	float magnitude = utils::Magnitude(x, y);

	x = x / magnitude;
	y = y / magnitude;
}

void utils::Scale(float& x, float& y, float scalar)
{
	x = x * scalar;
	y = y * scalar;
}

