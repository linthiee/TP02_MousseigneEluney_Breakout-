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

bool block::CheckCollisions(Block& block, ball::Ball ball)
{
	float edgesX = ball.posX;
	float edgesY = ball.posY;

	if (ball.posX < block.posX)
	{
		edgesX = block.posX;
	}
	else if (ball.posX > block.posX + block.width)
	{
		edgesX = block.posX + block.width;
	}

	if (ball.posY < block.posY)
	{
		edgesY = block.posY;
	}
	else if (ball.posY > block.posY + block.height)
	{
		edgesY = block.posY + block.height;
	}

	float distX = ball.posX - edgesX;
	float distY = ball.posY - edgesY;

	float distance = (sqrt)((distX * distX) + (distY * distY));

	if (distance <= ball.radius)
	{
		return true;
	}
	return false;
}

void block::UpdateTextures(Block& block)
{

}
