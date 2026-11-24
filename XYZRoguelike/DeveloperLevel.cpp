#include "DeveloperLevel.h"
#include "ResourceSystem.h"
#include "Logger.h"

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		LOG_INFO("Developer level started");
		
		player = std::make_shared<Player>();
		ratEnemy = std::make_shared<RatEnemy>();

		sf::Music* gameMusic = XYZEngine::ResourceSystem::Instance()->GetMusic("music_game");
		if (gameMusic != nullptr)
		{
			gameMusic->setLoop(true);
			gameMusic->play();

			LOG_INFO("Game music started");
		}
		else
		{
			LOG_WARNING("Game music resource not founded");
		}

		walls.push_back(std::make_shared<Wall>(0.f, -300.f, 800.f, 32.f));
		walls.push_back(std::make_shared<Wall>(0.f, 300.f, 800.f, 32.f));
		walls.push_back(std::make_shared<Wall>(-400.f, 0.f, 32.f, 600.f));
		walls.push_back(std::make_shared<Wall>(400.f, 0.f, 32.f, 600.f));
	}
	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}
	void DeveloperLevel::Stop() 
	{
		LOG_INFO("Developer level stopped");
		
		sf::Music* gameMusic = XYZEngine::ResourceSystem::Instance()->GetMusic("music_game");
		if (gameMusic != nullptr)
		{
			gameMusic->stop();
		}
		
		GameWorld::Instance()->Clear();
	}
}