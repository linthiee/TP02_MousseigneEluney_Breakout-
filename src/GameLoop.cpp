#include <string>
#include "GameLoop.h"
#include "Draw.h"
#include "Globals.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Utils.h"

struct Cursor
{
	float radius = 0.5f;
	float positionX = 0.0f;
	float positionY = 0.0f;
};

enum class State
{
	Menu, Play, Credits, Pause, HowToPlay, EndScreen, Exit
};

void Initializers(Texture& tempTexture, block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score,
	text::Text& hp, text::Text& title, buttons::Button& mute, buttons::Button& unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax]);

void DrawBackground();

void UpdateDeltaTime();

void UpdateMousePosition(Cursor& cursor);

int ScreenWidth();
int ScreenHeight();

void InitializeWindow(int screenWidth, int screenHeight, std::string title = "Breakout");

bool WindowClosed();
void EndWindow();

void StartDrawing();
void FinishDrawing();

namespace menu
{
	void Update(State& state, text::Text& playText, text::Text& creditsText, text::Text& howToPlayText, text::Text& exitText, Cursor& cursor);
	void Draw(text::Text title, text::Text playText, text::Text creditsText, text::Text howToPlayText, text::Text exitText);
}

namespace credits
{
	void Update(State& state, text::Text& creditsText, text::Text& exitText, text::Text& profText, Cursor& cursor);
	void Draw(text::Text creditsText, text::Text exitText, text::Text profText);
}

namespace howtoplay
{
	void Update(State& state, text::Text& escapeControl, text::Text& muteControl, text::Text& shootControl, text::Text& moveControl, text::Text& stickyPU,
		text::Text& extraPaddlePU, text::Text& tripleDmgPU, text::Text& exitText, text::Text& powerUpText, Cursor& cursor);
	void Draw(text::Text shootControl, text::Text escapeControl, text::Text muteControl, text::Text moveControl, text::Text stickyPU, text::Text extraPaddlePU,
		text::Text tripleDmgPU, text::Text exitText, text::Text powerUpText);
}

namespace game
{
	void Initialization(Texture& tempTexture, block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score,
		text::Text& hp, text::Text& title, buttons::Button& mute, buttons::Button& unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax]);
	void Update(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
		text::Text& score, buttons::Button& mute, buttons::Button& unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax], State& state, Cursor& cursor);
	void Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
		text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax]);
	void Deinitialize(Texture& tempTexture);
}

namespace sound
{
	void SetSound(Sound sound, int soundID);
	void SetPlayingSound();
	void PauseUnpauseSong(buttons::Button& mute);
	void PauseSounds(Sound sound, int id);
	void UnpauseSounds(Sound sound);
	void PauseAll(Sound sound, int id);
}

namespace pause
{
	void Update(State& state, Cursor& cursor, text::Text& pauseText, text::Text& returnText, text::Text& retryText);
	void Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
		text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax], text::Text pauseText, text::Text returnText, text::Text retryText);
}

namespace win
{
	void Update(State& state, Cursor& cursor, text::Text& conditionText, text::Text& returnText, text::Text& retryText, text::Text& exit);
	void Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
		text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax], text::Text conditionText, text::Text returnText, text::Text retryText, text::Text& exit);
}
namespace lost
{
	void Update(State& state, Cursor& cursor, text::Text& conditionText, text::Text& returnText, text::Text& retryText, text::Text& exit);
	void Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
		text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax], text::Text conditionText, text::Text returnText, text::Text retryText, text::Text& exit);
}

void MainLoop()
{
	srand(time(nullptr));
	globals::usingRaylib = false;

	Cursor cursor;

	State state = State::Menu;

	text::Text playText;
	text::Text creditsText;
	text::Text howToPlayText;
	text::Text exitText;

	text::Text authorText;
	text::Text profText;

	text::Text shootControl;
	text::Text moveControl;
	text::Text escapeControl;
	text::Text muteControl;
	text::Text stickyPU;
	text::Text extraPaddlePU;
	text::Text tripleDmgPU;
	text::Text powerUpText;

	text::Text conditionText;
	text::Text exit;

	text::Text pauseText;
	text::Text returnText;
	text::Text retryText;

	text::Text score;
	text::Text hp;
	text::Text title;

	buttons::Button unmute;
	buttons::Button mute;

	paddle::Paddle paddle;
	paddle::Paddle extraPaddles[globals::extraPaddlesMax];

	Texture tempTexture;

	ball::Ball ball;
	block::Block block[globals::maxRows][globals::maxCols];

	game::Initialization(tempTexture, block, ball, paddle, score, hp, title, mute, unmute, extraPaddles);

	sound::SetSound(globals::menuSound, globals::menuSoundID);

	SetExitKey(KEY_VOLUME_UP);

	while (!WindowClosed() && state != State::Exit)
	{
		switch (state)
		{
		case State::Menu:

			menu::Update(state, playText, creditsText, howToPlayText, exitText, cursor);

			sound::PauseSounds(globals::playingSound, globals::playingSongID);

			if (globals::retry)
			{
				state = State::Play;
				globals::retry = false;
			}
			if (state == State::Play)
			{
				Initializers(tempTexture, block, ball, paddle, score, hp, title, mute, unmute, extraPaddles);	
				sound::PauseAll(globals::playingSound, globals::playingSongID);
				sound::SetPlayingSound();
			}

			break;
		case State::Play:

			game::Update(block, ball, paddle, score, mute, unmute, extraPaddles, state, cursor);

			if (state == State::Menu)
			{
				sound::PauseAll(globals::playingSound, globals::playingSongID);
				sound::SetSound(globals::menuSound, globals::menuSoundID);
			}

			break;
		case State::Credits:

			credits::Update(state, creditsText, exitText, profText, cursor);

			break;
		case State::Pause:

			pause::Update(state, cursor, pauseText, returnText, retryText);

			if (state == State::Menu)
			{
				sound::PauseAll(globals::playingSound, globals::playingSongID);
				sound::SetSound(globals::menuSound, globals::menuSoundID);
			}

			break;

		case State::HowToPlay:

			howtoplay::Update(state, escapeControl, muteControl, shootControl, moveControl, stickyPU, extraPaddlePU, tripleDmgPU, exitText, powerUpText, cursor);

			break;
		case State::EndScreen:

			if (paddle.lives > 0)
			{
				win::Update(state, cursor, conditionText, returnText, retryText, exit);
			}
			else
			{
				lost::Update(state, cursor, conditionText, returnText, retryText, exit);
			}

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

			if (!globals::retry)
			{
				menu::Draw(title, playText, creditsText, howToPlayText, exitText);
			}
			else
			{
				game::Draw(block, ball, paddle, score, hp, mute, unmute, extraPaddles);
			}

			break;
		case State::Play:

			game::Draw(block, ball, paddle, score, hp, mute, unmute, extraPaddles);

			break;
		case State::Credits:

			credits::Draw(creditsText, exitText, profText);

			break;
		case State::Pause:

			pause::Draw(block, ball, paddle, score, hp, mute, unmute, extraPaddles, pauseText, returnText, retryText);

			break;

		case State::HowToPlay:

			howtoplay::Draw(shootControl, escapeControl, muteControl, moveControl, stickyPU, extraPaddlePU, tripleDmgPU, exitText, powerUpText);

			break;
		case State::EndScreen:

			if (paddle.lives > 0)
			{
				win::Draw(block, ball, paddle, score, hp, mute, unmute, extraPaddles, conditionText, returnText, retryText, exit);
			}
			else
			{
				lost::Draw(block, ball, paddle, score, hp, mute, unmute, extraPaddles, conditionText, returnText, retryText, exit);
			}

			break;
		case State::Exit:



			break;
		default:
			break;
		}

		FinishDrawing();
	}
	game::Deinitialize(tempTexture);

	EndWindow();
}

void Initializers(Texture& tempTexture, block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score, text::Text& hp,
	text::Text& title, buttons::Button& mute, buttons::Button& unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax])
{

	globals::gamePaused = false;

	paddle = paddle::Paddle();
	ball = ball::Ball();

	Color colors[globals::maxRows] = { RED, ORANGE, YELLOW, GREEN, SKYBLUE, BLUE, PURPLE };
	int scores[globals::maxRows] = { 350, 300, 250, 200, 150, 100, 50 };

	ball.currentTextureID = globals::ballNormalTextureID;
	paddle.currentTextureID = globals::paddleTextureID;
	unmute.currentTextureID = globals::unmutedIconID;
	mute.currentTextureID = globals::mutedIconID;

	for (int i = 0; i < globals::extraPaddlesMax; i++)
	{
		extraPaddles[i].isActive = false;
		extraPaddles[i].currentTextureID = globals::paddleTextureID;
		extraPaddles[i].color = BEIGE;
		extraPaddles[i].width = 20;
		extraPaddles[i].height = 2;
		extraPaddles[i].posY = 99;
	}

	extraPaddles[0].posX = extraPaddles[0].width / 2;
	extraPaddles[1].posX = 50;
	extraPaddles[2].posX = 100 - extraPaddles[2].width / 2;

	for (int col = 0; col < globals::maxCols; col++)
	{
		for (int row = 0; row < globals::maxRows; row++)
		{
			block[row][col].block.powerUpType = powerup::PowerUpType::None;
		}
	}

	for (int col = 0; col < globals::maxCols; col++)
	{
		int counterInCol = 0;
		for (int row = 0; row < globals::maxRows; row++)
		{
			block[row][col].durability = 3;

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
			else
			{
				block[row][col].currentTextureID = globals::blockNormalTextureID;
			}

			if (block[row][col].block.powerUpType != powerup::PowerUpType::None)
			{
				counterInCol++;
			}
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

void UpdateMousePosition(Cursor& cursor)
{
	if (globals::usingRaylib)
	{
		cursor.positionX = (100 * GetMousePosition().x) / globals::screenWidth;
		cursor.positionY = (100 * GetMousePosition().y) / globals::screenHeight;
	}
	else
	{
		cursor.positionX = (100 * slGetMouseX()) / globals::screenWidth;
		cursor.positionY = 100 - ((100 * slGetMouseY()) / globals::screenHeight);
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

void menu::Update(State& state, text::Text& playText, text::Text& creditsText, text::Text& howToPlayText, text::Text& exitText, Cursor& cursor)
{
	UpdateMousePosition(cursor);

	playText = globals::defaultText;

	playText.text = "Play";

	playText.color = GRAY;

	playText.posX = 10;
	playText.posY = 25;

	playText.fonstSize = 40;

	if (utils::CheckCollisions(playText.posX, playText.posY, 10, 7, cursor.radius, cursor.positionX, cursor.positionY))
	{
		playText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Play;
		}
	}
	else
	{
		playText.color = GRAY;
	}

	creditsText = globals::defaultText;

	creditsText.text = "Credits";

	creditsText.color = GRAY;

	creditsText.posX = 13;
	creditsText.posY = 45;

	creditsText.fonstSize = 40;

	if (utils::CheckCollisions(creditsText.posX, creditsText.posY, 20, 7, cursor.radius, cursor.positionX, cursor.positionY))
	{
		creditsText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Credits;
		}
	}
	else
	{
		creditsText.color = GRAY;
	}

	howToPlayText = globals::defaultText;

	howToPlayText.text = "How to play";

	howToPlayText.color = GRAY;

	howToPlayText.posX = 17;
	howToPlayText.posY = 65;

	howToPlayText.fonstSize = 40;

	if (utils::CheckCollisions(howToPlayText.posX, howToPlayText.posY, 25, 7, cursor.radius, cursor.positionX, cursor.positionY))
	{
		howToPlayText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::HowToPlay;
		}
	}
	else
	{
		howToPlayText.color = GRAY;
	}

	exitText = globals::defaultText;

	exitText.text = "Exit";

	exitText.color = GRAY;

	exitText.posX = 9;
	exitText.posY = 85;

	exitText.fonstSize = 40;

	if (utils::CheckCollisions(exitText.posX, exitText.posY, 10, 7, cursor.radius, cursor.positionX, cursor.positionY))
	{
		exitText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Exit;
		}
	}
	else
	{
		exitText.color = GRAY;
	}
}

void menu::Draw(text::Text title, text::Text playText, text::Text creditsText, text::Text howToPlayText, text::Text exitText)
{
	draw::DrawSprite(globals::backgroundTextureID, 50, 50, 100, 100, WHITE);

	draw::DrawText(title);
	draw::DrawText(playText);
	draw::DrawText(creditsText);
	draw::DrawText(howToPlayText);
	draw::DrawText(exitText);
}


void game::Initialization(Texture& tempTexture, block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score,
	text::Text& hp, text::Text& title, buttons::Button& mute, buttons::Button& unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax])
{

	InitializeWindow(globals::screenWidth, globals::screenHeight, "Breakout");

	InitAudioDevice();

	score.text = "Score: " + std::to_string(paddle.score);
	hp.text = "Hp: ";
	title.text = "Breakout!";

	if (globals::usingRaylib)
	{
		globals::background = "res/Background_Image.png";

		tempTexture = LoadTexture(globals::background.c_str());
		globals::backgroundTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::blockNormalTexture.c_str());
		globals::blockNormalTextureID = tempTexture.id;
		globals::paddleTextureID = tempTexture.id;
		globals::extraPaddlesTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::ballNormalTexture.c_str());
		globals::ballNormalTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::pauseTexture.c_str());
		globals::pauseTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::extraPaddleBrickTexture.c_str());
		globals::extraPaddleBrickTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::tripleDamageBrickTexture.c_str());
		globals::tripleDamageBrickTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::shootBallBrickTexture.c_str());
		globals::shootBallBrickTextureID = tempTexture.id;

		tempTexture = LoadTexture(globals::unmutedIcon.c_str());
		globals::unmutedIconID = tempTexture.id;

		tempTexture = LoadTexture(globals::mutedIcon.c_str());
		globals::mutedIconID = tempTexture.id;

		globals::menuSound = LoadSound(globals::menuSong.c_str());

		globals::collisionEffectSound = LoadSound(globals::collisionEffect.c_str());

		globals::playingSound = LoadSound(globals::playingSong.c_str());

		globals::collisionWithPaddleSound = LoadSound(globals::collisionWithPaddle.c_str());

		globals::defaultText.font = LoadFont(globals::fontText.c_str());

		score.font = globals::defaultText.font;

		score.posX = 80;
		score.posY = 4;

		hp.font = globals::defaultText.font;

		hp.posX = 4;
		hp.posY = 4;

		title.fonstSize = 40;

		title.font = globals::defaultText.font;

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
		globals::extraPaddlesTextureID = slLoadTexture(globals::blockNormalTexture.c_str());

		globals::extraPaddleBrickTextureID = slLoadTexture(globals::extraPaddleBrickTexture.c_str());

		globals::tripleDamageBrickTextureID = slLoadTexture(globals::tripleDamageBrickTexture.c_str());

		globals::shootBallBrickTextureID = slLoadTexture(globals::shootBallBrickTexture.c_str());

		globals::pauseTextureID = slLoadTexture(globals::pauseTexture.c_str());

		globals::unmutedIconID = slLoadTexture(globals::unmutedIcon.c_str());

		globals::mutedIconID = slLoadTexture(globals::mutedIcon.c_str());

		globals::defaultText.fontID = slLoadFont(globals::fontText.c_str());

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

	Initializers(tempTexture, block, ball, paddle, score, hp, title, mute, unmute, extraPaddles);

}

void game::Update(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball,
	paddle::Paddle& paddle, text::Text& score, buttons::Button& mute, buttons::Button& unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax], State& state, Cursor& cursor)
{
	sound::PauseUnpauseSong(mute);

	UpdateDeltaTime();

	globals::gameWasPaused = false;

	if (slGetKey(KEY_ESCAPE) || IsKeyPressed(KEY_ESCAPE))
	{
		if (!globals::gameHeldPaused)
		{
			globals::gameWasPaused = true;
		}
		globals::gameHeldPaused = true;
	}
	else
	{
		globals::gameHeldPaused = false;
	}

	if (globals::gameWasPaused)
	{
		globals::gamePaused = !globals::gamePaused;
	}

	if (globals::gamePaused)
	{
		state = State::Pause;
	}

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
					ball::UpdateBlockDurability(block[row][col], ball.damage);
					UpdateMovement(ball, block[row][col]);

					if (paddle.powerUpType == powerup::PowerUpType::TripleDamage)
					{
						if (row > 0)
						{
							ball::UpdateBlockDurability(block[row - 1][col], 1);
						}

						if (row < globals::maxRows - 1)
						{
							ball::UpdateBlockDurability(block[row + 1][col], 1);
						}

						if (col > 0)
						{
							ball::UpdateBlockDurability(block[row][col - 1], 1);
						}

						if (col < globals::maxCols - 1)
						{
							ball::UpdateBlockDurability(block[row][col + 1], 1);
						}

						paddle.powerUpType = powerup::PowerUpType::None;

					}

					if (block[row][col].durability <= 0)
					{
						paddle.score += block[row][col].score;
						if (paddle.powerUpType == powerup::PowerUpType::None)
						{
							paddle.powerUpType = block::PowerUpActivaded(extraPaddles, block[row][col]);
						}
					}
					ball.damage = 1;
				}
			}
		}
	}

	UpdateOnLivesLost(ball, paddle);

	score.text = "Score: " + std::to_string(paddle.score);

	UpdatePowerUp(paddle, extraPaddles, ball);

	if (paddle::LoseCon(paddle))
	{
		state = State::EndScreen;
	}
	else if (block::WinCondition(block))
	{
		state = State::EndScreen;
	}

}

void game::Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
	text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax])
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

	for (int i = 0; i < globals::extraPaddlesMax; i++)
	{
		if (extraPaddles[i].isActive && paddle.powerUpType == powerup::PowerUpType::ExtraPaddles)
		{
			paddle::Draw(extraPaddles[i]);
		}
	}

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

void sound::PauseSounds(Sound sound, int id)
{
	if (globals::usingRaylib)
	{
		PauseSound(sound);
	}
	else
	{
		slSoundPause(id);
	}
}

void sound::UnpauseSounds(Sound sound)
{
	if (globals::usingRaylib)
	{
		ResumeSound(sound);
	}
	else
	{
		slSoundResumeAll();
	}
}

void sound::PauseAll(Sound sound, int id)
{
	if (globals::usingRaylib)
	{
		PauseSound(sound);
	}
	else
	{
		slSoundStopAll();
	}
}

void pause::Update(State& state, Cursor& cursor, text::Text& pauseText, text::Text& returnText, text::Text& retryText)
{
	UpdateMousePosition(cursor);

	pauseText = globals::defaultText;

	pauseText.text = "Game Paused";

	pauseText.posX = 50;
	pauseText.posY = 38;

	returnText = globals::defaultText;

	returnText.text = "menu";

	returnText.color = GRAY;

	returnText.posX = 40;
	returnText.posY = 65;

	if (utils::CheckCollisions(returnText.posX, returnText.posY, 10, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		returnText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Menu;
		}
	}
	else
	{
		returnText.color = GRAY;
	}

	retryText = globals::defaultText;

	retryText.text = "reset";

	retryText.posX = 60;
	retryText.posY = 65;

	if (utils::CheckCollisions(retryText.posX, retryText.posY, 10, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		retryText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			globals::retry = true;
			state = State::Menu;
		}
	}
	else
	{
		retryText.color = GRAY;
	}

	globals::gameWasPaused = false;

	if (slGetKey(KEY_ESCAPE) || IsKeyPressed(KEY_ESCAPE))
	{
		if (!globals::gameHeldPaused)
		{
			globals::gameWasPaused = true;
		}
		globals::gameHeldPaused = true;
	}
	else
	{
		globals::gameHeldPaused = false;
	}

	if (globals::gameWasPaused)
	{
		globals::gamePaused = !globals::gamePaused;
	}

	if (!globals::gamePaused)
	{
		state = State::Play;
	}
}

void pause::Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
	text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax], text::Text pauseText, text::Text returnText, text::Text retryText)
{
	game::Draw(block, ball, paddle, score, hp, mute, unmute, extraPaddles);
	draw::DrawSprite(globals::pauseTextureID, 50, 50, 80, 80, WHITE);

	draw::DrawText(pauseText);
	draw::DrawText(returnText);
	draw::DrawText(retryText);
}
void win::Update(State& state, Cursor& cursor, text::Text& conditionText, text::Text& returnText, text::Text& retryText, text::Text& exit)
{
	UpdateMousePosition(cursor);

	conditionText = globals::defaultText;

	conditionText.text = "You won!";

	conditionText.posX = 50;
	conditionText.posY = 38;

	returnText = globals::defaultText;

	returnText.text = "menu";

	returnText.color = GRAY;

	returnText.posX = 40;
	returnText.posY = 65;

	if (utils::CheckCollisions(returnText.posX, returnText.posY, 10, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		returnText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Menu;
		}
	}
	else
	{
		returnText.color = GRAY;
	}

	retryText = globals::defaultText;

	retryText.text = "reset";

	retryText.posX = 60;
	retryText.posY = 65;

	if (utils::CheckCollisions(retryText.posX, retryText.posY, 10, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		retryText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			globals::retry = true;
			state = State::Menu;
		}
	}
	else
	{
		retryText.color = GRAY;
	}

	exit = globals::defaultText;

	exit.text = "exit";

	exit.posX = 50;
	exit.posY = 68;

	if (utils::CheckCollisions(exit.posX, exit.posY, 10, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		exit.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Exit;
		}
	}
	else
	{
		exit.color = GRAY;
	}

}

void win::Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
	text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax], text::Text conditionText, text::Text returnText, text::Text retryText, text::Text& exit)
{
	game::Draw(block, ball, paddle, score, hp, mute, unmute, extraPaddles);
	draw::DrawSprite(globals::pauseTextureID, 50, 50, 80, 80, WHITE);

	draw::DrawText(conditionText);
	draw::DrawText(returnText);
	draw::DrawText(retryText);
	draw::DrawText(exit);
}

void lost::Update(State& state, Cursor& cursor, text::Text& conditionText, text::Text& returnText, text::Text& retryText, text::Text& exit)
{
	UpdateMousePosition(cursor);

	conditionText = globals::defaultText;

	conditionText.text = "You lost!";

	conditionText.posX = 50;
	conditionText.posY = 38;

	returnText = globals::defaultText;

	returnText.text = "menu";

	returnText.color = GRAY;

	returnText.posX = 40;
	returnText.posY = 65;

	if (utils::CheckCollisions(returnText.posX, returnText.posY, 10, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		returnText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Menu;
		}
	}
	else
	{
		returnText.color = GRAY;
	}

	retryText = globals::defaultText;

	retryText.text = "reset";

	retryText.posX = 60;
	retryText.posY = 65;

	if (utils::CheckCollisions(retryText.posX, retryText.posY, 10, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		retryText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			globals::retry = true;
			state = State::Menu;
		}
	}
	else
	{
		retryText.color = GRAY;
	}

	exit = globals::defaultText;

	exit.text = "exit";

	exit.posX = 50;
	exit.posY = 68;

	if (utils::CheckCollisions(exit.posX, exit.posY, 10, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		exit.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Exit;
		}
	}
	else
	{
		exit.color = GRAY;
	}
}

void lost::Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
	text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute, paddle::Paddle extraPaddles[globals::extraPaddlesMax], text::Text conditionText, text::Text returnText, text::Text retryText, text::Text& exit)
{
	game::Draw(block, ball, paddle, score, hp, mute, unmute, extraPaddles);
	draw::DrawSprite(globals::pauseTextureID, 50, 50, 80, 80, WHITE);

	draw::DrawText(conditionText);
	draw::DrawText(returnText);
	draw::DrawText(retryText);
	draw::DrawText(exit);
}

void credits::Update(State& state, text::Text& creditsText, text::Text& exitText, text::Text& profText, Cursor& cursor)
{
	UpdateMousePosition(cursor);

	creditsText = globals::defaultText;

	creditsText.text = "Made by Eluney Jazmin Mousseigne";

	creditsText.posX = 50;
	creditsText.posY = 20;

	creditsText.fonstSize = 40;

	profText = globals::defaultText;

	profText.text = "Special thanks to Sergio Baretto & Stefano Cvitanich";

	profText.posX = 50;
	profText.posY = 30;

	profText.fonstSize = 30;

	exitText = globals::defaultText;

	exitText.text = "Exit";

	exitText.posX = 5;
	exitText.posY = 95;

	exitText.fonstSize = 30;

	if (utils::CheckCollisions(exitText.posX, exitText.posY, 7, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		exitText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Menu;
		}
	}
	else
	{
		exitText.color = GRAY;
	}
}

void credits::Draw(text::Text creditsText, text::Text exitText, text::Text profText)
{
	DrawBackground();

	draw::DrawText(creditsText);
	draw::DrawText(exitText);
	draw::DrawText(profText);
}

void howtoplay::Update(State& state, text::Text& escapeControl, text::Text& muteControl, text::Text& shootControl, text::Text& moveControl, text::Text& stickyPU,
	text::Text& extraPaddlePU, text::Text& tripleDmgPU, text::Text& exitText, text::Text& powerUpText, Cursor& cursor)
{
	UpdateMousePosition(cursor);

	shootControl = globals::defaultText;

	shootControl.text = " ^         <-  Shoots the ball in a random direction when the game starts";

	shootControl.posX = 60;
	shootControl.posY = 10;

	shootControl.fonstSize = 20;

	moveControl = globals::defaultText;

	moveControl.text = " <    >            <-  Move left and right";

	moveControl.posX = 40;
	moveControl.posY = 15;

	moveControl.fonstSize = 20;

	escapeControl = globals::defaultText;

	escapeControl.text = "ESC            <-  Pause/Unpause game";

	escapeControl.posX = 42;
	escapeControl.posY = 22;

	escapeControl.fonstSize = 20;

	muteControl = globals::defaultText;

	muteControl.text = "M            <-  Mute/Unmute background music";

	muteControl.posX = 47;
	muteControl.posY = 28;

	muteControl.fonstSize = 20;

	stickyPU = globals::defaultText;

	stickyPU.text = " Sticks the ball to your paddle. With up key lauch it directly at your objective";

	stickyPU.posX = 52;
	stickyPU.posY = 42;

	stickyPU.fonstSize = 20;

	stickyPU.color = GREEN;

	extraPaddlePU = globals::defaultText;

	extraPaddlePU.text = "Spawn 3 extra paddles. Each will catch the ball once and then destroy";

	extraPaddlePU.posX = 50;
	extraPaddlePU.posY = 49;

	extraPaddlePU.fonstSize = 20;

	extraPaddlePU.color = VIOLET;

	tripleDmgPU = globals::defaultText;

	tripleDmgPU.text = "The ball will insta-destroy the block it hits and damage the adjacent ones (up to 4)";

	tripleDmgPU.posX = 56;
	tripleDmgPU.posY = 57;

	tripleDmgPU.fonstSize = 20;

	tripleDmgPU.color = RED;

	powerUpText = globals::defaultText;

	powerUpText.text = "You can only have one of these power ups active at a time (first destroyed will active). \nIf you lose the ball while having a power up you will lose it, be careful!\n\n\nTo win, break al the blocks (or lose all the lives...)";

	powerUpText.posX = 50;
	powerUpText.posY = 70;

	powerUpText.fonstSize = 20;

	powerUpText.color = WHITE;

	exitText = globals::defaultText;

	exitText.text = "Exit";

	exitText.posX = 5;
	exitText.posY = 95;

	exitText.fonstSize = 20;

	if (utils::CheckCollisions(exitText.posX, exitText.posY, 7, 5, cursor.radius, cursor.positionX, cursor.positionY))
	{
		exitText.color = WHITE;

		if (utils::IsMouseButtonPressed())
		{
			state = State::Menu;
		}
	}
	else
	{
		exitText.color = GRAY;
	}
}

void howtoplay::Draw(text::Text shootControl, text::Text escapeControl, text::Text muteControl, text::Text moveControl, text::Text stickyPU, text::Text extraPaddlePU,
	text::Text tripleDmgPU, text::Text exitText, text::Text powerUpText)
{
	DrawBackground();

	draw::DrawText(shootControl);
	draw::DrawText(moveControl);
	draw::DrawText(escapeControl);
	draw::DrawText(muteControl);

	draw::DrawSprite(globals::shootBallBrickTextureID, 7, 40, 10, 5, GREEN);
	draw::DrawText(stickyPU);

	draw::DrawSprite(globals::extraPaddleBrickTextureID, 7, 48, 10, 5, VIOLET);
	draw::DrawText(extraPaddlePU);

	draw::DrawSprite(globals::tripleDamageBrickTextureID, 7, 55, 10, 5, RED);
	draw::DrawText(tripleDmgPU);

	draw::DrawText(powerUpText);

	draw::DrawText(exitText);
}

void game::Deinitialize(Texture& tempTexture)
{
	if (globals::usingRaylib)
	{
		UnloadSound(globals::menuSound);
		UnloadSound(globals::playingSound);
		UnloadSound(globals::collisionEffectSound);
		UnloadSound(globals::collisionWithPaddleSound);

		UnloadTexture(tempTexture);

		UnloadFont(globals::defaultText.font);

		CloseAudioDevice();
	}
}