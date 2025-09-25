#pragma once
#include <iostream>
#include "Raylib.h"
#include "Globals.h"
#include "Draw.h"

namespace paddle
{
	struct Paddle
	{
		float width = 7;
		float height = 2;

		float posX = 50;
		float posY = 95;

		float speed = 50.0f;

		Color color = WHITE;

		int currentTextureID = 0;

		Key keyLeft = Key::LEFT_KEY;
		Key keyRight = Key::RIGHT_KEY;
		Key keyUp = Key::UP_KEY;

		int score = 0;

		int lives = 5;
	};

	void Draw(Paddle paddle);
	void Movement(Paddle& paddle);
	void LivesDraw(Paddle& paddle, text::Text hp);
}
