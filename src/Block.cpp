#include "Block.h"

powerup::PowerUpType block::DecidePowerUpType(int counterInCol)
{
	if (counterInCol >= maxPowerUpsPerCol)
	{
		return powerup::PowerUpType::None;
	}

	int probability = rand() % (probRange + minProb);

	if (probability <= shootBallProb)
	{
		return powerup::PowerUpType::ShootBall;
	}
	if (probability <= extraPaddlesProb)
	{
		return powerup::PowerUpType::ExtraPaddles;
	}
	if (probability <= doubleDmgProb)
	{
		return powerup::PowerUpType::DoubleDamage;
	}
	if (probability <= extraBallProb)
	{
		return powerup::PowerUpType::ExtraBall;
	}

	return powerup::PowerUpType::None;
}

void block::ApplyPowerUpToBlock(Block& block)
{
	switch (block.block.powerUpType)
	{
	case powerup::PowerUpType::ExtraBall:
		block.color = PINK; 
		break;
	case powerup::PowerUpType::ExtraPaddles: 
		block.color = WHITE;
		break;
	case powerup::PowerUpType::DoubleDamage: 
		block.color = BLUE;
		break;
	case powerup::PowerUpType::ShootBall:
		block.color = BLACK;
		break;
	case powerup::PowerUpType::None:    
		break;
	}
}

void block::Draw(Block block)
{
	DrawSprite(block.currentTextureID, block.posX, block.posY, block.width, block.height, block.color);
}

void block::UpdateDurability(Block& block)
{
	block.color.r /= 1.25f;
	block.color.g /= 1.25f;
	block.color.b /= 1.25f;

	if (block.durability > 0)
	{
		block.durability--;
	}
}
