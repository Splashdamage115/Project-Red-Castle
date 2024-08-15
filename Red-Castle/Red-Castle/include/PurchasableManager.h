#ifndef PURCHASABLE_MANAGER_H
#define PURCHASABLE_MANAGER_H

#include "Purchasables.h"
#include "Player.h"

class PurchasableManager
{
public:
	PurchasableManager();
	void initNewWeapon(sf::Vector2f t_pos, std::shared_ptr<GunBasic> t_weapon);
	void tryPurchase(Player& t_player);
	void checkCollisions(sf::FloatRect t_playerBounds);
	void update();
private:
	std::vector<Purchasable> m_purchasables;
	std::shared_ptr<sf::Text> m_priceText;
	int m_collidingWith{ -1 };
	float m_purchaseCooldown{ 0.f }; // used to avoid hold down purchases
};

#endif //!PURCHASABLE_MANAGER_H