#pragma once
#include "Component.h"

namespace XYZRoguelike
{
	class CharacterStatsComponent : public XYZEngine::Component
	{
	public:
		CharacterStatsComponent(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetHealthPoints(int healthPoints);
		int GetHealthPoints() const;

		void SetArmor(int armor); // На данном этапе броня это статический показатель. Если у персонажа 10 брони, а ему нанесут <=10 урона, то он не получит урона
		int GetArmor() const;

		void TakeDamage(int damage);
		bool IsDead() const;

	private:
		int healthPoints = 100;
		int armor = 0;
	};
}
