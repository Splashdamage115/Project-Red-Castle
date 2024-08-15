#include "Purchasables.h"
#include "RenderObject.h"
#include "TextureLoader.h"

void Purchasable::initWeaponBuyable(sf::Vector2f t_pos, std::shared_ptr<GunBasic> t_weapon)
{
	m_weapon = t_weapon;

	m_price = t_weapon->price();

	m_body = std::make_shared<AnimatedSprite>(1.f, *TextureLoader::getInstance().getTexture(m_weapon->textureLocation()));
	m_weapon->getAnimation(m_body);
	m_body->setOrigin(sf::Vector2f(0.f, 0.f));
	m_body->setPosition(t_pos);
	RenderObject::getInstance().add(m_body);

	m_collisionSquare = std::make_shared<sf::RectangleShape>(sf::Vector2f(m_body->getGlobalBounds().width, m_body->getGlobalBounds().height) + sf::Vector2f(50.f, 50.f));
	m_collisionSquare->setPosition(t_pos - sf::Vector2f(25.f, 25.f));
	m_collisionSquare->setFillColor(sf::Color::Transparent);
	m_collisionSquare->setOutlineThickness(1.f);
	m_collisionSquare->setOutlineColor(sf::Color::White);
	RenderObject::getInstance().add(m_collisionSquare);
}

void Purchasable::update()
{
	m_body->update();
}
