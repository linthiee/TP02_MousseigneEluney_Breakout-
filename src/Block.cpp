#include "Block.h"

void block::Draw(Block block)
{
	DrawSprite(block.currentTextureID, block.posX, block.posY, block.width, block.height, block.color);
}

void block::UpdateTextures(Block& block)
{

}

void block::UpdateDurability(Block& block)
{
	block.color.r /= 1.25f;
	block.color.g /= 1.25f;
	block.color.b /= 1.25f;
	//block.color.a /= 1.5f;
	if (block.durability > 0)
	{
		block.durability--;
	}
}
