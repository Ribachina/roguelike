#pragma once
#include "Component.h"

namespace XYZEngine
{
	class RigidbodyComponent;
}

namespace XYZRoguelike
{
	class PlayerSearchComponent;

	// Класс движения врага к игроку. Получаем игрока из PlayerSearchComponent
	class EnemyChaseComponent : public XYZEngine::Component
	{
	public:
		EnemyChaseComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetMoveSpeed(float speed); // Скорость движения врага

	private:
		XYZEngine::RigidbodyComponent* rigidbody = nullptr;
		PlayerSearchComponent* playerSearch = nullptr;

		float moveSpeed = 2.f;
	};
}
