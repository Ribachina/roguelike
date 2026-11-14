#include "GameResources.h"
#include "ResourceSystem.h"

namespace XYZRoguelike
{
	void GameResources::Load()
	{
		auto resources = XYZEngine::ResourceSystem::Instance();

		resources->LoadTexture("ball", "Resources/Textures/ball.png");
		resources->LoadSoundBuffer("hurt_01", "Resources/Sounds/hurt_01.ogg");
		resources->LoadSoundBuffer("step_01", "Resources/Sounds/step_01.wav");
		resources->LoadMusic("music_menu", "Resources/Musics/music_menu.ogg");
		resources->LoadMusic("music_game", "Resources/Musics/music_game.ogg");
	}
}