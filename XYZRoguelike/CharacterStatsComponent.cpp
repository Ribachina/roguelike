#include "CharacterStatsComponent.h"
#include "Logger.h"
#include <algorithm>

namespace XYZRoguelike
{
	CharacterStatsComponent::CharacterStatsComponent(XYZEngine::GameObject* gameobject)
		: Component(gameobject)
	{

	}

	void CharacterStatsComponent::Update(float deltaTime)
	{

	}

	void CharacterStatsComponent::Render()
	{

	}

	void CharacterStatsComponent::SetHealthPoints(int newHealthPoints)
	{
		healthPoints = std::max(0, newHealthPoints);
	}

	int CharacterStatsComponent::GetHealthPoints() const
	{
		return healthPoints;
	}

	void CharacterStatsComponent::SetArmor(int newArmor)
	{
		armor = std::max (0, newArmor);
	}

	int CharacterStatsComponent::GetArmor() const
	{
		return armor;
	}

	void CharacterStatsComponent::TakeDamage(int damage)
	{
		const int receivedDamage = std::max(0, damage - armor);
		healthPoints -= receivedDamage;
		if (healthPoints < 0)
		{
			healthPoints = 0;
		}

		LOG_INFO("Damage received: " + std::to_string(receivedDamage) + " HP: " + std::to_string(healthPoints));
	}

	bool CharacterStatsComponent::IsDead() const
	{
		return healthPoints <= 0;
	}




}
