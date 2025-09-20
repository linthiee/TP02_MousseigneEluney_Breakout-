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

		float speed = 5.0f;

		Color color = WHITE;

	};

	void Draw(Ball& ball, paddle::Paddle& paddle);
	void Movement(Ball& ball);
}
