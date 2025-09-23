#pragma once
#include "Raylib.h"
#include "Draw.h"
#include "Paddle.h"
#include "Block.h"
#include "Utils.h"

namespace ball
{
	struct Ball
	{
		float radius = 1.2f;

		bool idle = true;

		float posX = 0.0f;
		float posY = 0.0f;

		float velocityX = 1.0f;
		float velocityY = 1.0f;

		float speed = 60.0f;

		bool firstShoot = true;

		Color color = WHITE;

		int currentTextureID = 0;
	};

	void Draw(Ball ball);
	void ShootBall(Ball& ball, paddle::Paddle& paddle);
	void Movement(Ball& ball);

	bool CheckCollisions(float posX, float posY, float width, float height, ball::Ball ball);
	bool CheckCollisions(block::Block& block, ball::Ball ball);
	bool CheckCollisions(paddle::Paddle& paddle, ball::Ball ball);

	void CollidedPaddle(paddle::Paddle& paddle, Ball& ball);

	void UpdateMovement(Ball& ball, block::Block block);

	void UpdateOnLivesLost(Ball& ball, paddle::Paddle& paddle);

}
