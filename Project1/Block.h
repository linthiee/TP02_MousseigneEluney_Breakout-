#pragma once
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

		int durability = 3;
	};

	void Draw(Block& block);
}