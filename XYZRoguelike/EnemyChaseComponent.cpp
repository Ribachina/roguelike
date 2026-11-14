#include "EnemyChaseComponent.h"
#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "PlayerSearchComponent.h"
#include "Vector.h"

namespace XYZRoguelike
{
	EnemyChaseComponent::EnemyChaseComponent(XYZEngine::GameObject* gameObject)
		: Component(gameObject)
	{
		rigidbody = gameObject->GetComponent<XYZEngine::RigidbodyComponent>();
		playerSearch = gameObject->GetComponent<PlayerSearchComponent>();
	}
	void EnemyChaseComponent::Update(float deltaTime)
	{
		if (rigidbody == nullptr || playerSearch == nullptr)
		{
			return;
		}

		XYZEngine::GameObject* target = playerSearch->GetTarget();
		if (target == nullptr)
		{
			rigidbody->SetLinearVelocity({ 0.f, 0.f });
			return;
		}

		auto enemyTransform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		auto targetTransform = target->GetComponent<XYZEngine::TransformComponent>();
		if (enemyTransform == nullptr || targetTransform == nullptr)
		{
			rigidbody->SetLinearVelocity({ 0.f, 0.f });
			return;
		}

		XYZEngine::Vector2Df toTarget = targetTransform->GetWorldPosition() - enemyTransform->GetWorldPosition();

		float distance = toTarget.GetLength();
		if (distance == 0.f)
		{
			rigidbody->SetLinearVelocity({ 0.f, 0.f });
			return;
		}

		XYZEngine::Vector2Df direction = toTarget * (1.f / distance);

		rigidbody->SetLinearVelocity(direction * moveSpeed);
	}
	
	void EnemyChaseComponent::Render()
	{

	}

	void EnemyChaseComponent::SetMoveSpeed(float speed)
	{
		moveSpeed = speed;
	}

}


