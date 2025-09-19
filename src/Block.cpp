#include "Block.h"

void block::Draw(Block& block)
{
	if (usingRaylib)
	{
		block.texture = LoadTexture(block.currentTexture.c_str());
		DrawTexture(block.texture, block.posX * screenWidth / 100, block.posY * screenHeight / 100, block.color);
	}
	else
	{
		block.currentTexture = slLoadTexture(block.currentTexture.c_str());
	}
}

void block::InitTextures(Block block[maxRows][maxCols])
{
	for (int row = 0; row < maxRows; row++)
	{
		for (int col = 0; col < maxCols; col++)
		{
			if (usingRaylib)
			{
				std::cout << block[row][col].currentTexture << std::endl;
				block[row][col].texture = LoadTexture(block[row][col].currentTexture.c_str());

				block[row][col].texture.width = block[row][col].width * screenWidth / 100;
				block[row][col].texture.height = block[row][col].height * screenHeight / 100;
			}
			else
			{
				block[row][col].currentTexture = slLoadTexture(block[row][col].currentTexture.c_str());
			}
		}
	}
}
