#ifndef TILE_SET_MANAGER_H
#define TILE_SET_MANAGER_H

#include "Library.h"

class TileSetManager
{
public:
	void init();

	sf::FloatRect getActiveBounds() { return m_activeArea->getGlobalBounds(); }
private:
	std::shared_ptr<sf::RectangleShape> m_activeArea;
};

#endif // !TILE_SET_MANAGER_H
