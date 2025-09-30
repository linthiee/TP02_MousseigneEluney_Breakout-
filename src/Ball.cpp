#include "Ball.h"

void ball::Draw(Ball ball)
{
	draw::DrawCirc(ball.posX, ball.posY, ball.radius, BLACK);
	draw::DrawSprite(ball.currentTextureID, ball.posX, ball.posY, (ball.radius), 16.0f * (ball.radius) / 9.0f, ball.color);
}

void ball::ShootBall(Ball& ball, paddle::Paddle& paddle)
{
	bool shoot = false;
	int upKey = 0;

	if (!ball.firstShoot)
	{
		return;
	}

	ball.posX = paddle.posX;
	ball.posY = paddle.posY - (paddle.height / 2) - ball.radius;

	if (globals::usingRaylib)
	{
		switch (paddle.keyUp)
		{
		case globals::Key::NONE_KEY:
			break;
		case globals::Key::LEFT_KEY:

			upKey = (int)KeyboardKey::KEY_LEFT;

			break;
		case globals::Key::RIGHT_KEY:

			upKey = (int)KeyboardKey::KEY_RIGHT;

			break;
		case globals::Key::UP_KEY:

			upKey = (int)(KeyboardKey::KEY_UP);

			break;
		default:
			break;
		}
		if (IsKeyDown(upKey))
		{
			shoot = true;
		}
	}
	else
	{
		switch (paddle.keyUp)
		{
		case globals::Key::NONE_KEY:
			break;
		case globals::Key::LEFT_KEY:

			upKey = SL_KEY_LEFT;

			break;
		case globals::Key::RIGHT_KEY:

			upKey = SL_KEY_RIGHT;

			break;
		case globals::Key::UP_KEY:

			upKey = SL_KEY_UP;

			break;
		default:
			break;
		}
		if (slGetKey(upKey))
		{
			shoot = true;
		}
	}

	if (shoot)
	{
		ball.velocityY = -1;
		ball.velocityX = 1;

		float direction = rand() % ((globals::maxDirecBall - globals::minDirecBall + 1) + globals::minDirecBall);

		direction -= globals::maxDirecBall / 2;

		ball.velocityX = direction / 10.0f;

		if (paddle.powerUpType == powerup::PowerUpType::ShootBall)
		{
			ball.velocityX = direction / 100.0f;
			ball.velocityY = -1;
		}
		utils::Normalize(ball.velocityX, ball.velocityY);

		ball.firstShoot = false;
		ball.idle = false;

		paddle.powerUpType = powerup::PowerUpType::None;
	}
}

void ball::Movement(Ball& ball)
{
	if (!ball.idle)
	{
		utils::Normalize(ball.velocityX, ball.velocityY);

		ball.posX += ball.velocityX * ball.speed * globals::deltaT;
		ball.posY += ball.velocityY * ball.speed * globals::deltaT;

		if (ball.posX + ball.radius > 100)
		{
			ball.posX = 100 - ball.radius;
			ball.velocityX *= -1;
		}
		if (ball.posX - ball.radius < 0)
		{
			ball.posX = ball.radius;
			ball.velocityX *= -1;
		}

		if (ball.posY + ball.radius > 100.0f)
		{
			ball.posY = 100 - ball.radius;
			ball.velocityY *= -1;
		}
		if (ball.posY - ball.radius < 0)
		{
			ball.posY = ball.radius;
			ball.velocityY *= -1;
		}
	}
}


bool ball::CheckCollisions(float posX, float posY, float width, float height, ball::Ball ball)
{
	float edgesX = ball.posX;
	float edgesY = ball.posY;

	if (ball.posX < posX - (width / 2))
	{
		edgesX = posX - (width / 2);
	}
	else if (ball.posX > posX + (width / 2))
	{
		edgesX = posX + (width / 2);
	}

	if (ball.posY > posY + (height / 2))
	{
		edgesY = posY + (height / 2);
	}
	else if (ball.posY < posY - (height / 2))
	{
		edgesY = posY - (height / 2);
	}

	float distX = ball.posX - edgesX;
	float distY = ball.posY - edgesY;

	float distance = (sqrt)((distX * distX) + (distY * distY));

	if (distance < ball.radius)
	{
		return true;
	}
	return false;
}

bool ball::CheckCollisions(block::Block& block, ball::Ball ball)
{
	return CheckCollisions(block.posX, block.posY, block.width, block.height, ball);
}

bool ball::CheckCollisions(paddle::Paddle& paddle, ball::Ball ball)
{
	return CheckCollisions(paddle.posX, paddle.posY, paddle.width, paddle.height, ball);
}

void ball::UpdateBlockDurability(block::Block& block, int damage)
{
	block.color.r /= 1.25f;
	block.color.g /= 1.25f;
	block.color.b /= 1.25f;

	if (block.durability > 0)
	{
		block.durability -= damage;
	}
}

void ball::CollidedPaddle(paddle::Paddle& paddle, Ball& ball)
{
	if (paddle.powerUpType == powerup::PowerUpType::ShootBall)
	{
		ball.firstShoot = true;
		ball.idle = true;

		return;
	}

	if (ball.posY < paddle.posY)
	{
		ball.posY = paddle.posY - (paddle.height / 2) - ball.radius;
		ball.velocityY = -1.0f;
	}
	else
	{
		ball.posY = paddle.posY + (paddle.height / 2) + ball.radius;
		ball.velocityY = 1.0f;
	}

	ball.velocityX = (ball.posX - paddle.posX) / (paddle.width / 2);
	utils::Normalize(ball.velocityX, ball.velocityY);
}

void ball::UpdateMovement(Ball& ball, block::Block block)
{
	if (ball.posY < block.posY)
	{
		ball.posY = block.posY - (block.height / 2) - ball.radius;
		ball.velocityY = -1.0f;
	}
	else
	{
		ball.posY = block.posY + (block.height / 2) + ball.radius;
		ball.velocityY = 1.0f;
	}

	if (ball.posX < block.posX - (block.width / 2))
	{
		ball.posX = block.posX - (block.width / 2) - ball.radius;
		ball.velocityX = -1.0f;
	}
	else if (ball.posX > block.posX + (block.width / 2))
	{
		ball.posX = block.posX + (block.width / 2) + ball.radius;
		ball.velocityX = 1.0f;
	}
}

void ball::UpdateOnLivesLost(Ball& ball, paddle::Paddle& paddle)
{
	if (ball.posY + ball.radius >= 100.0f)
	{
		paddle.lives--;

		paddle.posX = 50;
		paddle.posY = 95;

		ball.posX = paddle.posX;
		ball.posY = paddle.posY - (paddle.height / 2) - ball.radius;

		ball.firstShoot = true;
		ball.idle = true;
	}
}

void ball::UpdatePowerUp(paddle::Paddle& paddle, paddle::Paddle extraPaddles[globals::extraPaddlesMax], Ball& ball)
{
	int paddlesActive = 0;

	switch (paddle.powerUpType)
	{
	case powerup::PowerUpType::ExtraPaddles:

		for (int i = 0; i < globals::extraPaddlesMax; i++)
		{
			if (CheckCollisions(extraPaddles[i], ball))
			{
				if (extraPaddles[i].isActive)
				{
					extraPaddles[i].isActive = false;
					CollidedPaddle(extraPaddles[i], ball);
				}
			}
		}

		for (int i = 0; i < globals::extraPaddlesMax; i++)
		{
			if (extraPaddles[i].isActive)
			{
				paddlesActive++;
			}
		}

		if (paddlesActive == 0)
		{
			paddle.powerUpType = powerup::PowerUpType::None;
		}

		break;
	case powerup::PowerUpType::TripleDamage:

		ball.damage = 3;

		break;
	case powerup::PowerUpType::ShootBall:

		break;
	case powerup::PowerUpType::None:

		break;
	default:

		break;
	}
}