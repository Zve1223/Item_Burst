#include "Item.hpp"


namespace bst
{
	Item::Item(float x, float y, itemType type, uint64_t health, float speed) : type(type), health(health)
	{
		base.setPosition(sf::Vector2f(x, y));
		base.setSize(sf::Vector2f(ITEM_SIZES[type], ITEM_SIZES[type]));
		base.setOrigin(sf::Vector2f(ITEM_SIZES[type] / 2.0f, ITEM_SIZES[type] / 2.0f));

		healthText.setCharacterSize(static_cast<uint16_t>(std::abs(ITEM_SIZES[0] / 2.0f)));

		velocity = sf::Vector2f(speed, 0.0f);
	}
}
