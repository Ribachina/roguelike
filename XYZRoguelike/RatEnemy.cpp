#include "RatEnemy.h"
#include "GameObject.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "PlayerSearchComponent.h"
#include "EnemyChaseComponent.h"

namespace XYZRoguelike
{
	RatEnemy::RatEnemy()
		: Enemy()
	{
		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>(); // Визуал крысы
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		renderer->SetPixelSize(24, 24);

		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>(); // Тело для движения

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>(); // Коллайдер для столкновений

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>(); // Начальная позиция
		transform->MoveBy({ 200.f, 200.f });

		SetupAI(200.f, 100.f); // Радиус обнаружения и скорость
	}
}