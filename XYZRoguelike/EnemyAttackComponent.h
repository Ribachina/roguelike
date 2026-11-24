#pragma once
#include "Component.h"

namespace XYZRoguelike
{
	class PlayerSearchComponent;
	class AttackComponent;

	class EnemyAttackComponent : public XYZEngine::Component
	{
	public:
		EnemyAttackComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetPlayerSearch(PlayerSearchComponent* newPlayerSearch);
		void SetAttack(AttackComponent* newAttack);

	private:
		PlayerSearchComponent* playerSearch = nullptr;
		AttackComponent* attack = nullptr;
	};
}
