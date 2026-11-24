#include "PlayerSearchComponent.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Vector.h"
#include <iostream>
#include <cassert>

namespace XYZRoguelike
{
	PlayerSearchComponent::PlayerSearchComponent(XYZEngine::GameObject* gameObject)
		: Component(gameObject)
	{
		transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		assert(transform != nullptr && "TransformComponent is required for PlayerSearchComponent"); // Объект врага обязан иметь Transform
	}


	void XYZRoguelike::PlayerSearchComponent::Update(float deltaTime)
	{
		XYZEngine::GameObject* player = XYZEngine::GameWorld::Instance()->FindGameObject("Player");

		if (player == nullptr)
		{
			target = nullptr;
			return;
		}

		auto playerTransform = player->GetComponent<XYZEngine::TransformComponent>();
		if (transform == nullptr || playerTransform == nullptr)
		{
			target = nullptr;
			return;
		}

		XYZEngine::Vector2Df enemyPosition = transform->GetLocalPosition();
		XYZEngine::Vector2Df playerPosition = playerTransform->GetLocalPosition();
		XYZEngine::Vector2Df toPlayer = playerPosition - enemyPosition;
		
		float distance = toPlayer.GetLength();
		if (distance <= detectionRadius)
		{
			target = player;
		}
		else
		{
			target = nullptr;
		}
	}	

	void PlayerSearchComponent::Render()
	{

	}

	XYZEngine::GameObject* PlayerSearchComponent::GetTarget() const
	{
		return target;
	}

	void PlayerSearchComponent::SetDetectionRadius(float radius)
	{
		detectionRadius = radius;
	}
}
