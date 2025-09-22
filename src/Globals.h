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

extern std::string background;
extern int backgroundTextureID;

extern std::string blockNormalTexture;
extern int blockNormalTextureID;

extern std::string ballNormalTexture;
extern int ballNormalTextureID;

extern float deltaT;

extern bool usingRaylib;

extern int screenWidth;
extern int screenHeight;

const int minDirecBall = 0;
const int maxDirecBall = 20;

const int maxCols = 8;
const int maxRows = 7;
