#pragma once
#include "Component.h"
#include <SFML/Audio.hpp>

namespace XYZEngine
{
	// Класс для воспроизведения звуковых эффектов
	class AudioComponent : public Component
	{
	public:
		AudioComponent(GameObject* gameObject); // Создаём класс

		void Update(float deltaTime) override; // Обновляем
		void Render() override; // Ничего не рисует, но обязаны объявить

		void SetBuffer(const sf::SoundBuffer& buffer);
		void Play();
		void Stop();

		void SetLoop(bool loop);
		void SetVolume(float volume);

	private:
		sf::Sound sound;
	};
}