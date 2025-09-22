#include "Menu.h"

void menu::Update(State& state)
{
	PlaySound(menuSound);
}

void menu::Draw()
{
	DrawSprite(menuTextureID, 50, 50, 100, 100, WHITE);
}
