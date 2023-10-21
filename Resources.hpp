#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


namespace bst
{
	extern const enum TEXTURES
	{
		APPLE_TEX,
		BAKED_POTATO_TEX,
		CHORUS_FRUIT_TEX,
		DIAMOND_TEX,
		DRAGON_FIREBALL_TEX,
		EGG_TEX,
		EMERALD_TEX,
		ENDER_EYE_TEX,
		ENDER_PEARL_TEX,
		FIREWORK_STAR_TEX,
		FIREWORK_STAR_OVERLAY_TEX,
		FIRE_CHARGE_TEX,
		GOLDEN_APPLE_TEX,
		HEART_OF_THE_SEA_TEX,
		MAGMA_CREAM_TEX,
		NAUTILUS_SHELL_TEX,
		POPPED_CHORUS_FRUIT_TEX,
		PUFFERFISH_TEX,
		SLIME_BALL_TEX,
		SNOWBALL_TEX,
		TURTLE_EGG_TEX,
		TEX_COUNT
	};

	extern const enum itemType
	{
		BASE,
		DOUBLE,
		BONUS,
		TYPE_COUNT
	};

	extern const float ITEM_SIZES[TYPE_COUNT] = { 64.0f, 128.0f, 128.0f };

	extern sf::Image icon;

	extern const std::string fontName = "minecraft.ttf";
	extern sf::Font font;

	extern const std::vector<std::string> textureNames = {
			"apple.png", "baked_potato.png", "chorus_fruit.png", "diamond.png", "dragon_fireball.png", "egg.png", "emerald.png",
			"ender_eye.png", "ender_pearl.png", "firework_star.png", "firework_star_overlay.png", "fire_charge.png", "golden_apple.png", "heart_of_the_sea.png",
			"magma_cream.png", "nautilus_shell.png", "popped_chorus_fruit.png", "pufferfish.png", "slime_ball.png", "snowball.png", "turtle_egg.png"
	};
	extern std::vector<sf::Texture*> textures;
	extern sf::Texture* errorTexture;

	extern void loadPresets();
	extern void loadIcon();
	extern void loadFont();
	extern void loadTextures();
	extern void createErrorTexture();
}