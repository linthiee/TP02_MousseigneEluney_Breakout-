#pragma once
#include <iostream>
#include "raylib.h"

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

namespace buttons
{
	struct Button
	{

		float posX = 0;
		float posY = 0;

		int width = 5;
		int height = 6;

		Color color = WHITE;

		int currentTextureID = 0;

		bool isMuted = false;
	};
}

float Clamp(float value, float min, float max);
float Magnitude(float x, float y);
void Normalize(float& x, float& y);
void Scale(float& x, float& y, float scalar);
