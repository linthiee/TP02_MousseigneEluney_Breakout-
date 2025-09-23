#pragma once
#include <string>
#include "Raylib.h"
#include "Draw.h"

namespace block
{
	struct Block
	{
		float width = 5;
		float height = 2;

		float posX = 0;
		float posY = 0;

		Color color = RED;

		int durability = 3;

		int currentTextureID = 0;

		int score = 0;
	};

	void Draw(Block block);

	void UpdateTextures(Block& block);

	void UpdateDurability(Block& block);
}