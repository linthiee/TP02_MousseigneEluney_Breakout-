#pragma once
#include <string>
#include "Raylib.h"
#include "Draw.h"

namespace powerup
{
	enum class PowerUpType
	{
		None, ExtraBall, DoubleDamage, ExtraPaddles, ShootBall
	};

	struct PowerUp
	{
		PowerUpType powerUpType;

		bool isActive = false;

		int counterInCol = 0;

		float timer = 10.0f;
	};


}

namespace block
{
	struct Block
	{
		powerup::PowerUp block;

		float width = 5;
		float height = 2;

		float posX = 0;
		float posY = 0;

		Color color = WHITE;

		int durability = 3;

		int currentTextureID = 0;

		int score = 0;

	};

	powerup::PowerUpType DecidePowerUpType(int counterInCol);

	void ApplyPowerUpToBlock(Block& block);

	void UpdateDurability(Block& block);

	void Draw(Block block);
}