#pragma once
#include "Component.h"
#include <SFML/Audio.hpp>

namespace XYZEngine
{
	class InputComponent;
	class RigidbodyComponent;
	class AudioComponent;
}

namespace XYZRoguelike
{
	class AttackComponent;
	
	// Класс управления игроком
	class PlayerControllerComponent : public XYZEngine::Component
	{
	public:
		PlayerControllerComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

	private:
		XYZEngine::InputComponent* input = nullptr;
		XYZEngine::RigidbodyComponent* rigidbody = nullptr;
		XYZEngine::AudioComponent* audio = nullptr;

		const sf::SoundBuffer* stepSound = nullptr;
		const sf::SoundBuffer* hurtSound = nullptr;

		float moveSpeed = 200.f;

		float stepTimer = 0.f;
		float stepInterval = 0.35f;

		AttackComponent* attack = nullptr;
		bool attackWasPressed = false;
	};
}
