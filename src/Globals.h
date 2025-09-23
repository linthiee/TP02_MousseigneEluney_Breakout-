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

extern std::string paddleTexture;
extern int paddleTextureID;

extern std::string mutedIcon;
extern int mutedIconID;

extern std::string unmutedIcon;
extern int unmutedIconID;

extern std::string menuTexture;
extern int menuTextureID;

extern std::string menuSong;
extern int menuSoundID;
extern Sound menuSound;

extern std::string fontText;
extern int font;
extern int fontSize;

extern float deltaT;

extern bool usingRaylib;

extern int screenWidth;
extern int screenHeight;

const int minDirecBall = 0;
const int maxDirecBall = 20;

const int maxCols = 8;
const int maxRows = 7;
