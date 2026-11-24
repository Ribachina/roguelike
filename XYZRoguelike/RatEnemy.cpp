#include "RatEnemy.h"
#include "GameObject.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "PlayerSearchComponent.h"
#include "EnemyChaseComponent.h"
#include "CharacterStatsComponent.h"

namespace XYZRoguelike
{
	RatEnemy::RatEnemy()
		: Enemy()
	{
		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>(); // Визуал крысы
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("rat"));
		renderer->SetPixelSize(32, 32);

		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>(); // Тело для движения

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>(); // Коллайдер для столкновений

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>(); // Начальная позиция
		transform->MoveBy({ 200.f, 200.f });

		SetupAI(200.f, 100.f); // Радиус обнаружения и скорость
		SetupStats(50, 5); // Здоровье и броня
		SetupAttack(20, 40.f, 1.f); // Урон, радиуас атаки, перезарядка атаки
		SetupEnemyAttack();
	}
}