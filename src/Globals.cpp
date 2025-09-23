#include "Globals.h"

std::string background = "res/Background_Image.png";
int backgroundTextureID = 0;

std::string blockNormalTexture = "res/Brick_Texture_Default.png";
int blockNormalTextureID = 0;

std::string ballNormalTexture = "res/Ball_Texture.png";
int ballNormalTextureID = 0;

std::string paddleTexture = "res/Brick_Texture_Default.png";
int paddleTextureID = 0;

std::string menuTexture = "res/Background_Menu.png";
int menuTextureID = 0;

std::string menuSong = "res/Background_Theme.wav";
int menuSoundID = 0;
Sound menuSound;

std::string fontText = "res/Pixellari.ttf";
int font = 0;
int fontSize = 20;

float deltaT = 0.0f;

bool usingRaylib = false;

int screenWidth = 825;
int screenHeight = 525;