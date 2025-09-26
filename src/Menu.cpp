#include "Menu.h"

//void menu::Update(State& state)
//{
//
//}

void menu::Draw(text::Text title)
{
	draw::DrawSprite(globals::menuTextureID, 50, 50, 100, 100, WHITE);

	draw::DrawText(title);
}
