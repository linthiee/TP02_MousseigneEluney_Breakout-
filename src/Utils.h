#pragma once
#include "raylib.h"
#include <iostream>

namespace text
{
	struct Text
	{
		std::string text;

		float posX = 0;
		float posY = 0;

		int fonstSize = 20;
		int spacing = 0;

		Color color = WHITE;

		Font font;
	};
}

float Clamp(float value, float min, float max);
float Magnitude(float x, float y);
void Normalize(float& x, float& y);
void Scale(float& x, float& y, float scalar);
