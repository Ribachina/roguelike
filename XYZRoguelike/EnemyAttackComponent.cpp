#include "EnemyAttackComponent.h"
#include "PlayerSearchComponent.h"
#include "AttackComponent.h"

namespace XYZRoguelike
{
	EnemyAttackComponent::EnemyAttackComponent(XYZEngine::GameObject* gameObject)
		: Component(gameObject)
	{
		
	}
	
	void EnemyAttackComponent::SetPlayerSearch(PlayerSearchComponent* newPlayerSearch)
	{
		playerSearch = newPlayerSearch;
	}

	void EnemyAttackComponent::SetAttack(AttackComponent* newAttack)
	{
		attack = newAttack;
	}

	void EnemyAttackComponent::Update(float deltaTime)
	{
		if (playerSearch == nullptr || attack == nullptr)
		{
			return;
		}

		XYZEngine::GameObject* target = playerSearch->GetTarget();
		if (target == nullptr)
		{
			return;
		}

		attack->TryAttack(target);
	}
	
	void EnemyAttackComponent::Render()
	{

	}
}