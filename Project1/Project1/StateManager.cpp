#include "StateManager.h"

void MainLoop()
{
	usingRaylib = true;

	//Initialization
	paddle::Paddle paddle;
	ball::Ball ball;
	block::Block block[maxRows][maxCols];

	Initializers(block);

	while (!WindowClosed())
	{
		UpdateDeltaTime();

		//Inputs

		paddle::Movement(paddle);
		ball::Shoot(ball, paddle);

		//Update

		screenWidth = ScreenWidth();
		screenHeight = ScreenHeight();
		ball::UpdatePos(ball);

		//Draw

		StartDrawing();

		for (int row = 0; row < maxRows; row++)
		{
			for (int col = 0; col < maxCols; col++)
			{
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
	Color colors[maxRows] = { RED, ORANGE, YELLOW, GREEN, SKYBLUE, BLUE, PURPLE };

	for (int row = 0; row < maxRows; row++)
	{
		for (int col = 0; col < maxCols; col++)
		{
			block[row][col].width = 100.0f * ((float)screenWidth / ((float)maxCols + 1.0f)) / (float)screenWidth;

			block[row][col].posX = 50 + 50.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;
			block[row][col].posX += (col - ((float)maxCols / 2)) * 100.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;

			block[row][col].posY = row * block[row][col].height * 2 + block[row][col].height;

			block[row][col].color = colors[row];
		}
	}
	InitializeWindow(screenWidth, screenHeight, "Breakout");

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
		slWindow(screenWidth, screenHeight, title.c_str(), true);
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