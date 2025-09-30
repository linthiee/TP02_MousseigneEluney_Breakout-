#pragma once
#include <iostream>
#include "raylib.h"
#include "sl.h"
#include "Globals.h"

namespace utils
{
	float Clamp(float value, float min, float max);
	float Magnitude(float x, float y);
	void Normalize(float& x, float& y);
	void Scale(float& x, float& y, float scalar);
	bool CheckCollisions(float posX, float posY, float width, float height, float radius, float cursorX, float cursorY);
	bool IsMouseButtonPressed();
}
