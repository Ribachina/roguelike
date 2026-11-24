#include "PlayerControllerComponent.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "RigidbodyComponent.h"
#include "AudioComponent.h"
#include "Vector.h"
#include "ResourceSystem.h"
#include "AttackComponent.h"
#include "GameWorld.h"
#include <cassert>
#include "Logger.h"

namespace XYZRoguelike
{
	PlayerControllerComponent::PlayerControllerComponent(XYZEngine::GameObject* gameObject)
		: Component(gameObject)
	{
		input = gameObject->GetComponent<XYZEngine::InputComponent>();
		rigidbody = gameObject->GetComponent<XYZEngine::RigidbodyComponent>();
		audio = gameObject->GetComponent<XYZEngine::AudioComponent>();
		stepSound = XYZEngine::ResourceSystem::Instance()->GetSoundBufferShared("step_01");

		attack = gameObject->GetComponent<AttackComponent>();
		assert(attack != nullptr && "AttackComponent is required for PlayerControllerComponent");
	}
	
	void PlayerControllerComponent::Update(float deltaTime)
	{
		float horizontal = input->GetHorizontalAxis();
		float vertical = input->GetVerticalAxis();

		XYZEngine::Vector2Df direction{ horizontal, vertical };

		rigidbody->SetLinearVelocity(direction * moveSpeed);

		const bool isMoving = horizontal != 0.f || vertical != 0.f;
		if (isMoving)
		{
			stepTimer += deltaTime;

			if (stepTimer >= stepInterval)
			{
				if (stepSound != nullptr)
				{
				audio->SetBuffer(*stepSound);
				audio->Play();
				}
				
				stepTimer = 0.f;
			}
		}
		else
		{
			stepTimer = 0.f;
		}

		const bool attackPressed = input->IsKeyPressed(sf::Keyboard::Space);
		if (attackPressed && !attackWasPressed)
		{
			XYZEngine::GameObject* enemy = XYZEngine::GameWorld::Instance()->FindGameObject("Enemy");

			if (enemy == nullptr)
			{
				LOG_WARNING("Enemy not founded");
			}
			else if (attack == nullptr)
			{
				LOG_ERROR("Player AttackComponent is missing");
			}

			attack->TryAttack(enemy);
		}

		attackWasPressed = attackPressed;
	}
	void PlayerControllerComponent::Render()
	{
	}
}