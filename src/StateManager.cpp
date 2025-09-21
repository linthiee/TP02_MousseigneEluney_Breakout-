#include "StateManager.h"

void MainLoop()
{
	srand(time(nullptr));
	usingRaylib = false;

	//Initialization
	paddle::Paddle paddle;
	ball::Ball ball;
	block::Block block[maxRows][maxCols];

	Color colors[maxRows] = { RED, ORANGE, YELLOW, GREEN, SKYBLUE, BLUE, PURPLE };

	Initializers(block);

	while (!WindowClosed())
	{
		UpdateDeltaTime();

		//Inputs

		paddle::Movement(paddle);
		ball::ShootBall(ball, paddle);

		//Update

		screenWidth = ScreenWidth();
		screenHeight = ScreenHeight();

		ball::Movement(ball);


		for (int row = 0; row < maxRows; row++)
		{
			for (int col = 0; col < maxCols; col++)
			{
				if (CheckCollisions(block[row][col], ball))
				{
					if (ball.posX - ball.radius < block[row][col].posX + block[row][col].width)
					{
						ball.posX = block[row][col].posX + ball.radius + block[row][col].width;
						ball.posY = (float)ball.posY;
					}
				}
				else
				{
					if (ball.posX + ball.radius > block[row][col].posX)
					{
						ball.posX = block[row][col].posX - ball.radius;
						ball.posY = ball.posY;
					}
				}

				//UpdateMovement(ball);
			}
		}
		//Draw

		StartDrawing();

		DrawBackground();

		for (int row = 0; row < maxRows; row++)
		{
			for (int col = 0; col < maxCols; col++)
			{
				block[row][col].color = colors[row];
				block::Draw(block[row][col]);
			}
		}

		paddle::Draw(paddle);
		ball::Draw(ball);

		FinishDrawing();
	}
	//DeInitialize
	EndWindow();

}

void Initializers(block::Block block[maxRows][maxCols])
{
	InitializeWindow(screenWidth, screenHeight, "Breakout");

	for (int row = 0; row < maxRows; row++)
	{
		for (int col = 0; col < maxCols; col++)
		{
			block[row][col].width = 100.0f * ((float)screenWidth / ((float)maxCols + 1.0f)) / (float)screenWidth;

			block[row][col].posX = 49.5f + 50.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;
			block[row][col].posX += (col - ((float)maxCols / 2)) * 90.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;

			block[row][col].posY = row * block[row][col].height * 2 + block[row][col].height;

			if (usingRaylib)
			{
				block[row][col].texture = LoadTexture(block[row][col].currentTexture.c_str());

				block[row][col].texture.width = block[row][col].width * screenWidth / 100;
				block[row][col].texture.height = block[row][col].height * screenHeight / 100;

				backgroundTexture = LoadTexture(background.c_str());

				backgroundTexture.width = screenWidth;
				backgroundTexture.height = screenHeight;
			}
			else
			{
				block[row][col].currentTextureID = slLoadTexture(block[row][col].currentTexture.c_str());

				background = "res/Background_Sigil.png";
				backgroundTextureID = slLoadTexture(background.c_str());
			}
		}
	}
}

void DrawBackground()
{
	if (usingRaylib)
	{
		DrawTexture(backgroundTexture, 0, 0, WHITE);
	}
	else
	{
		slSprite(backgroundTextureID, screenWidth / 2, screenHeight / 2, screenWidth, screenHeight);
	}
}

void UpdateDeltaTime()
{
	if (usingRaylib)
	{
		deltaT = GetFrameTime();
	}
	else
	{
		deltaT = slGetDeltaTime();
	}
}

int ScreenWidth()
{
	if (usingRaylib)
	{
		return GetScreenWidth();
	}
	else
	{
		return screenWidth;
	}
}

int ScreenHeight()
{
	if (usingRaylib)
	{
		return GetScreenHeight();
	}
	else
	{
		return screenHeight;
	}
}

void InitializeWindow(int screenWidth, int screenHeight, std::string title)
{

	if (usingRaylib)
	{
		InitWindow(screenWidth, screenHeight, title.c_str());

	}
	else
	{
		slWindow(screenWidth, screenHeight, title.c_str(), false);
	}
}

bool WindowClosed()
{

	if (usingRaylib)
	{

		if (WindowShouldClose())
		{
			return true;
		}
	}
	else
	{
		if (slShouldClose())
		{
			return true;
		}
	}
	return false;
}

void EndWindow()
{
	if (usingRaylib)
	{
		CloseWindow();
	}
	else
	{
		slClose();
	}
}

void StartDrawing()
{
	if (usingRaylib)
	{
		BeginDrawing();

		ClearBackground(BLACK);
	}
	else
	{
		slSetBackColor(0, 0, 0);
	}
}

void FinishDrawing()
{
	if (usingRaylib)
	{
		EndDrawing();
	}
	else
	{
		slRender();
	}
}