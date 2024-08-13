#ifndef PURCHASABLE_MANAGER_H
#define PURCHASABLE_MANAGER_H

#include "Purchasables.h"

class PurchasableManager
{
public:
	void initNewWeapon(sf::Vector2f t_pos, std::shared_ptr<GunBasic> t_weapon);
	std::shared_ptr<GunBasic> tryPurchase();
	void checkCollisions(sf::FloatRect t_playerBounds);
private:
	std::vector<Purchasable> m_purchasables;
	int m_collidingWith{ -1 };
};

#endif //!PURCHASABLE_MANAGER_H