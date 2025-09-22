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
	if (block.durability > 0)
	{
		block.durability--;
	}
}
