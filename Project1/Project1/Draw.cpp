#include "Draw.h"

void DrawRec(int posX, int posY, int width, int height, Color color)
{
	if (usingRaylib)
	{
		DrawRectangle(posX - width / 2, posY - height / 2, width, height, color);
	}
	else
	{
		double r = (double)color.r / 255;
		double g = (double)color.g / 255;
		double b = (double)color.b / 255;
		double a = (double)color.a / 255;

		slSetForeColor(r, g, b, a);
		slRectangleFill(posX, screenHeight - posY, width, height);
	}
}

void DrawCirc(int posX, int posY, float radius, Color color)
{
	if (usingRaylib)
	{
		DrawCircle(posX, posY, radius, color);
	}
	else
	{
		double r = (double)color.r / 255;
		double g = (double)color.g / 255;
		double b = (double)color.b / 255;
		double a = (double)color.a / 255;

		slSetForeColor(r, g, b, a);
		slCircleFill((double)posX, screenHeight - (double)posY, (double)radius, (double)radius * 200);
	}
}
