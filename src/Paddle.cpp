#include "Paddle.h"
#include "Draw.h"

void paddle::Draw(Paddle& paddle)
{
	DrawRec(paddle.posX * screenWidth / 100, paddle.posY * screenHeight / 100, paddle.width * screenWidth / 100, paddle.height * screenHeight / 100, paddle.color);
}

void paddle::Movement(Paddle& paddle)
{
	if (usingRaylib)
	{
		KeyboardKey leftKey;

		switch (paddle.keyLeft)
		{
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			leftKey = KeyboardKey::KEY_LEFT;

			break;
		case Key::RIGHT_KEY:

			leftKey = KeyboardKey::KEY_RIGHT;

			break;
		default:
			break;
		}

		if (paddle.posX <= paddle.width / 2)
		{
			paddle.posX = paddle.width / 2;
		}
		if (paddle.posX + paddle.width / 2 >= 100)
		{
			paddle.posX = 100 - paddle.width / 2;
		}

		if (IsKeyDown(leftKey))
		{
			paddle.posX -= paddle.speed * deltaT;
		}
		
		KeyboardKey rightKey;

		switch (paddle.keyRight)
		{
		case Key::NONE_KEY:
			break;
		case Key::LEFT_KEY:

			rightKey = KeyboardKey::KEY_LEFT;

			break;
		case Key::RIGHT_KEY:

			rightKey = KeyboardKey::KEY_RIGHT;

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
		int leftKey = 0;
		
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
		default:
			break;
		}

		if (slGetKey(leftKey))
		{
			paddle.posX -= paddle.speed * deltaT;
		}

		int rightKey = 0;

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
		default:
			break;
		}

		if (slGetKey(rightKey))
		{
			paddle.posX += paddle.speed * deltaT;
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
}
