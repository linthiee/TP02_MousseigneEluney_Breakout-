#include "Draw.h"

void DrawSprite(float id, float posX, float posY, float width, float height, Color color)
{
	if (usingRaylib)
	{
		Texture texture;

		texture.id = id;
		texture.width = (width * screenWidth / 100.0f);
		texture.height = (height * screenHeight / 100.0f);

		DrawTexture(texture, (posX * screenWidth / 100.0f) - ((width / 2) * screenWidth / 100.0f), (posY * screenHeight / 100.0f) - ((height / 2) * screenHeight / 100.0f), color);
	}
	else
	{
		double r = (double)color.r / 220;
		double g = (double)color.g / 220;
		double b = (double)color.b / 220;
		double a = (double)color.a / 220;

		slSetForeColor(r, g, b, a);
		slSprite(id, (posX * screenWidth / 100.0f), screenHeight - (posY * screenHeight / 100.0f), (width * screenWidth / 100.0f), (height * screenHeight / 100.0f));
	}
}

void DrawRec(float posX, float posY, float width, float height, Color color)
{
	if (usingRaylib)
	{
		DrawRectangle((posX * screenWidth / 100.0f) - ((width / 2) * screenWidth / 100.0f), (posY * screenHeight / 100.0f) - ((height / 2) * screenHeight / 100.0f), (width * screenWidth / 100.0f), (height * screenHeight / 100.0f), color);
	}
	else
	{
		double r = (double)color.r / 255;
		double g = (double)color.g / 255;
		double b = (double)color.b / 255;
		double a = (double)color.a / 255;

		slSetForeColor(r, g, b, a);
		slRectangleFill((posX * screenWidth / 100.0f), screenHeight - (posY * screenHeight / 100.0f), (width * screenWidth / 100.0f), (height * screenHeight / 100.0f));
	}
}

void DrawCirc(float posX, float posY, float radius, Color color)
{
	if (usingRaylib)
	{
		DrawCircle((posX * screenWidth / 100.0f), (posY * screenHeight / 100.0f), (radius * screenHeight / 100.0f), color);
	}
	else
	{
		double r = (double)color.r / 255;
		double g = (double)color.g / 255;
		double b = (double)color.b / 255;
		double a = (double)color.a / 255;

		slSetForeColor(r, g, b, a);
		slCircleFill((posX * screenWidth / 100.0f), screenHeight - (posY * screenHeight / 100.0f), (radius * screenHeight / 100.0f), (double)radius * 200);
	}
}

void DrawText(text::Text text)
{

	if (usingRaylib)
	{
		DrawTextEx(text.font, text.text.c_str(), { (text.posX * screenWidth / 100.0f) - (MeasureText(text.text.c_str(), text.fonstSize)) / 2, (text.posY * screenHeight / 100.0f) - (text.fonstSize / 2) }, text.fonstSize, text.spacing, text.color);
	}
	else
	{
		slSetFont(font, (int)text.fonstSize);
		slText((text.posX * screenWidth / 100.0f) - slGetTextWidth(text.text.c_str()) / 2, screenHeight - (text.posY * screenHeight / 100.0f), text.text.c_str());
	}
}

void DrawButtons(buttons::Button icon)
{
	DrawSprite(icon.currentTextureID, icon.posX, icon.posY, icon.width, icon.height, icon.color);
}
