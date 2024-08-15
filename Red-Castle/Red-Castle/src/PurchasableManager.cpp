#include "PurchasableManager.h"
#include "RenderObject.h"
#include "GlobalFontStorage.h"
#include "Game.h"

PurchasableManager::PurchasableManager()
{
    m_priceText = std::make_shared<sf::Text>();
    m_priceText->setFont(*GlobalFontStorage::getInstance().getFont());
    m_priceText->setCharacterSize(24u);
    m_priceText->setString("");
    m_priceText->setPosition(sf::Vector2f(static_cast<float>(SCREEN_WIDTH) / 2.f, static_cast<float>(SCREEN_HEIGHT) / 2.f + 250.f));

    RenderObject::getInstance().addHUD(m_priceText);
}

void PurchasableManager::initNewWeapon(sf::Vector2f t_pos, std::shared_ptr<GunBasic> t_weapon)
{
    Purchasable newPurchasable;
    newPurchasable.initWeaponBuyable(t_pos, t_weapon);
    m_purchasables.push_back(newPurchasable);
}

void PurchasableManager::tryPurchase(Player& t_player)
{
    if (m_collidingWith < 0 || m_collidingWith > static_cast<int>(m_purchasables.size()) || m_purchaseCooldown > 0.f)
        return;
    
    if (t_player.tryRefillAmmo(m_purchasables.at(m_collidingWith).getWeapon()))
    {
        m_purchaseCooldown = 1.f;
        return;
    }

    if (t_player.tryPurchase(m_purchasables.at(m_collidingWith).getPrice()))
    {
        if(m_purchasables.at(m_collidingWith).getWeapon() != nullptr)
        {
            t_player.buyNewGun(m_purchasables.at(m_collidingWith).getWeapon());
            m_purchaseCooldown = 1.f;
            return;
        }
    }
    
}

void PurchasableManager::checkCollisions(sf::FloatRect t_playerBounds)
{
    for (unsigned int i = 0; i < m_purchasables.size(); ++i)
    {
        if (m_purchasables.at(i).getBounds().intersects(t_playerBounds))
        {
            m_collidingWith = i;
            m_priceText->setString("$" + std::to_string(m_purchasables.at(m_collidingWith).getPrice()) + " (Ammo: $" + std::to_string(m_purchasables.at(m_collidingWith).getPrice() / 2) + ")");
            m_priceText->setOrigin(sf::Vector2f(m_priceText->getGlobalBounds().width / 2.f, m_priceText->getGlobalBounds().height / 2.f));
            return;
        }
    }
    m_collidingWith = -1;
    m_priceText->setString("");
}

void PurchasableManager::update()
{
    if (m_purchaseCooldown > 0.f)
        m_purchaseCooldown -= Game::deltaTime;
}
