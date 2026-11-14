#include "MainMenuScene.h"
#include "MainMenuComponent.h"
#include "DeveloperLevel.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "ResourceSystem.h"

namespace XYZRoguelike
{
	MainMenuScene::MainMenuScene(std::shared_ptr<DeveloperLevel> developerLevel)
		: developerLevel(developerLevel)
	{

	}

	void MainMenuScene::Start()
	{
		menuObject = XYZEngine::GameWorld::Instance()->CreateGameObject("MainMenu");

		auto menuComponent = menuObject->AddComponent<MainMenuComponent>();
		menuComponent->SetMenuScene(this);

		sf::Music* menuMusic = XYZEngine::ResourceSystem::Instance()->GetMusic("music_menu");
		if (menuMusic != nullptr)
		{
			menuMusic->setLoop(true);
			menuMusic->play();
		}
	}

	void MainMenuScene::Restart()
	{
		Stop();
		Start();
	}

	void MainMenuScene::Stop()
	{
		sf::Music* menuMusic = XYZEngine::ResourceSystem::Instance()->GetMusic("music_menu");
		if (menuMusic != nullptr)
		{
			menuMusic->stop();
		}

		if (menuObject != nullptr)
		{
			XYZEngine::GameWorld::Instance()->DestroyGameObject(menuObject);
			menuObject = nullptr;
		}
	}

	void MainMenuScene::StartGame()
	{
		Stop();

		if (developerLevel != nullptr)
		{
			developerLevel->Start();
		}
	}
}