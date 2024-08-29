#ifndef TILE_SET_MANAGER_H
#define TILE_SET_MANAGER_H

#include "Library.h"

enum class Direction
{
	North, East, South, West, None
};

struct door
{
	std::shared_ptr<sf::RectangleShape > m_doorSprite;
	sf::Vector2f m_openPos{ 0.f,0.f };
	sf::Vector2f m_closedPos{ 0.f,0.f };
};

class TileSetManager
{
public:
	void init();

	void update(); // used for animations
	sf::FloatRect getActiveBounds(sf::Vector2f t_playerPos); // get the rectangle the player is in (for spawning)
	std::vector<std::shared_ptr<sf::RectangleShape>>& getWalls(sf::Vector2f t_playerPos); // get the wall bounds for movement collisions

	bool closeDoors(sf::FloatRect t_playerBounds); // this takes the whole bounds so to confirm player has fully entered the room and is not on the door
	void openDoors(); // open the doors after all enemies are killed
private:
	void spawnBox(sf::Vector2f t_topLeftPosition); // initialise floor tiles
	void spawnWalls(sf::Vector2f t_topLeftPosition); // initialise walls and doors for the new area
	void closeDoorsAnimation();
	void openDoorsAnimation();

	std::vector<std::shared_ptr<sf::RectangleShape>> m_activeArea; // floor area
	std::vector<std::vector<std::shared_ptr<sf::RectangleShape>>> m_walls;
	std::vector<std::vector<door>> m_doors;
	std::vector<bool> m_enemyRoom;

	bool m_closed{ false }; // check if the doors are closed
	int m_activeAreaNum{ 0 }; // area the player is in (for door animations)
	float m_animationTimeRemaining{ 0.f };

	static constexpr float DOOR_CLOSE_TIME{ 0.5f };
};

#endif // !TILE_SET_MANAGER_H
