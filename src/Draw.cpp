#include "Draw.h"

void draw::DrawSprite(float id, float posX, float posY, float width, float height, Color color)
{
	if (globals::usingRaylib)
	{
		Texture texture;

		texture.id = id;
		texture.width = (width * globals::screenWidth / 100.0f);
		texture.height = (height * globals::screenHeight / 100.0f);

		DrawTexture(texture, (posX * globals::screenWidth / 100.0f) - ((width / 2) * globals::screenWidth / 100.0f), (posY * globals::screenHeight / 100.0f) - ((height / 2) * globals::screenHeight / 100.0f), color);
	}
	else
	{
		double r = (double)color.r / 220;
		double g = (double)color.g / 220;
		double b = (double)color.b / 220;
		double a = (double)color.a / 220;

		slSetForeColor(r, g, b, a);
		slSprite(id, (posX * globals::screenWidth / 100.0f), globals::screenHeight - (posY * globals::screenHeight / 100.0f), (width * globals::screenWidth / 100.0f), (height * globals::screenHeight / 100.0f));
	}
}

void draw::DrawRec(float posX, float posY, float width, float height, Color color)
{
	if (globals::usingRaylib)
	{
		DrawRectangle((posX * globals::screenWidth / 100.0f) - ((width / 2) * globals::screenWidth / 100.0f), (posY * globals::screenHeight / 100.0f) - ((height / 2) * globals::screenHeight / 100.0f), (width * globals::screenWidth / 100.0f), (height * globals::screenHeight / 100.0f), color);
	}
	else
	{
		double r = (double)color.r / 255;
		double g = (double)color.g / 255;
		double b = (double)color.b / 255;
		double a = (double)color.a / 255;

		slSetForeColor(r, g, b, a);
		slRectangleFill((posX * globals::screenWidth / 100.0f), globals::screenHeight - (posY * globals::screenHeight / 100.0f), (width * globals::screenWidth / 100.0f), (height * globals::screenHeight / 100.0f));
	}
}

void draw::DrawCirc(float posX, float posY, float radius, Color color)
{
	if (globals::usingRaylib)
	{
		DrawCircle((posX * globals::screenWidth / 100.0f), (posY * globals::screenHeight / 100.0f), (radius * globals::screenHeight / 100.0f), color);
	}
	else
	{
		double r = (double)color.r / 255;
		double g = (double)color.g / 255;
		double b = (double)color.b / 255;
		double a = (double)color.a / 255;

		slSetForeColor(r, g, b, a);
		slCircleFill((posX * globals::screenWidth / 100.0f), globals::screenHeight - (posY * globals::screenHeight / 100.0f), (radius * globals::screenHeight / 100.0f), (double)radius * 200);
	}
}

void draw::DrawText(text::Text text)
{
	if (globals::usingRaylib)
	{
		DrawTextEx(text.font, text.text.c_str(), { (text.posX * globals::screenWidth / 100.0f) - (MeasureText(text.text.c_str(), text.fonstSize)) / 2, (text.posY * globals::screenHeight / 100.0f) - (text.fonstSize / 2) }, text.fonstSize, text.spacing, text.color);
	}
	else
	{
		slSetFont(globals::font, (int)text.fonstSize);
		slText((text.posX * globals::screenWidth / 100.0f) - slGetTextWidth(text.text.c_str()) / 2, globals::screenHeight - (text.posY * globals::screenHeight / 100.0f), text.text.c_str());
	}
}

void draw::DrawButtons(buttons::Button icon)
{
	draw::DrawSprite(icon.currentTextureID, icon.posX, icon.posY, icon.width, icon.height, icon.color);
}
