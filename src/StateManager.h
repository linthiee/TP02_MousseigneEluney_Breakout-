#pragma once

#include <string>
#include "Draw.h"
#include "Globals.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

void MainLoop();

void Initializers(block::Block block[maxRows][maxCols]);

void DrawBackground();

void UpdateDeltaTime();

int ScreenWidth();
int ScreenHeight();

void InitializeWindow(int screenWidth, int screenHeight, std::string title = "Breakout");

bool WindowClosed();
void EndWindow();

void StartDrawing();
void FinishDrawing();
