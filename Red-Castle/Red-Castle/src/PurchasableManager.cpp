#include "PurchasableManager.h"

void PurchasableManager::initNewWeapon(sf::Vector2f t_pos, std::shared_ptr<GunBasic> t_weapon)
{
    Purchasable newPurchasable;
    newPurchasable.initWeaponBuyable(t_pos, t_weapon);
    m_purchasables.push_back(newPurchasable);
}

std::shared_ptr<GunBasic> PurchasableManager::tryPurchase()
{
    if (m_collidingWith < 0 || m_collidingWith > static_cast<int>(m_purchasables.size()))
        return nullptr;
    //if (MONEY_STORAGE_LOCATION >= m_purchasables.at(m_collidingWith).getPrice())
    {
        return  m_purchasables.at(m_collidingWith).getWeapon();
    }
    return nullptr;
}

void PurchasableManager::checkCollisions(sf::FloatRect t_playerBounds)
{
    for (unsigned int i = 0; i < m_purchasables.size(); ++i)
    {
        if (m_purchasables.at(i).getBounds().intersects(t_playerBounds))
        {
            m_collidingWith = i;
            return;
        }
    }
    m_collidingWith = -1;
}
