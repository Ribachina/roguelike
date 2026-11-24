#pragma once

namespace XYZEngine
{
	class GameObject;
}

namespace XYZRoguelike
{
	
	class CharacterStatsComponent;
	class AttackComponent;
	class EnemyAttackComponent;
	class PlayerSearchComponent;
	
	// Класс для врагов. Создаём GameObject и делаем общую настройку через SetupAI (радиус обнаружения, скорость перемещения)
	class Enemy
	{
	public:
		virtual ~Enemy() = default;

		XYZEngine::GameObject* GetGameObject();

	protected:
		Enemy();

		void SetupAI(float detectionRadius, float moveSpeed);
		void SetupStats(int healthPoints, int armor);
		void SetupAttack(int damage, float attackRange, float attackCooldown);

		XYZEngine::GameObject* gameObject = nullptr;
		CharacterStatsComponent* stats = nullptr;
		AttackComponent* attack = nullptr;
		EnemyAttackComponent* enemyAttack = nullptr;
		PlayerSearchComponent* playerSearch = nullptr;

		void SetupEnemyAttack();
	};
}
