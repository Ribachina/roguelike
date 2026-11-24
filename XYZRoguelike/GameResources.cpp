#include "GameResources.h"
#include "ResourceSystem.h"
#include "Logger.h"

namespace XYZRoguelike
{
	void GameResources::Load()
	{
		LOG_INFO("Loading game resources");
		
		auto resources = XYZEngine::ResourceSystem::Instance();

		resources->LoadTexture("ball", "Resources/Textures/ball.png");
		resources->LoadTexture("rat", "Resources/Textures/rat.png");
		resources->LoadTexture("knight", "Resources/Textures/knight.png");
		resources->LoadSoundBuffer("hurt_01", "Resources/Sounds/hurt_01.ogg");
		resources->LoadSoundBuffer("step_01", "Resources/Sounds/step_01.wav");
		resources->LoadMusic("music_menu", "Resources/Musics/music_menu.ogg");
		resources->LoadMusic("music_game", "Resources/Musics/music_game.ogg");

		LOG_INFO("Game resources loaded");
	}
}