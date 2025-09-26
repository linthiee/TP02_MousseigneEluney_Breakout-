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
		return powerup::PowerUpType::DoubleDamage;
	}
	if (probability <= globals::extraBallProb)
	{
		return powerup::PowerUpType::ExtraBall;
	}

	return powerup::PowerUpType::None;
}

powerup::PowerUpType block::PowerUpActivaded(Block& block)
{
	switch (block.block.powerUpType)
	{
	case powerup::PowerUpType::ExtraBall:

		std::cout << "Power up active!";
		return powerup::PowerUpType::ExtraBall;

		break;
	case powerup::PowerUpType::ExtraPaddles:
		
		std::cout << "Power up active!";

		return powerup::PowerUpType::ExtraPaddles;

		break;
	case powerup::PowerUpType::DoubleDamage:

		std::cout << "Power up active!";

		return powerup::PowerUpType::DoubleDamage;

		break;
	case powerup::PowerUpType::ShootBall:
		std::cout << "Power up active!";

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
	case powerup::PowerUpType::ExtraBall:

		block.color = BLACK;

		break;
	case powerup::PowerUpType::ExtraPaddles: 

		block.color = BLACK;

		break;
	case powerup::PowerUpType::DoubleDamage: 

		block.color = BLACK;

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
	draw::DrawSprite(block.currentTextureID, block.posX, block.posY, block.width, block.height, block.color);
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