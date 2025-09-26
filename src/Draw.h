#pragma once

#include "Raylib.h"
#include "Sl.h"
#include "Globals.h"
#include "Utils.h"

namespace draw
{
	void DrawSprite(float id, float posX, float posY, float width, float height, Color color);
	void DrawRec(float posX, float posY, float width, float height, Color color);
	void DrawCirc(float posX, float posY, float radius, Color color);
	void DrawText(text::Text text);
	void DrawButtons(buttons::Button icon);
}
