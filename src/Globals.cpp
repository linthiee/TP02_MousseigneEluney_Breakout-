#include "Globals.h"

namespace globals
{
	std::string background = "res/Background_Raylib.png";
	int backgroundTextureID = 0;

	std::string blockNormalTexture = "res/Brick_Texture_Default.png";
	int blockNormalTextureID = 0;

	std::string ballNormalTexture = "res/Ball_Texture.png";
	int ballNormalTextureID = 0;

	std::string paddleTexture = "res/Brick_Texture_Default.png";
	int paddleTextureID = 0;

	std::string extraPaddleBrickTexture = "res/ExtraPaddle_Texture.png";
	int extraPaddleBrickTextureID = 0;

	std::string tripleDamageBrickTexture = "res/TripleDamage_Texture.png";
	int tripleDamageBrickTextureID = 0;

	std::string shootBallBrickTexture = "res/StickBall_Texture.png";
	int shootBallBrickTextureID = 0;

	std::string extraPaddlesTexture = "res/Brick_Texture_Default.png";
	int extraPaddlesTextureID = 0;

	std::string menuTexture = "res/Background_Menu.png";
	int menuTextureID = 0;

	std::string pauseTexture = "res/Background_Paused.png";
	int pauseTextureID = 0;

	std::string mutedIcon = "res/Muted_Icon.png";
	int mutedIconID = 0;

	std::string unmutedIcon = "res/Unmuted_Icon.png";
	int unmutedIconID = 0;

	std::string menuSong = "res/Background_Theme.wav";
	int menuSoundID = 0;
	Sound menuSound;

	std::string playingSong = "res/Playing_Theme.wav";
	int playingSongID = 0;
	Sound playingSound;

	std::string collisionEffect = "res/block_hit_pop.wav";
	int collisionEffectID = 0;
	Sound collisionEffectSound;

	std::string collisionWithPaddle = "res/paddle_bounce_blip.wav";
	int collisionWithPaddleID = 0;
	Sound collisionWithPaddleSound;

	std::string fontText = "res/Pixellari.ttf";
	int font = 0;
	int fontSize = 20;

	float deltaT = 0.0f;

	text::Text defaultText;

	bool muteButtonIsPressed = false;
	bool muteButtonWasPressed = false;

	bool isSongPlaying = false;

	bool usingRaylib = false;

	bool retry = false;

	bool gamePaused = false;
	bool gameHeldPaused = false;
	bool gameWasPaused = false;

	int screenWidth = 825;
	int screenHeight = 525;
}