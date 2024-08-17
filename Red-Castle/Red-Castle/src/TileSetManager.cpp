#include "TileSetManager.h"
#include "RenderObject.h"

void TileSetManager::init()
{
	m_activeArea = std::make_shared<sf::RectangleShape>(sf::Vector2f(2000.f, 2000.f));
	m_activeArea->setPosition(sf::Vector2f(-1000.f, -50.f));
	m_activeArea->setFillColor(sf::Color(41, 87, 100));
	RenderObject::getInstance().addBG(m_activeArea);
}
