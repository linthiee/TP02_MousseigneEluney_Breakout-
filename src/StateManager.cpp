#include "StateManager.h"

void MainLoop()
{
	srand(time(nullptr));
	usingRaylib = true;

	State state = State::Menu;

	paddle::Paddle paddle;
	ball::Ball ball;
	block::Block block[maxRows][maxCols];

	game::Initialization(block, ball, paddle);

	while (!WindowClosed())
	{
		switch (state)
		{
		case State::Menu:

			menu::Update(state);

			break;
		case State::Play:

			game::Update(block, ball, paddle);

			break;
		case State::Credits:
			break;
		case State::Pause:
			break;
		case State::EndScreen:
			break;
		case State::Exit:
			break;
		default:
			break;
		}

		StartDrawing();

		switch (state)
		{
		case State::Menu:

			menu::Draw();

			break;
		case State::Play:

			game::Draw(block, ball, paddle);

			break;
		case State::Credits:
			break;
		case State::Pause:
			break;
		case State::EndScreen:
			break;
		case State::Exit:
			break;
		default:
			break;
		}

		FinishDrawing();
	}
	//DeInitialize
	EndWindow();

}

void Initializers(block::Block block[maxRows][maxCols],ball::Ball& ball, paddle::Paddle& paddle)
{
	Color colors[maxRows] = { RED, ORANGE, YELLOW, GREEN, SKYBLUE, BLUE, PURPLE };

	InitializeWindow(screenWidth, screenHeight, "Breakout");

	Texture tempTexture;

	if (usingRaylib)
	{
		tempTexture = LoadTexture(background.c_str());
		backgroundTextureID = tempTexture.id;

		tempTexture = LoadTexture(blockNormalTexture.c_str());
		blockNormalTextureID = tempTexture.id;
		paddleTextureID = tempTexture.id;

		tempTexture = LoadTexture(ballNormalTexture.c_str());
		ballNormalTextureID = tempTexture.id;

		tempTexture = LoadTexture(menuTexture.c_str());
		menuTextureID = tempTexture.id;		
	}
	else
	{
		background = "res/Background_Sigil.png";
		backgroundTextureID = slLoadTexture(background.c_str());

		blockNormalTextureID = slLoadTexture(blockNormalTexture.c_str());

		ballNormalTextureID = slLoadTexture(ballNormalTexture.c_str());

		paddleTextureID = slLoadTexture(blockNormalTexture.c_str());

		menuTextureID = slLoadTexture(menuTexture.c_str());

		menuSoundID = slLoadWAV(menuSong.c_str());
	}

	ball.currentTextureID = ballNormalTextureID;
	paddle.currentTextureID = paddleTextureID;
	
	for (int row = 0; row < maxRows; row++)
	{
		for (int col = 0; col < maxCols; col++)
		{

			block[row][col].width = 100.0f * ((float)screenWidth / ((float)maxCols + 1.0f)) / (float)screenWidth;

			block[row][col].posX = 49.5f + 50.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;
			block[row][col].posX += (col - ((float)maxCols / 2)) * 90.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;

			block[row][col].posY = row * block[row][col].height * 3 + 5 * block[row][col].height;

			block[row][col].color = colors[row];


			block[row][col].currentTextureID = blockNormalTextureID;
		}
	}
}

void DrawBackground()
{
	DrawSprite(backgroundTextureID, 50, 50, 100, 100, WHITE);
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

void game::Initialization(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle)
{
	Initializers(block, ball, paddle);
}

void game::Update(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle)
{
	UpdateDeltaTime();

	paddle::Movement(paddle);
	ball::ShootBall(ball, paddle);

	screenWidth = ScreenWidth();
	screenHeight = ScreenHeight();

	ball::Movement(ball);

	if (CheckCollisions(paddle, ball))
	{
		ball::CollidedPaddle(paddle, ball);
	}

	for (int row = 0; row < maxRows; row++)
	{
		for (int col = 0; col < maxCols; col++)
		{
			if (block[row][col].durability > 0)
			{
				if (CheckCollisions(block[row][col], ball))
				{
					UpdateDurability(block[row][col]);
					UpdateMovement(ball, block[row][col]);
				}
			}
		}
	}
}

void game::Draw(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle)
{	
	DrawBackground();

	for (int row = 0; row < maxRows; row++)
	{
		for (int col = 0; col < maxCols; col++)
		{
			if (block[row][col].durability > 0)
			{
				block::Draw(block[row][col]);
			}
		}
	}

	paddle::Draw(paddle);
	ball::Draw(ball);
}