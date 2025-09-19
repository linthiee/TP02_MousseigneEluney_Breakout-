#include "Block.h"

void block::Draw(Block& block)
{
	if (usingRaylib)
	{
		DrawTexture(block.texture, (block.posX * screenWidth / 100) - block.width / 2, block.posY * screenHeight / 100, block.color);
	}
	else
	{
		slSprite(block.currentTextureID, block.posX * screenWidth / 100, screenHeight - (block.posY * screenHeight / 100), block.width * screenWidth / 100, block.height * screenHeight / 100);
	}
}

void block::UpdateTextures(Block& block)
{

}
