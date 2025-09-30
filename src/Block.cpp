#include "Block.h"

powerup::PowerUpType block::DecidePowerUpType(int counterInCol)
{
	if (counterInCol >= globals::maxPowerUpsPerCol)
	{
		return powerup::PowerUpType::None;
	}

	int probability = rand() % (globals::probRange + globals::minProb);

	if (probability <= globals::shootBallProb)
	{
		return powerup::PowerUpType::ShootBall;
	}
	if (probability <= globals::extraPaddlesProb)
	{
		return powerup::PowerUpType::ExtraPaddles;
	}
	if (probability <= globals::doubleDmgProb)
	{
		return powerup::PowerUpType::TripleDamage;
	}

	return powerup::PowerUpType::None;
}

powerup::PowerUpType block::PowerUpActivaded(paddle::Paddle extraPaddles[globals::extraPaddlesMax], Block& block)
{
	switch (block.block.powerUpType)
	{
	case powerup::PowerUpType::ExtraPaddles:

		for (int i = 0; i < globals::extraPaddlesMax; i++)
		{
			extraPaddles[i].isActive = true;
		}

		return powerup::PowerUpType::ExtraPaddles;

		break;
	case powerup::PowerUpType::TripleDamage:

		return powerup::PowerUpType::TripleDamage;

		break;
	case powerup::PowerUpType::ShootBall:

		return powerup::PowerUpType::ShootBall;

		break;
	case powerup::PowerUpType::None:

		return powerup::PowerUpType::None;

		break;
	default:

		return powerup::PowerUpType::None;

		break;
	}
	return powerup::PowerUpType::None;
}

void block::ApplyPowerUpToBlock(Block& block)
{
	switch (block.block.powerUpType)
	{
	case powerup::PowerUpType::ExtraPaddles:

		block.currentTextureID = globals::extraPaddleBrickTextureID;

		break;
	case powerup::PowerUpType::TripleDamage:

		block.currentTextureID = globals::tripleDamageBrickTextureID;

		break;
	case powerup::PowerUpType::ShootBall:

		block.currentTextureID = globals::shootBallBrickTextureID;

		break;
	case powerup::PowerUpType::None:

		block.currentTextureID = globals::blockNormalTextureID;

		break;
	}
}

bool block::WinCondition(Block block[globals::maxRows][globals::maxCols])
{
	for (int row = 0; row < globals::maxRows; row++)
	{
		for (int col = 0; col < globals::maxCols; col++)
		{
			if (block[row][col].durability > 0)
			{
				return false;
			}
		}
	}
	return true;
}

void block::Draw(Block block)
{
	draw::DrawSprite(block.currentTextureID, block.posX, block.posY, block.width, block.height, block.color);
}