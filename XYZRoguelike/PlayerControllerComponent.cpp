#include "PlayerControllerComponent.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "RigidbodyComponent.h"
#include "AudioComponent.h"
#include "Vector.h"
#include "ResourceSystem.h"

namespace XYZRoguelike
{
	PlayerControllerComponent::PlayerControllerComponent(XYZEngine::GameObject* gameObject)
		: Component(gameObject)
	{
		input = gameObject->GetComponent<XYZEngine::InputComponent>();
		rigidbody = gameObject->GetComponent<XYZEngine::RigidbodyComponent>();
		audio = gameObject->GetComponent<XYZEngine::AudioComponent>();
		stepSound = XYZEngine::ResourceSystem::Instance()->GetSoundBufferShared("step_01");
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
	}
	void PlayerControllerComponent::Render()
	{
	}
}