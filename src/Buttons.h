#pragma once
#include "raylib.h"

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
