#include "Paddle.h"

void paddle::Draw(Paddle paddle)
{
	DrawRec(paddle.posX, paddle.posY, paddle.width, paddle.height, paddle.color);
}

void paddle::Movement(Paddle& paddle)
{
	int leftKey = 0;
	int rightKey = 0;

	if (usingRaylib)
	{
		switch (paddle.keyLeft)
		{
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			leftKey = (int)KeyboardKey::KEY_LEFT;

			break;
		case Key::RIGHT_KEY:

			leftKey = (int)KeyboardKey::KEY_RIGHT;

			break;
		case Key::UP_KEY:

			leftKey = (int)(KeyboardKey::KEY_UP);

			break;
		default:
			break;
		}

		if (IsKeyDown(leftKey))
		{
			paddle.posX -= paddle.speed * deltaT;
		}

		switch (paddle.keyRight)
		{
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			rightKey = (int)KeyboardKey::KEY_LEFT;

			break;
		case Key::RIGHT_KEY:

			rightKey = (int)(KeyboardKey::KEY_RIGHT);

			break;
		case Key::UP_KEY:

			rightKey = (int)(KeyboardKey::KEY_UP);

			break;
		default:
			break;
		}

		if (IsKeyDown(rightKey))
		{
			paddle.posX += paddle.speed * deltaT;
		}
	}
	else
	{
		switch (paddle.keyLeft)
		{
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			leftKey = SL_KEY_LEFT;

			break;
		case Key::RIGHT_KEY:

			leftKey = SL_KEY_RIGHT;

			break;
		case Key::UP_KEY:

			leftKey = SL_KEY_UP;

			break;
		default:
			break;
		}

		if (slGetKey(leftKey))
		{
			paddle.posX -= paddle.speed * deltaT;
		}

		switch (paddle.keyRight)
		{
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			rightKey = SL_KEY_LEFT;

			break;
		case Key::RIGHT_KEY:

			rightKey = SL_KEY_RIGHT;

			break;
		case Key::UP_KEY:

			rightKey = SL_KEY_UP;

			break;
		default:
			break;
		}

		if (slGetKey(rightKey))
		{
			paddle.posX += paddle.speed * deltaT;
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
