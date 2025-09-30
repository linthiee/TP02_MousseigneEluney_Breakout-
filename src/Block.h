#pragma once
#include <string>
#include "Raylib.h"
#include "Globals.h"
#include "PowerUps.h"
#include "Paddle.h"
#include "Draw.h"

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

	powerup::PowerUpType PowerUpActivaded(paddle::Paddle extraPaddles[globals::extraPaddlesMax], Block& block);

	void ApplyPowerUpToBlock(Block& block);

	bool WinCondition(Block block[globals::maxRows][globals::maxCols]);

	void Draw(Block block);
}