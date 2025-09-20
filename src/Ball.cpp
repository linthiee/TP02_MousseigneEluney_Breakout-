#include "Ball.h"

void ball::Draw(Ball ball)
{
	ball.posY = ball.posY * screenHeight / 100;
	ball.posX = ball.posX * screenWidth / 100;

	DrawCirc(ball.posX, ball.posY, ball.radius, ball.color);
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
	ball.posY = paddle.posY - 3.0f;

	if (usingRaylib)
	{
		switch (paddle.keyUp)
		{
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			upKey = (int)KeyboardKey::KEY_LEFT;

			break;
		case Key::RIGHT_KEY:

			upKey = (int)KeyboardKey::KEY_RIGHT;

			break;
		case Key::UP_KEY:

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
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			upKey = SL_KEY_LEFT;

			break;
		case Key::RIGHT_KEY:

			upKey = SL_KEY_RIGHT;

			break;
		case Key::UP_KEY:

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
		ball.velocityY = -ball.velocityY;

		int direction = rand() % ((maxDirecBall - minDirecBall + 1) + minDirecBall);

		if (direction == -1 || direction == 0)
		{
			ball.velocityX = -ball.velocityX;

			if (direction == -1 || direction == 0)
			{
				ball.velocityX = -ball.velocityX;
			}
		}
		else
		{
			if (direction == 1)
			{
				ball.velocityX = -ball.velocityX;
			}
		}
		ball.firstShoot = false;
	}
}

void ball::Movement(Ball& ball)
{
	ball.posX += ball.velocityX * ball.speed * deltaT;
	ball.posY += ball.velocityY * ball.speed * deltaT;

	if (ball.posX + (ball.radius / 100) > 100)
	{
		ball.posX = 100 - (ball.radius / 100);
		ball.velocityX *= -1;
	}
	if (ball.posX - (ball.radius / 100) < 0)
	{
		ball.posX = ball.radius / 100;
		ball.velocityX *= -1;
	}

	if (ball.posY + (ball.radius / 100) > 100.0f)
	{
		ball.posY = 100 - (ball.radius / 100);
		ball.velocityY *= -1;
	}
	if (ball.posY - (ball.radius / 100) < 0)
	{
		ball.posY = (ball.radius / 100);
		ball.velocityY *= -1;
	}
}
