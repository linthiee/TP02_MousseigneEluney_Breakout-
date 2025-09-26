#include "StateManager.h"

void MainLoop()
{
	srand(time(nullptr));
	globals::usingRaylib = true;

	State state = State::Menu;

	text::Text score;
	text::Text hp;
	text::Text title;

	buttons::Button unmute;
	buttons::Button mute;

	paddle::Paddle paddle;
	ball::Ball ball;
	block::Block block[globals::maxRows][globals::maxCols];

	game::Initialization(block, ball, paddle, score, hp, title, mute, unmute);

	sound::SetSound(globals::menuSound, globals::menuSoundID);

	while (!WindowClosed())
	{
		switch (state)
		{
		case State::Menu:

			//menu::Update(state);

			if (slGetKey('P'))
			{
				state = State::Play;
			}
			if (IsKeyPressed('P'))
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

void Initializers(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score, text::Text& hp, text::Text& title, buttons::Button& mute, buttons::Button& unmute)
{
	Color colors[globals::maxRows] = { RED, ORANGE, YELLOW, GREEN, SKYBLUE, BLUE, PURPLE };
	int scores[globals::maxRows] = { 350, 300, 250, 200, 150, 100, 50 };

	InitializeWindow(globals::screenWidth, globals::screenHeight, "Breakout");

	InitAudioDevice();

	Texture tempTexture;

	score.text = "Score: " + std::to_string(paddle.score);
	hp.text = "Hp: ";
	title.text = "Breakout!";

	if (globals::usingRaylib)
	{
		globals::background = "res/Background_Raylib.png";

		tempTexture = LoadTexture(globals::background.c_str());
		globals::backgroundTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::blockNormalTexture.c_str());
		globals::blockNormalTextureID = tempTexture.id;
		globals::paddleTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::ballNormalTexture.c_str());
		globals::ballNormalTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::menuTexture.c_str());
		globals::menuTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::unmutedIcon.c_str());
		globals::unmutedIconID = tempTexture.id;

		tempTexture = LoadTexture(globals::mutedIcon.c_str());
		globals::mutedIconID = tempTexture.id;

		globals::menuSound = LoadSound(globals::menuSong.c_str());

		globals::collisionEffectSound = LoadSound(globals::collisionEffect.c_str());
	
		globals::playingSound = LoadSound(globals::playingSong.c_str());
		
		globals::collisionWithPaddleSound = LoadSound(globals::collisionWithPaddle.c_str());

		score.font = LoadFont(globals::fontText.c_str());

		score.posX = 80;
		score.posY = 4;

		hp.font = LoadFont(globals::fontText.c_str());

		hp.posX = 4;
		hp.posY = 4;

		title.fonstSize = 40;

		title.font = LoadFont(globals::fontText.c_str());

		title.posX = 50;
		title.posY = 10;

		mute.posX = 95;
		mute.posY = 4;

		unmute.posX = 95;
		unmute.posY = 4;
	}
	else
	{
		globals::backgroundTextureID = slLoadTexture(globals::background.c_str());

		globals::blockNormalTextureID = slLoadTexture(globals::blockNormalTexture.c_str());

		globals::ballNormalTextureID = slLoadTexture(globals::ballNormalTexture.c_str());

		globals::paddleTextureID = slLoadTexture(globals::blockNormalTexture.c_str());

		globals::menuTextureID = slLoadTexture(globals::menuTexture.c_str());

		globals::unmutedIconID = slLoadTexture(globals::unmutedIcon.c_str());

		globals::mutedIconID = slLoadTexture(globals::mutedIcon.c_str());

		globals::font = slLoadFont(globals::fontText.c_str());

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

		globals::menuSoundID = slLoadWAV(globals::menuSong.c_str());

		globals::playingSongID = slLoadWAV(globals::playingSong.c_str());

		globals::collisionEffectID = slLoadWAV(globals::collisionEffect.c_str());

		globals::collisionWithPaddleID = slLoadWAV(globals::collisionWithPaddle.c_str());
	}

	ball.currentTextureID = globals::ballNormalTextureID;
	paddle.currentTextureID = globals::paddleTextureID;
	unmute.currentTextureID = globals::unmutedIconID;
	mute.currentTextureID = globals::mutedIconID;

	for (int col = 0; col < globals::maxCols; col++)
	{
		int counterInCol = 0;
		for (int row = 0; row < globals::maxRows; row++)
		{
			block[row][col].width = 100.0f * ((float)globals::screenWidth / ((float)globals::maxCols + 1.0f)) / (float)globals::screenWidth;

			block[row][col].posX = 49.5f + 50.0f * ((float)globals::screenWidth / ((float)globals::maxCols)) / (float)globals::screenWidth;
			block[row][col].posX += (col - ((float)globals::maxCols / 2)) * 90.0f * ((float)globals::screenWidth / ((float)globals::maxCols)) / (float)globals::screenWidth;

			block[row][col].posY = row * block[row][col].height * 3 + 5 * block[row][col].height;

			block[row][col].color = colors[row];

			block[row][col].score = scores[row];

			if (counterInCol < globals::maxPowerUpsPerCol)
			{
				block[row][col].block.powerUpType = block::DecidePowerUpType(block[row][col].block.counterInCol);
				block::ApplyPowerUpToBlock(block[row][col]);
			}

			if (block[row][col].block.powerUpType != powerup::PowerUpType::None)
			{
				counterInCol++;
			}

			block[row][col].currentTextureID = globals::blockNormalTextureID;
		}
	}
}

void DrawBackground()
{
	draw::DrawSprite(globals::backgroundTextureID, 50, 50, 100, 100, WHITE);
}

void UpdateDeltaTime()
{
	if (globals::usingRaylib)
	{
		globals::deltaT = GetFrameTime();
	}
	else
	{
		globals::deltaT = slGetDeltaTime();
	}
}

int ScreenWidth()
{
	if (globals::usingRaylib)
	{
		return GetScreenWidth();
	}
	else
	{
		return globals::screenWidth;
	}
}

int ScreenHeight()
{
	if (globals::usingRaylib)
	{
		return GetScreenHeight();
	}
	else
	{
		return globals::screenHeight;
	}
}

void InitializeWindow(int screenWidth, int screenHeight, std::string title)
{
	if (globals::usingRaylib)
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
	if (globals::usingRaylib)
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
	if (globals::usingRaylib)
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
	if (globals::usingRaylib)
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
	if (globals::usingRaylib)
	{
		EndDrawing();
	}
	else
	{
		slRender();
	}
}

void game::Initialization(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score,
	text::Text& hp, text::Text& title, buttons::Button& mute, buttons::Button& unmute)
{
	Initializers(block, ball, paddle, score, hp, title, mute, unmute);
}

void game::Update(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score, buttons::Button& mute, buttons::Button& unmute)
{
	sound::PauseUnpauseSong(mute);

	UpdateDeltaTime();

	paddle::Movement(paddle);
	ball::ShootBall(ball, paddle);

	globals::screenWidth = ScreenWidth();
	globals::screenHeight = ScreenHeight();

	ball::Movement(ball);

	if (CheckCollisions(paddle, ball))
	{
		if (!ball.idle)
		{
			sound::SetSound(globals::collisionWithPaddleSound, globals::collisionWithPaddleID);
		}
		ball::CollidedPaddle(paddle, ball);
	}

	for (int row = 0; row < globals::maxRows; row++)
	{
		for (int col = 0; col < globals::maxCols; col++)
		{
			if (block[row][col].durability > 0)
			{
				if (CheckCollisions(block[row][col], ball))
				{
					sound::SetSound(globals::collisionEffectSound, globals::collisionEffectID);
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

void game::Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
	text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute)
{
	DrawBackground();

	if (mute.isMuted)
	{
		draw::DrawButtons(mute);
	}
	else
	{
		draw::DrawButtons(unmute);
	}

	draw::DrawText(score);
	draw::DrawText(hp);

	LivesDraw(paddle, hp);

	for (int row = 0; row < globals::maxRows; row++)
	{
		for (int col = 0; col < globals::maxCols; col++)
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

void sound::SetSound(Sound sound, int soundID)
{
	if (globals::usingRaylib)
	{
		SetSoundVolume(sound, 0.5f);
		PlaySound(sound);
	}
	else
	{
		slSoundPlay(soundID);
	}
}

void sound::SetPlayingSound()
{
	if (globals::usingRaylib)
	{
		StopSound(globals::menuSound);

		PlaySound(globals::playingSound);
	}
	else
	{
		slSoundStop(globals::menuSoundID);

		slSoundLoop(globals::playingSongID);
	}
}

void sound::PauseUnpauseSong(buttons::Button& mute)
{
	if (globals::usingRaylib)
	{
		if (IsKeyPressed('M') && !mute.isMuted)
		{
			mute.isMuted = true;
			PauseSound(globals::playingSound);
		}
		else if (IsKeyPressed('M') && mute.isMuted)
		{
			mute.isMuted = false;
			ResumeSound(globals::playingSound);
		}
	}
	else
	{
		globals::muteButtonWasPressed = false;

		if (slGetKey('M'))
		{
			if (!globals::muteButtonIsPressed)
			{
				globals::muteButtonWasPressed = true;
			}
			globals::muteButtonIsPressed = true;
		}
		else
		{
			globals::muteButtonIsPressed = false;
		}

		if (globals::muteButtonWasPressed)
		{
			mute.isMuted = !mute.isMuted;

			if (mute.isMuted)
			{
				slSoundPause(globals::playingSongID);
			}
			else
			{
				slSoundResumeAll();
			}
		}
	}
}
