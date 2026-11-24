#include "pch.h"
#include "ResourceSystem.h"
#include <iostream>
#include "Logger.h"
#include <stdexcept>

namespace XYZEngine
{
	ResourceSystem* ResourceSystem::Instance()
	{
		static ResourceSystem resourceSystem;
		return &resourceSystem;
	}

	void ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
	{
		if (textures.find(name) != textures.end())
		{
			LOG_WARNING("Texture already loaded: " + name);
			return;
		}

		sf::Texture* newTexture = new sf::Texture();
		if (!newTexture->loadFromFile(sourcePath))
		{
			delete newTexture;

			throw std::runtime_error("Failed to load texture: " + sourcePath);
		}
		
		newTexture->setSmooth(isSmooth);
		textures.emplace(name, newTexture);

		LOG_INFO("Texture loaded: " + name);
	}
	const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
	{
		return textures.find(name)->second;
	}
	sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
	{
		return new sf::Texture(*textures.find(name)->second);
	}
	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
		auto texturePair = textures.find(name);

		sf::Texture* deletingTexure = texturePair->second;
		textures.erase(texturePair);
		delete deletingTexure;
	}

	void ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
	{
		if (textureMaps.find(name) != textureMaps.end())
		{
			LOG_WARNING("Texture map already loaded: " + name); // Повторная загрузка
			
			return;
		}

		sf::Texture textureMap;
		if (!textureMap.loadFromFile(sourcePath))
		{
			throw std::runtime_error("Failed to load texure map: " + sourcePath); // Невозможно загрузить элемент или файл
		}
			
		std::vector<sf::Texture*> textureMapElements;
		auto textureSize = textureMap.getSize();
		int loadedElements = 0;

			for (int y = 0; y + elementPixelSize.y <= textureSize.y; y += elementPixelSize.y)
			{
				if (loadedElements == totalElements)
				{
					break;
				}

				for (int x = 0; x + elementPixelSize.x <= textureSize.x; x += elementPixelSize.x)
				{
					if (loadedElements == totalElements)
					{
						break;
					}

					sf::Texture* newTextureMapElement = new sf::Texture();
					if (!newTextureMapElement->loadFromFile(sourcePath, sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
					{
						delete newTextureMapElement;

						for (auto* element : textureMapElements)
						{
							delete element;
						}

						throw std::runtime_error("Failed to load texture map element: " + sourcePath);
					}
					
					newTextureMapElement->setSmooth(isSmooth);

					textureMapElements.push_back(newTextureMapElement);
					
					loadedElements++;
				}
			}

			if (loadedElements != totalElements)
			{
				for (auto* element : textureMapElements)
				{
					delete element;
				}

				throw std::runtime_error("Texture map don't contain enough elements: " + name);
			}

			textureMaps.emplace(name, std::move(textureMapElements));

			LOG_INFO("Texture map loaded: " + name + " (" + std::to_string(totalElements) + " elements)"); // Всё ок
	}
	const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures[elementIndex];
	}
	sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return new sf::Texture(*textures[elementIndex]);
	}
	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures.size();
	}
	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
		auto textureMap = textureMaps.find(name);
		auto deletingTextures = textureMap->second;

		for (int i = 0; i < deletingTextures.size(); i++)
		{
			delete deletingTextures[i];
		}

		textureMaps.erase(textureMap);
	}

	void ResourceSystem::LoadSoundBuffer(const std::string& name, std::string sourcePath)
	{
		if (soundBuffers.find(name) != soundBuffers.end())
		{
			LOG_WARNING("Sound already loaded: " + name);
			return;
		}

		sf::SoundBuffer* newSoundBuffer = new sf::SoundBuffer();
		if (!newSoundBuffer->loadFromFile(sourcePath))
		{
			delete newSoundBuffer;

			throw std::runtime_error("Failed to load sound: " + sourcePath);
		}
		
		soundBuffers.emplace(name, newSoundBuffer);

		LOG_INFO("Sound loaded: " + name);
	}
	const sf::SoundBuffer* ResourceSystem::GetSoundBufferShared(const std::string& name) const
	{
		auto soundBuffer = soundBuffers.find(name);

		if (soundBuffer == soundBuffers.end())
		{
			return nullptr;
		}
		
		return soundBuffer->second;
	}
	sf::SoundBuffer* ResourceSystem::GetSoundBufferCopy(const std::string& name) const
	{
		return new sf::SoundBuffer(*soundBuffers.find(name)->second);
	}
	void ResourceSystem::DeleteSharedSoundBuffer(const std::string& name)
	{
		auto soundBuffer = soundBuffers.find(name);

		if (soundBuffer == soundBuffers.end())
		{
			return;
		}

		sf::SoundBuffer* deletingSoundBuffer = soundBuffer->second;
		soundBuffers.erase(soundBuffer);
		delete deletingSoundBuffer;
	}

	void ResourceSystem::LoadMusic(const std::string& name, const std::string& sourcePath)
	{
		if (musics.find(name) != musics.end())
		{
			LOG_WARNING("Music already loaded: " + name);
			return;
		}

		sf::Music* newMusic = new sf::Music();
		if (!newMusic->openFromFile(sourcePath))
		{
			delete newMusic;

			throw std::runtime_error("Failed to load music: " + sourcePath);
		}
		
		musics.emplace(name, newMusic);

		LOG_INFO("Music loaded: " + name);
	}
	sf::Music* ResourceSystem::GetMusic(const std::string& name)
	{
		auto music = musics.find(name);

		if (music == musics.end())
		{
			return nullptr;
		}

		return music->second;
	}
	void ResourceSystem::DeleteMusic(const std::string& name)
	{
		auto music = musics.find(name);

		if (music == musics.end())
		{
			return;
		}

		sf::Music* deleteMusic = music->second;
		musics.erase(music);
		delete deleteMusic;
	}

	void ResourceSystem::Clear()
	{
		DeleteAllTextures();
		DeleteAllTextureMaps();
		DeleteAllSoundBuffers();
		DeleteAllMusic();
	}

	void ResourceSystem::DeleteAllTextures()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& texturePair : textures)
		{
			keysToDelete.push_back(texturePair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTexture(key);
		}
	}
	void ResourceSystem::DeleteAllTextureMaps()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& textureMapPair : textureMaps)
		{
			keysToDelete.push_back(textureMapPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}
	void ResourceSystem::DeleteAllSoundBuffers()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& soundBuffer : soundBuffers)
		{
			keysToDelete.push_back(soundBuffer.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedSoundBuffer(key);
		}
	}
	void ResourceSystem::DeleteAllMusic()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& music : musics)
		{
			keysToDelete.push_back(music.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteMusic(key);
		}
	}
}