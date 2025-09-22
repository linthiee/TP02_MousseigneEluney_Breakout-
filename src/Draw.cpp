#include "Draw.h"

void DrawSprite(float id, float posX, float posY, float width, float height, Color color)
{
	if (usingRaylib)
	{
		Texture texture;

		texture.id = id;
		texture.width = (width * screenWidth / 100.0f);
		texture.height =  (height * screenHeight / 100.0f);

		DrawTexture(texture, (posX * screenWidth / 100.0f) - ((width / 2) * screenWidth / 100.0f), (posY * screenHeight / 100.0f) - ((height / 2) * screenHeight / 100.0f), color);
	}
	else
	{
		double r = (double)color.r / 128;
		double g = (double)color.g / 128;
		double b = (double)color.b / 128;
		double a = (double)color.a / 128;

		slSetForeColor(r, g, b, a);
		slSprite(id, (posX * screenWidth / 100.0f), screenHeight - (posY * screenHeight / 100.0f), (width * screenWidth / 100.0f), (height * screenHeight / 100.0f));
	}
}

void DrawRec(float posX, float posY, float width, float height, Color color)
{
	if (usingRaylib)
	{
		DrawRectangle((posX * screenWidth / 100.0f) - ((width / 2)*screenWidth/100.0f), (posY * screenHeight / 100.0f) - ((height / 2) * screenHeight / 100.0f), (width * screenWidth / 100.0f), (height * screenHeight / 100.0f), color);
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
		DrawCircle((posX * screenWidth / 100.0f), (posY * screenHeight / 100.0f), (radius*screenHeight/100.0f), color);
	}
	else
	{
		double r = (double)color.r / 255;
		double g = (double)color.g / 255;
		double b = (double)color.b / 255;
		double a = (double)color.a / 255;

		slSetForeColor(r, g, b, a);
		slCircleFill((posX * screenWidth / 100.0f),screenHeight - (posY * screenHeight / 100.0f), (radius * screenHeight / 100.0f), (double)radius * 200);
	}
}
