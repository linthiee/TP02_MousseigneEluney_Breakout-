#pragma once

namespace powerup
{
	enum class PowerUpType
	{
		None, TripleDamage, ExtraPaddles, ShootBall
	};

	struct PowerUp
	{
		PowerUpType powerUpType;

		bool isActive = false;

		int counterInCol = 0;

		float timer = 10.0f;
	};
}
