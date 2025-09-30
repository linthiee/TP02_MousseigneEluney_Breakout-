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

bool utils::CheckCollisions(float posX, float posY, float width, float height, float radius, float cursorX, float cursorY)
{
	float edgesX = cursorX;
	float edgesY = cursorY;

	if (cursorX < posX - (width / 2))
	{
		edgesX = posX - (width / 2);
	}
	else if (cursorX > posX + (width / 2))
	{
		edgesX = posX + (width / 2);
	}

	if (cursorY > posY + (height / 2))
	{
		edgesY = posY + (height / 2);
	}
	else if (cursorY < posY - (height / 2))
	{
		edgesY = posY - (height / 2);
	}

	float distX = cursorX - edgesX;
	float distY = cursorY - edgesY;

	float distance = (sqrt)((distX * distX) + (distY * distY));

	if (distance < radius)
	{
		return true;
	}
	return false;

}

bool utils::IsMouseButtonPressed()
{
	if (globals::usingRaylib)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return true;
		}
	}
	else
	{
		if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
		{
			return true;
		}
	}
	return false;
}

