#include "Wall.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "ResourceSystem.h"

namespace XYZRoguelike
{
	Wall::Wall(float x, float y, float width, float height)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Wall");

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		renderer->SetPixelSize(static_cast<int>(width), static_cast<int>(height));

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(x, y);

		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(true);
		
		gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
	}

	XYZEngine::GameObject* Wall::GetGameObject()
	{
		return gameObject;
	}
}