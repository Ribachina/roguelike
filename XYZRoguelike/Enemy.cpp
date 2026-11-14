#include "Enemy.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "PlayerSearchComponent.h"
#include "EnemyChaseComponent.h"

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
		auto playerSearch = gameObject->AddComponent<PlayerSearchComponent>();
		playerSearch->SetDetectionRadius(detectionRadius);

		auto chase = gameObject->AddComponent<EnemyChaseComponent>();
		chase->SetMoveSpeed(moveSpeed);
	}
}