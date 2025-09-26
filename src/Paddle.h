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

		globals::Key keyLeft = globals::Key::LEFT_KEY;
		globals::Key keyRight = globals::Key::RIGHT_KEY;
		globals::Key keyUp = globals::Key::UP_KEY;

		int score = 0;

		int lives = 5;
	};

	void Draw(Paddle paddle);
	void Movement(Paddle& paddle);
	void LivesDraw(Paddle& paddle, text::Text hp);
}
