#include "Ball.h"

void ball::Draw(Ball& ball, paddle::Paddle& paddle)
{
	ball.posY = (paddle.posY - 3.0f) * screenHeight / 100;
	ball.posX = paddle.posX * screenWidth / 100;

	DrawCirc(ball.posX, ball.posY, ball.radius, ball.color);
}
