#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include "Library.h"

class TextureLoader
{
public:
	static TextureLoader& getInstance()
	{
		static TextureLoader instance;
		return instance;
	}

	// DELETE FUNCTIONS TO AVOID MORE INSTANCES
	TextureLoader(TextureLoader const&) = delete;
	void operator=(TextureLoader const&) = delete;

	std::shared_ptr<sf::Texture> getTexture(std::string t_address)
	{
		for (unsigned int i = 0; i < m_textureName.size(); i++)
		{
			if (m_textureName.at(i) == t_address)
			{
				return m_texture.at(i);
			}
		}

		std::shared_ptr<sf::Texture> newTexture;
		newTexture = std::make_shared<sf::Texture>();
		newTexture->loadFromFile(t_address);
		m_texture.push_back(newTexture);
		m_textureName.push_back(t_address);
		return newTexture;
	}
private:
	TextureLoader() {}

	std::vector<std::shared_ptr<sf::Texture>> m_texture;
	std::vector<std::string> m_textureName;
};

#endif // !TEXTURE_LOADER_HPP
