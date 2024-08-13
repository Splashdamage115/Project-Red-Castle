#ifndef PURCHASABLES_H
#define PURCHASABLES_H

#include "Library.h"
#include "AnimatedSprite.h"
#include "Weapons.h"

enum class purchasableType
{
	Weapon
};

class Purchasable
{
public:
	void initWeaponBuyable(sf::Vector2f t_pos, std::shared_ptr<GunBasic> t_weapon);

	void update();
	int getPrice() { return m_price; }
	std::shared_ptr<GunBasic> getWeapon() { return m_weapon; }
	sf::FloatRect getBounds() { return m_body->getGlobalBounds(); }
private:
	std::shared_ptr<GunBasic> m_weapon;
	std::shared_ptr<sf::RectangleShape> m_collisionSquare;
	std::shared_ptr<AnimatedSprite> m_body;
	int m_price{ 0 };
};
#endif // !PURCHASABLES_H