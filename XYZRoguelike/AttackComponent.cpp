#include "AttackComponent.h"
#include "CharacterStatsComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Vector.h"
#include "Logger.h"
#include <algorithm>
#include <cassert>

namespace XYZRoguelike
{
	AttackComponent::AttackComponent(XYZEngine::GameObject* gameObject)
		: Component(gameObject)
	{
		transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		assert(transform != nullptr && "TransformComponent is required for AttackComponent");
	}

	void AttackComponent::Update(float deltaTime)
	{
		if (cooldownTimer > 0.f)
		{
			cooldownTimer -= deltaTime;

			if (cooldownTimer < 0.f)
			{
				cooldownTimer = 0.f;
			}
		}
	}

	void AttackComponent::Render()
	{

	}

	void AttackComponent::SetDamage(int newDamage)
	{
		damage = std::max(0, newDamage);
	}

	int AttackComponent::GetDamage() const
	{
		return damage;
	}

	void AttackComponent::SetAttackRange(float newAttackRange)
	{
		attackRange = std::max(0.f, newAttackRange);
	}

	float AttackComponent::GetAttackRange() const
	{
		return attackRange;
	}

	void AttackComponent::SetAttackCooldown(float newCooldown)
	{
		attackCooldown = std::max(0.f, newCooldown);
	}

	float AttackComponent::GetAttackCooldown() const
	{
		return attackCooldown;
	}

	bool AttackComponent::TryAttack(XYZEngine::GameObject* target)
	{
		if (target == nullptr)
		{
			return false;
		}

		if (cooldownTimer > 0.f)
		{
			return false;
		}

		auto targetStats = target->GetComponent<CharacterStatsComponent>();
		if (targetStats == nullptr)
		{
			return false;
		}

		auto targetTransform = target->GetComponent<XYZEngine::TransformComponent>();
		if (targetTransform == nullptr)
		{
			return false;
		}

		XYZEngine::Vector2Df attackerPosition = transform->GetLocalPosition();
		XYZEngine::Vector2Df targetPosition = targetTransform->GetLocalPosition();
		XYZEngine::Vector2Df toTarget = targetPosition - attackerPosition;

		const float distance = toTarget.GetLength();
		if (distance > attackRange)
		{
			return false;
		}

		targetStats->TakeDamage(damage);
		cooldownTimer = attackCooldown;

		LOG_INFO(gameObject->GetName() + " attacked " + target->GetName() + " to " + std::to_string(damage) + " damage");

		return true;

	}

	
}