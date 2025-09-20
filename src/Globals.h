#pragma once

enum class Key
{
	NONE_KEY,
	LEFT_KEY,
	RIGHT_KEY,
	UP_KEY,
	ESCAPE_KEY,
};

extern float deltaT;

extern bool usingRaylib;

extern int screenWidth;
extern int screenHeight;

const int maxCols = 10;
const int maxRows = 7;