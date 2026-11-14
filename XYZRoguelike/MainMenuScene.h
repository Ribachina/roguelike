#pragma once

#include "Scene.h"
#include <memory>

namespace XYZEngine
{
	class GameObject;
}

namespace XYZRoguelike
{
	class DeveloperLevel;
	
	
	// √лавное меню. ”правл€ет созданием-удалением объектов в меню, ну и музыкой в меню заодно
	class MainMenuScene : public XYZEngine::Scene
	{
	public:
		MainMenuScene(std::shared_ptr<DeveloperLevel> developerLevel);

		void Start() override;
		void Restart() override;
		void Stop() override;
		
		void StartGame();

	private:
		std::shared_ptr<DeveloperLevel> developerLevel;
		XYZEngine::GameObject* menuObject = nullptr;
	};
}
