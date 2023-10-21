#pragma once

#include "Resources.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


namespace bst
{
	class Item
	{
	public:
		Item(float, float, itemType, uint64_t, float);
		~Item();

		void move();
		void hit(uint64_t);
	private:
		sf::RectangleShape base;
		sf::Text healthText;
		itemType type;
		uint64_t health;
		sf::Vector2f velocity;
	};
}