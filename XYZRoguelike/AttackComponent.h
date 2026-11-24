#pragma once
#include "Component.h"

namespace XYZEngine
{
	class GameObject;
	class TransformComponent;
}

namespace XYZRoguelike
{
	class AttackComponent : public XYZEngine::Component
	{
	public:
		AttackComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetDamage(int newDamage);
		int GetDamage() const;

		void SetAttackRange(float newAttackRange);
		float GetAttackRange() const;

		void SetAttackCooldown(float newCooldown);
		float GetAttackCooldown() const;

		bool TryAttack(XYZEngine::GameObject* target);

	private:
		XYZEngine::TransformComponent* transform = nullptr;

		int damage = 10;
		float attackRange = 40.f;
		float attackCooldown = 1.f;
		float cooldownTimer = 0.f;
	};
}
