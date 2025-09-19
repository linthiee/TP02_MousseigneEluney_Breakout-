#pragma once
#include "Raylib.h"
#include "Paddle.h"
#include "Draw.h"

namespace ball
{
	struct Ball
	{
		float radius = 7.0f;

		int posX = 0;
		int posY = 0;

		float velocityX = 1;
		float velocityY = 1;

		float speed = 0.5f;

		Color color = WHITE;

		bool startPos = true;

	};

	void Draw(Ball& ball, paddle::Paddle& paddle);
	void Shoot(Ball& ball, paddle::Paddle& paddle);
	void UpdatePos(Ball& ball);
}
