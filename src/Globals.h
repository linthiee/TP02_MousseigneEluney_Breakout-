#pragma once
#include <iostream>
#include <ctime>
#include "Raylib.h"

enum class Key
{
	NONE_KEY,
	LEFT_KEY,
	RIGHT_KEY,
	UP_KEY,
	ESCAPE_KEY,
};

extern Texture backgroundTexture;

extern std::string background;
extern int backgroundTextureID;

extern float deltaT;

extern bool usingRaylib;

extern int screenWidth;
extern int screenHeight;

const int minDirecBall = -1;
const int maxDirecBall = 1;

const int maxCols = 10;
const int maxRows = 7;

const int offset = 5;