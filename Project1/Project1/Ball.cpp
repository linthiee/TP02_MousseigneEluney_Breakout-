#include "Ball.h"

void ball::Draw(Ball& ball, paddle::Paddle& paddle)
{
	if (ball.startPos)
	{
		ball.posY = (paddle.posY - 3.0f) * screenHeight / 100;
		ball.posX = paddle.posX * screenWidth / 100;
	}

	DrawCirc(ball.posX, ball.posY, ball.radius, ball.color);
}

void ball::Shoot(Ball& ball, paddle::Paddle& paddle)
{
	int upKey = 0;

	if (usingRaylib)
	{
		switch (paddle.upKey)
		{
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			upKey = KeyboardKey::KEY_UP;

			break;
		case Key::RIGHT_KEY:

			upKey = KeyboardKey::KEY_UP;

			break;
		case Key::UP_KEY:

			upKey = KeyboardKey::KEY_UP;

			break;
		default:
			break;
		}
	}
	else
	{
		switch (paddle.upKey)
		{
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			upKey = SL_KEY_UP;

			break;
		case Key::RIGHT_KEY:

			upKey = SL_KEY_UP;

			break;
		case Key::UP_KEY:

			upKey = SL_KEY_UP;

			break;
		default:
			break;
		}
	}

	if (IsKeyDown(upKey))
	{
		if ((GetRandomValue(-1, 1) == -1))
		{
			ball.velocityY = -ball.velocityY;

			if ((GetRandomValue(-1, 1) == -1))
			{
				ball.velocityX = -ball.velocityX;
			}
		}
		else
		{
			if ((GetRandomValue(-1, 1) == -1))
			{
				ball.velocityX = -ball.velocityX;
			}
		}
		ball.startPos = false;
	}
}

void ball::UpdatePos(Ball& ball)
{
	ball.posX = ball.posX + ball.velocityX * deltaT;
	ball.posY = ball.posY + ball.velocityY * deltaT;

	if (ball.posY + ball.radius >= screenHeight || ball.posY - ball.radius <= 0)
	{
		ball.velocityY *= -1;
	}
}
