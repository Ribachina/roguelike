#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include "AudioComponent.h"
#include "PlayerControllerComponent.h"
#include "CharacterStatsComponent.h"
#include "AttackComponent.h"

namespace XYZRoguelike
{
	Player::Player()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("knight"));
		playerRenderer->SetPixelSize(32, 32);

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto playerAudio = gameObject->AddComponent<XYZEngine::AudioComponent>();

		auto stats = gameObject->AddComponent<CharacterStatsComponent>();
		stats->SetHealthPoints(100);
		stats->SetArmor(20);

		auto playerAttack = gameObject->AddComponent<AttackComponent>();
		playerAttack->SetDamage(20);
		playerAttack->SetAttackRange(40.f);
		playerAttack->SetAttackCooldown(0.5f);

		auto playerController = gameObject->AddComponent<PlayerControllerComponent>();
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}