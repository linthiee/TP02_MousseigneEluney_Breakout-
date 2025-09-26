#include "Paddle.h"

void paddle::Draw(Paddle paddle)
{
	draw::DrawSprite(paddle.currentTextureID, paddle.posX, paddle.posY, paddle.width, paddle.height, paddle.color);
}

void paddle::Movement(Paddle& paddle)
{
	int leftKey = 0;
	int rightKey = 0;

	if (globals::usingRaylib)
	{
		switch (paddle.keyLeft)
		{
		case globals::Key::NONE_KEY:
			break;
		case globals::Key::LEFT_KEY:

			leftKey = (int)KeyboardKey::KEY_LEFT;

			break;
		case globals::Key::RIGHT_KEY:

			leftKey = (int)KeyboardKey::KEY_RIGHT;

			break;
		case globals::Key::UP_KEY:

			leftKey = (int)(KeyboardKey::KEY_UP);

			break;
		default:
			break;
		}

		if (IsKeyDown(leftKey))
		{
			paddle.posX -= paddle.speed * globals::deltaT;
		}

		switch (paddle.keyRight)
		{
		case globals::Key::NONE_KEY:
			break;
		case globals::Key::LEFT_KEY:

			rightKey = (int)KeyboardKey::KEY_LEFT;

			break;
		case globals::Key::RIGHT_KEY:

			rightKey = (int)(KeyboardKey::KEY_RIGHT);

			break;
		case globals::Key::UP_KEY:

			rightKey = (int)(KeyboardKey::KEY_UP);

			break;
		default:
			break;
		}

		if (IsKeyDown(rightKey))
		{
			paddle.posX += paddle.speed * globals::deltaT;
		}
	}
	else
	{
		switch (paddle.keyLeft)
		{
		case globals::Key::NONE_KEY:
			break;
		case globals::Key::LEFT_KEY:

			leftKey = SL_KEY_LEFT;

			break;
		case globals::Key::RIGHT_KEY:

			leftKey = SL_KEY_RIGHT;

			break;
		case globals::Key::UP_KEY:

			leftKey = SL_KEY_UP;

			break;
		default:
			break;
		}

		if (slGetKey(leftKey))
		{
			paddle.posX -= paddle.speed * globals::deltaT;
		}

		switch (paddle.keyRight)
		{
		case globals::Key::NONE_KEY:
			break;
		case globals::Key::LEFT_KEY:

			rightKey = SL_KEY_LEFT;

			break;
		case globals::Key::RIGHT_KEY:

			rightKey = SL_KEY_RIGHT;

			break;
		case globals::Key::UP_KEY:

			rightKey = SL_KEY_UP;

			break;
		default:
			break;
		}

		if (slGetKey(rightKey))
		{
			paddle.posX += paddle.speed * globals::deltaT;
		}
	}

	if (paddle.posX <= paddle.width / 2)
	{
		paddle.posX = paddle.width / 2;
	}
	if (paddle.posX + paddle.width / 2 >= 100)
	{
		paddle.posX = 100 - paddle.width / 2;
	}
}

void paddle::LivesDraw(Paddle& paddle, text::Text hp)
{
	int posX = 10;
	int radius = 1.2f;

	for (int i = 0; i < paddle.lives; i++)
	{
		if (globals::usingRaylib)
		{
			draw::DrawCirc(hp.posX * 2 + i * 2, radius * 4.0f, radius, WHITE);
		}
		else
		{
			draw::DrawCirc(hp.posX * 2 + i * 2, radius * 3.0f, radius, WHITE);
		}
	}
}

void paddle::ApplyPowerUp(Paddle& paddle)
{
	switch (paddle.powerUpType)
	{
	case powerup::PowerUpType::ExtraBall:

		paddle.speed = 100.0f;

		break;
	case powerup::PowerUpType::ExtraPaddles:

		paddle.speed = 100.0f;

		break;
	case powerup::PowerUpType::DoubleDamage:

		paddle.speed = 100.0f;

		break;
	case powerup::PowerUpType::ShootBall:

		paddle.speed = 100.0f;

		break;
	case powerup::PowerUpType::None:

		break;
	default:

		break;
	}
}
