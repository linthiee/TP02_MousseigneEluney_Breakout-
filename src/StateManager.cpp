#include "StateManager.h"

void MainLoop()
{
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

		//Update

		screenWidth = ScreenWidth();
		screenHeight = ScreenHeight();

		//Draw

		StartDrawing();

		for (int row = 0; row < maxRows; row++)
		{
			for (int col = 0; col < maxCols; col++)
			{
				block[row]->color = colors[row];
				block::Draw(block[row][col]);
			}
		}

		paddle::Draw(paddle);
		ball::Draw(ball, paddle);

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

			block[row][col].posX = 50 + 50.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;
			block[row][col].posX += (col - ((float)maxCols / 2)) * 100.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;

			block[row][col].posY = row * block[row][col].height * 2 + block[row][col].height;

			if (usingRaylib)
			{
				block[row][col].texture = LoadTexture(block[row][col].currentTexture.c_str());

				block[row][col].texture.width = block[row][col].width / 2 * screenWidth / 100;
				block[row][col].texture.height = block[row][col].height * screenHeight / 100;
			}
			else
			{
				block[row][col].currentTextureID = slLoadTexture(block[row][col].currentTexture.c_str());
			}
		}
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
		SetWindowState(FLAG_WINDOW_RESIZABLE);
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