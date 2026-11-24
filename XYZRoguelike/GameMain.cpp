// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "DeveloperLevel.h"
#include "GameResources.h"
#include "MainMenuScene.h"
#include "Logger.h"


using namespace XYZRoguelike;

int main()
{
	XYZEngine::SetupLogger();
	LOG_INFO("Application started");
	
	XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "XYZRoguelike"));

	GameResources::Load();

	auto developerLevel = std::make_shared<DeveloperLevel>();
	auto mainMenuScene = std::make_shared<MainMenuScene>(developerLevel);

	mainMenuScene->Start();
	

	XYZEngine::Engine::Instance()->Run();

	return 0;
}
