#include "Enemy.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "PlayerSearchComponent.h"
#include "EnemyChaseComponent.h"
#include "CharacterStatsComponent.h"
#include "AttackComponent.h"
#include "EnemyAttackComponent.h"

namespace XYZRoguelike
{
	Enemy::Enemy()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
	}

	XYZEngine::GameObject* Enemy::GetGameObject()
	{
		return gameObject;
	}

	void Enemy::SetupAI(float detectionRadius, float moveSpeed)
	{
		playerSearch = gameObject->AddComponent<PlayerSearchComponent>();
		playerSearch->SetDetectionRadius(detectionRadius);

		auto chase = gameObject->AddComponent<EnemyChaseComponent>();
		chase->SetMoveSpeed(moveSpeed);
	}
	
	void Enemy::SetupStats(int healthPoints, int armor)
	{
		stats = gameObject->AddComponent<CharacterStatsComponent>();

		stats->SetHealthPoints(healthPoints);
		stats->SetArmor(armor);
	}

	void Enemy::SetupAttack(int damage, float attackRange, float attaclCooldown)
	{
		attack = gameObject->AddComponent<AttackComponent>();

		attack->SetDamage(damage);
		attack->SetAttackRange(attackRange);
		attack->SetAttackCooldown(attaclCooldown);
	}

	void Enemy::SetupEnemyAttack()
	{
		enemyAttack = gameObject->AddComponent<EnemyAttackComponent>();

		enemyAttack->SetPlayerSearch(playerSearch);
		enemyAttack->SetAttack(attack);
	}
}