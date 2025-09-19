#pragma once
#include <string>
#include <iostream>
#include "Raylib.h"
#include "Draw.h"

namespace block
{
	struct Block
	{
		int width = 5;
		int height = 2;

		float posX = 0;
		float posY = 0;

		Color color = RED;

		std::string currentTexture = "res/Brick_Texture_Default.png";
		int currentTextureID = 0;

		Texture texture;

		int durability = 3;
	};

	void Draw(Block& block);
	void UpdateTextures(Block& block);
}