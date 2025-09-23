#include "Menu.h"
//#include "Menu.h"

void menu::Update(State& state)
{

}

void menu::Draw(text::Text title)
{
	DrawSprite(menuTextureID, 50, 50, 100, 100, WHITE);

	DrawText(title);
}
