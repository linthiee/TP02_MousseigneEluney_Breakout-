#pragma once

#include <string>
#include "Draw.h"
#include "Globals.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Utils.h"
#include "Menu.h"

enum class State
{
	Menu, Play, Credits, Pause, EndScreen, Exit
};

void MainLoop();

void Initializers(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score,
	text::Text& hp, text::Text& title, buttons::Button& mute, buttons::Button& unmute);

void DrawBackground();

void UpdateDeltaTime();

int ScreenWidth();
int ScreenHeight();

void InitializeWindow(int screenWidth, int screenHeight, std::string title = "Breakout");

bool WindowClosed();
void EndWindow();

void StartDrawing();
void FinishDrawing();

namespace game
{
	void Initialization(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle, text::Text& score,
		text::Text& hp, text::Text& title, buttons::Button& mute, buttons::Button& unmute);
	void Update(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
		text::Text& score, buttons::Button& mute, buttons::Button& unmute);
	void Draw(block::Block block[globals::maxRows][globals::maxCols], ball::Ball& ball, paddle::Paddle& paddle,
		text::Text score, text::Text hp, buttons::Button mute, buttons::Button unmute);
}

namespace sound
{
	void SetSound(Sound sound, int soundID);
	void SetPlayingSound();
	void PauseUnpauseSong(buttons::Button& mute);
}