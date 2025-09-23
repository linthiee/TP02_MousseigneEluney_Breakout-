#include "StateManager.h"

void MainLoop()
{
	srand(time(nullptr));
	usingRaylib = false;

	State state = State::Play;

	text::Text score;
	text::Text hp;
	text::Text title;

	buttons::Button unmute;
	buttons::Button mute;

	paddle::Paddle paddle;
	ball::Ball ball;
	block::Block block[maxRows][maxCols];

	game::Initialization(block, ball, paddle, score, hp, title, mute, unmute);

	sound::SetSound();

	while (!WindowClosed())
	{
		switch (state)
		{
		case State::Menu:

			menu::Update(state);

			if (slGetKey('P'))
			{
				state = State::Play;
			}

			if (state == State::Play)
			{
				sound::SetPlayingSound();
			}

			break;
		case State::Play:

			game::Update(block, ball, paddle, score, mute, unmute);

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

			menu::Draw(title);

			break;
		case State::Play:

			game::Draw(block, ball, paddle, score, hp, mute, unmute);

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
	//DeInitialize (ACORDARSE DE DEINICIALIZAR LAS TEXTURAS!!!!!!!!1111)
	EndWindow();

}

void Initializers(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score, text::Text& hp, text::Text& title, buttons::Button& mute, buttons::Button& unmute)
{
	Color colors[maxRows] = { RED, ORANGE, YELLOW, GREEN, SKYBLUE, BLUE, PURPLE };
	int scores[maxRows] = { 350, 300, 250, 200, 150, 100, 50 };

	InitializeWindow(screenWidth, screenHeight, "Breakout");

	InitAudioDevice();

	Texture tempTexture;

	score.text = "Score: " + std::to_string(paddle.score);
	hp.text = "Hp: ";
	title.text = "Breakout!";

	if (usingRaylib)
	{
		background = "res/Background_Raylib.png";

		tempTexture = LoadTexture(background.c_str());
		backgroundTextureID = tempTexture.id;

		tempTexture = LoadTexture(blockNormalTexture.c_str());
		blockNormalTextureID = tempTexture.id;
		paddleTextureID = tempTexture.id;

		tempTexture = LoadTexture(ballNormalTexture.c_str());
		ballNormalTextureID = tempTexture.id;

		tempTexture = LoadTexture(menuTexture.c_str());
		menuTextureID = tempTexture.id;

		tempTexture = LoadTexture(unmutedIcon.c_str());
		unmutedIconID = tempTexture.id;

		tempTexture = LoadTexture(mutedIcon.c_str());
		mutedIconID = tempTexture.id;

		menuSound = LoadSound(menuSong.c_str());

		score.font = LoadFont(fontText.c_str());

		score.posX = 80;
		score.posY = 4;

		hp.font = LoadFont(fontText.c_str());

		hp.posX = 4;
		hp.posY = 4;

		title.fonstSize = 40;

		title.font = LoadFont(fontText.c_str());

		title.posX = 50;
		title.posY = 10;

		mute.posX = 95;
		mute.posY = 4;

		unmute.posX = 95;
		unmute.posY = 4;
	}
	else
	{
		backgroundTextureID = slLoadTexture(background.c_str());

		blockNormalTextureID = slLoadTexture(blockNormalTexture.c_str());

		ballNormalTextureID = slLoadTexture(ballNormalTexture.c_str());

		paddleTextureID = slLoadTexture(blockNormalTexture.c_str());

		menuTextureID = slLoadTexture(menuTexture.c_str());

		unmutedIconID = slLoadTexture(unmutedIcon.c_str());

		mutedIconID = slLoadTexture(mutedIcon.c_str());

		font = slLoadFont(fontText.c_str());

		title.fonstSize = 40;

		score.posX = 80;
		score.posY = 4;

		hp.posX = 4;
		hp.posY = 4;

		title.posX = 50;
		title.posY = 10;

		mute.posX = 95;
		mute.posY = 4;

		unmute.posX = 95;
		unmute.posY = 4;

		menuSoundID = slLoadWAV(menuSong.c_str());
	}

	ball.currentTextureID = ballNormalTextureID;
	paddle.currentTextureID = paddleTextureID;
	unmute.currentTextureID = unmutedIconID;
	mute.currentTextureID = mutedIconID;

	for (int row = 0; row < maxRows; row++)
	{
		for (int col = 0; col < maxCols; col++)
		{
			block[row][col].width = 100.0f * ((float)screenWidth / ((float)maxCols + 1.0f)) / (float)screenWidth;

			block[row][col].posX = 49.5f + 50.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;
			block[row][col].posX += (col - ((float)maxCols / 2)) * 90.0f * ((float)screenWidth / ((float)maxCols)) / (float)screenWidth;

			block[row][col].posY = row * block[row][col].height * 3 + 5 * block[row][col].height;

			block[row][col].color = colors[row];

			block[row][col].score = scores[row];

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

void game::Initialization(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score,
	text::Text& hp, text::Text& title, buttons::Button& mute, buttons::Button& unmute)
{
	Initializers(block, ball, paddle, score, hp, title, mute, unmute);
}

void game::Update(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score, buttons::Button& mute, buttons::Button& unmute)
{
	sound::PauseUnpauseSong(mute);

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

					if (block[row][col].durability <= 0)
					{
						paddle.score += block[row][col].score;
					}
				}
			}
		}
	}

	UpdateOnLivesLost(ball, paddle);

	score.text = "Score: " + std::to_string(paddle.score);
}

void game::Draw(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle,
	text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute)
{
	DrawBackground();

	if (mute.isMuted)
	{
		DrawButtons(mute);
	}
	else
	{
		DrawButtons(unmute);
	}

	DrawText(score);
	DrawText(hp);

	LivesDraw(paddle, hp);

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

void sound::SetSound()
{
	if (usingRaylib)
	{
		PlaySound(menuSound);
	}
	else
	{
		slSoundPlay(menuSoundID);
	}
}

void sound::SetPlayingSound()
{
	menuSong = "res/Playing_Theme.wav";


	if (usingRaylib)
	{
		menuSound = LoadSound(menuSong.c_str());
		PlaySound(menuSound);
	}
	else
	{
		slSoundStop(menuSoundID);

		menuSoundID = slLoadWAV(menuSong.c_str());
		slSoundLoop(menuSoundID);
	}
}

void sound::PauseUnpauseSong(buttons::Button& mute)
{
	if (usingRaylib)
	{
		if (IsKeyPressed('M') && !mute.isMuted)
		{
			mute.isMuted = true;
			StopSound(menuSound);
		}
		else if (IsKeyPressed('M') && mute.isMuted)
		{
			mute.isMuted = false;
			ResumeSound(menuSound);
		}
	}
	else
	{
		muteButtonWasPressed = false;

		if (slGetKey('M'))
		{
			if (!muteButtonIsPressed)
			{
				muteButtonWasPressed = true;
			}
			muteButtonIsPressed = true;
		}
		else
		{
			muteButtonIsPressed = false;
		}

		if (muteButtonWasPressed)
		{
			mute.isMuted = !mute.isMuted;

			if (mute.isMuted)
			{
				slSoundPause(menuSoundID);
			}
			else
			{
				slSoundResumeAll();
			}
		}
	}
}
