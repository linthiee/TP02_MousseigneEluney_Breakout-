#pragma once

enum class State
{
	Menu, Play, Credits, Pause, EndScreen, Exit
};

#include <string>
#include "Draw.h"
#include "Globals.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

void MainLoop();

void Initializers(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle);

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
	void Initialization(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle);
	void Update(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle);
	void Draw(block::Block block[maxRows][maxCols], ball::Ball& ball, paddle::Paddle& paddle);
}
