#pragma once

#include "Component.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>

namespace XYZRoguelike
{
	class MainMenuScene;

	
	// Интерфейс главного меню. Обработка ввода, переключение пунктов и отрисовка
	class MainMenuComponent : public XYZEngine::Component
	{
	public:
		MainMenuComponent(XYZEngine::GameObject* gameObject);

		void SetMenuScene(MainMenuScene* scene);
		
		void Update(float deltaTime) override;
		void Render() override;

	private:
		MainMenuScene* menuScene = nullptr;

		sf::Font font;
		Menu menu;

		bool upWasPressed = false;
		bool downWasPressed = false;
		bool enterWasPressed = false;
		bool escapeWasPressed = false;
	};
}