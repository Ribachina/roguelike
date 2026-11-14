#include "pch.h"
#include "AudioComponent.h"

namespace XYZEngine
{
	AudioComponent::AudioComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void AudioComponent::Update(float deltaTime)
	{
	}

	void AudioComponent::Render()
	{
	}

	void AudioComponent::SetBuffer(const sf::SoundBuffer& buffer)
	{
		sound.setBuffer(buffer);
	}

	void AudioComponent::Play()
	{
		sound.play();
	}

	void AudioComponent::Stop()
	{
		sound.stop();
	}

	void AudioComponent::SetLoop(bool loop)
	{
		sound.setLoop(loop);
	}

	void AudioComponent::SetVolume(float volume)
	{
		sound.setVolume(volume);
	}
}