#include "Block.h"

void block::Draw(Block& block)
{
	if (usingRaylib)
	{
		DrawTexture(block.texture, (block.posX * screenWidth / 100) - (block.width * screenWidth / 100) / 2, (block.posY * screenHeight / 100) + (offset * screenHeight / 100), block.color);
	}
	else
	{
		double r = (double)block.color.r / 128;
		double g = (double)block.color.g / 128;
		double b = (double)block.color.b / 128;
		double a = (double)block.color.a / 128;

		slSetForeColor(r, g, b, a);

		slSprite(block.currentTextureID, block.posX * screenWidth / 100, screenHeight - (block.posY * screenHeight / 100) - (offset * screenHeight / 100), block.width * screenWidth / 100, block.height * screenHeight / 100);
	}
}

void block::UpdateTextures(Block& block)
{

}
