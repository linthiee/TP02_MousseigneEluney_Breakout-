#include "Block.h"

void block::Draw(Block& block)
{
	DrawRec(block.posX * screenWidth / 100, block.posY * screenHeight / 100, block.width * screenWidth / 100, block.height * screenHeight / 100, block.color);
}