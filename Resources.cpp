#include "Resources.hpp"

namespace bst
{
	const enum TEXTURES;
	const enum itemType;

	const float ITEM_SIZES[TYPE_COUNT] = { 64.0f, 128.0f, 128.0f };

	sf::Image icon;

	const std::string fontName = "minecraft.ttf";
	sf::Font font;

	const std::vector<std::string> textureNames = {
			"apple.png", "baked_potato.png", "chorus_fruit.png", "diamond.png", "dragon_fireball.png", "egg.png", "emerald.png",
			"ender_eye.png", "ender_pearl.png", "firework_star.png", "firework_star_overlay.png", "fire_charge.png", "golden_apple.png", "heart_of_the_sea.png",
			"magma_cream.png", "nautilus_shell.png", "popped_chorus_fruit.png", "pufferfish.png", "slime_ball.png", "snowball.png", "turtle_egg.png"
	};
	std::vector<sf::Texture*> textures;
	sf::Texture* errorTexture;

	void loadPresets();
	void loadIcon();
	void loadFont();
	void loadTextures();
	void createErrorTexture();

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
				std::cout << '\t' << "Failed to load " << textureName << std::endl;
				textures.push_back(errorTexture);
				continue;
			}
			std::cout << '\t' << textureName << " was loaded successfully" << std::endl;
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