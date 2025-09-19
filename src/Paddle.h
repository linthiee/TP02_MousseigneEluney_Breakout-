#pragma once
#include "Raylib.h"
#include "Globals.h"

namespace paddle
{
	struct Paddle
	{
		int width = 5;
		int height = 2;

		float posX = 50;
		float posY = 95;

		float speed = 20.0f;

		Color color = SKYBLUE;

		Key keyLeft = Key::LEFT_KEY;
		Key keyRight = Key::RIGHT_KEY;
	};

	void Draw(Paddle& paddle);
	void Movement(Paddle& paddle);
}
