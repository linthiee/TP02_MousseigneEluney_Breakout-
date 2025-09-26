#pragma once
#include <iostream>
#include <ctime>
#include "Raylib.h"

namespace globals
{
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

	extern std::string playingSong;
	extern int playingSongID;
	extern Sound playingSound;

	extern std::string collisionEffect;
	extern int collisionEffectID;
	extern Sound collisionEffectSound;

	extern std::string collisionWithPaddle;
	extern int collisionWithPaddleID;
	extern Sound collisionWithPaddleSound;

	extern std::string fontText;
	extern int font;
	extern int fontSize;

	extern float deltaT;

	extern bool usingRaylib;

	extern bool muteButtonIsPressed;
	extern bool muteButtonWasPressed;

	extern int screenWidth;
	extern int screenHeight;

	const int minDirecBall = 0;
	const int maxDirecBall = 20;

	const int minProb = 1.0f;
	const int maxProb = 100.0f;
	const int probRange = (maxProb - minProb + 1);

	const int maxPowerUpsPerCol = 3;

	const int shootBallProb = 20;
	const int extraPaddlesProb = 30;
	const int doubleDmgProb = 40;
	const int extraBallProb = 50;

	const int maxCols = 8;
	const int maxRows = 7;
}
