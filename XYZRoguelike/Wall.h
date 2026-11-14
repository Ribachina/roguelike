#pragma once

namespace XYZEngine
{
	class GameObject;
}

namespace XYZRoguelike
{
	
	// Класс для стен
	class Wall
	{
	public:
		Wall(float x, float y, float width, float height); // Создаём стену нужного размера в нужнйо позиции

		XYZEngine::GameObject* GetGameObject();

	private:
		XYZEngine::GameObject* gameObject = nullptr;
	};
}
