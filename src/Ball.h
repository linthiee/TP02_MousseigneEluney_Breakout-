#pragma once
#include "Raylib.h"
#include "Draw.h"
#include "Paddle.h"

namespace ball
{
	struct Ball
	{
		float radius = 7.0f;

		bool idle = true;

		float posX = 0.0f;
		float posY = 0.0f;

		float velocityX = 3;
		float velocityY = 3;

		float speed = 5.0f;

		bool firstShoot = true;

		Color color = WHITE;
	};

	void Draw(Ball ball);
    void ShootBall(Ball& ball, paddle::Paddle& paddle);
	void Movement(Ball& ball);
	//void UpdateMovement(Ball& ball);
}
