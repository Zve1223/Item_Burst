#include "Resources.hpp"

namespace bst
{
	void loadPresets()
	{
		loadIcon();
		loadFont();
		loadTextures();
	}

	void loadIcon()
	{
		std::cout << "Loading icon..." << std::endl;
		if (!icon.loadFromFile("./Icon/icon.png"))
		{
			std::cout << "Failed to load icon.png as Image" << std::endl;
			return;
		}
		std::cout << "icon.png was loaded successfully" << std::endl << std::endl;
	}

	void loadFont()
	{
		std::cout << "Loading font..." << std::endl;
		if (!font.loadFromFile("./Font/" + fontName))
		{
			std::cout << "Failed to load " + fontName << std::endl;
			return;
		}
		std::cout << fontName << " was loaded successfully" << std::endl << std::endl;
	}

	void loadTextures()
	{
		createErrorTexture();
		std::cout << "Loading textures..." << std::endl;
		for (auto textureName : textureNames)
		{
			sf::Texture* texture = new sf::Texture();
			if (!texture->loadFromFile("./Textures/" + textureName))
			{
				std::cout << "Failed to load " << textureName << std::endl;
				textures.push_back(errorTexture);
				continue;
			}
			std::cout << textureName << " was loaded successfully" << std::endl;
			textures.push_back(texture);
		}
		std::cout << "Done." << std::endl << std::endl;
	}

	void createErrorTexture()
	{
		sf::Image errorImage;
		errorImage.create(2, 2);
		errorImage.setPixel(0, 0, sf::Color::Black);
		errorImage.setPixel(1, 0, sf::Color::Magenta);
		errorImage.setPixel(0, 1, sf::Color::Magenta);
		errorImage.setPixel(1, 1, sf::Color::Black);
		errorTexture = new sf::Texture();
		errorTexture->loadFromImage(errorImage);
	}
}