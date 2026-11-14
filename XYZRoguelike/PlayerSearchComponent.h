#pragma once
#include "Component.h"

namespace XYZEngine
{
	class GameObject;
	class TransformComponent;
}

namespace XYZRoguelike
{
	// Класс поиска игрока. Проверяет расстояние между владельцем и игроком, если игрок внутри detectionRadius, то сохраняет игрока как цель
	class PlayerSearchComponent : public XYZEngine::Component
	{
	public:
		PlayerSearchComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		XYZEngine::GameObject* GetTarget() const; // Возвращает найденного игрока

		void SetDetectionRadius(float radius); // Установка радиуса обнаружения игрока

	private:
		XYZEngine::TransformComponent* transform = nullptr; // Получение позиции врага
		XYZEngine::GameObject* target = nullptr; // Получение позиции игрока

		float detectionRadius = 2.f;
	};
}
