#pragma once

namespace XYZEngine
{
	class GameObject;
}

namespace XYZRoguelike
{
	
	// Класс для врагов. Создаём GameObject и делаем общую настройку через SetupAI (радиус обнаружения, скорость перемещения)
	class Enemy
	{
	public:
		virtual ~Enemy() = default;

		XYZEngine::GameObject* GetGameObject();

	protected:
		Enemy();

		void SetupAI(float detectionRadius, float moveSpeed);

		XYZEngine::GameObject* gameObject = nullptr;
	};
}
