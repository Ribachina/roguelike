#include "MainMenuComponent.h"
#include "MainMenuScene.h"
#include "RenderSystem.h"
#include "Text.h"
#include <assert.h>

namespace XYZRoguelike
{
	MainMenuComponent::MainMenuComponent(XYZEngine::GameObject* gameObject)
		: Component(gameObject)
	{
		const bool fontLoaded = font.loadFromFile("Resources/Fonts/Roboto-Regular.ttf");
		assert(fontLoaded);

		MenuItem startGame;
		startGame.text.setString("Start Game");
		startGame.text.setFont(font);
		startGame.text.setCharacterSize(24);
		startGame.onPressCallback = [this](MenuItem&)
			{
				if (menuScene != nullptr)
				{
					menuScene->StartGame();
				}
			};

		MenuItem options;
		options.text.setString("Options");
		options.text.setFont(font);
		options.text.setCharacterSize(24);
		options.onPressCallback = [](MenuItem&)
			{

			};

		MenuItem exitGame;
		exitGame.text.setString("Exit Game");
		exitGame.text.setFont(font);
		exitGame.text.setCharacterSize(24);
		exitGame.onPressCallback = [](MenuItem&)
			{

			};

		MenuItem mainMenu;
		mainMenu.hintText.setString("Roguelike");
		mainMenu.hintText.setFont(font);
		mainMenu.hintText.setCharacterSize(48);
		mainMenu.hintText.setFillColor(sf::Color::Yellow);

		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;

		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(options);
		mainMenu.childrens.push_back(exitGame);

		menu.Init(mainMenu);
	}

	void MainMenuComponent::SetMenuScene(MainMenuScene* scene)
	{
		menuScene = scene;
	}

	void MainMenuComponent::Update(float deltaTime)
	{
		const bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		const bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		const bool enterPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
		const bool escapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

		Orientation orientation = menu.GetCurrentContext().childrenOrientation;

		if (escapePressed && !escapeWasPressed)
		{
			menu.GoBack();
		}

		if (enterPressed && !enterWasPressed)
		{
			enterWasPressed = enterPressed;
			menu.PressOnSelectedItem();
			return;
		}

		if (orientation == Orientation::Vertical)
		{
			if (upPressed && !upWasPressed)
			{
				menu.SwitchToPreviousMenuItem();
			}

			if (downPressed && !downWasPressed)
			{
				menu.SwitchToNextMenuItem();
			}
		}

		upWasPressed = upPressed;
		downWasPressed = downPressed;
		enterWasPressed = enterPressed;
		escapeWasPressed = escapePressed;
	}

	void MainMenuComponent::Render()
	{
		auto& window = XYZEngine::RenderSystem::Instance()->GetMainWindow();

		sf::Vector2f viewSize = window.getView().getSize();
		sf::Text& hintText = menu.GetCurrentContext().hintText;

		hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 0.f }));
		hintText.setPosition(viewSize.x / 2.f, 150.f);

		window.draw(hintText);
		menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}

}