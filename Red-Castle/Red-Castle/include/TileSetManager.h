#ifndef TILE_SET_MANAGER_H
#define TILE_SET_MANAGER_H

#include "Library.h"
#include "PurchasableManager.h"

enum class Direction
{
	North, East, South, West, None
};

enum class RoomType
{
	Enemy, Spawn, Shop, Exit
};

struct door
{
	std::shared_ptr<sf::RectangleShape> m_doorSprite;
	sf::Vector2f m_openPos{ 0.f,0.f };
	sf::Vector2f m_closedPos{ 0.f,0.f };
};

struct Tile
{
	RoomType m_roomType;
	std::shared_ptr<sf::RectangleShape > m_activeArea; // floor area
	std::vector<std::shared_ptr<sf::RectangleShape>> m_walls;
	std::vector<door> m_doors;
	bool m_closeDoors;
};

class TileSetManager
{
public:
	void init(std::shared_ptr<PurchasableManager> t_purchasables);

	void update(); // used for animations
	sf::FloatRect getActiveBounds(sf::Vector2f t_playerPos); // get the rectangle the player is in (for spawning)
	std::vector<std::shared_ptr<sf::RectangleShape>>& getWalls(sf::Vector2f t_playerPos); // get the wall bounds for movement collisions

	bool checkSpawnEnemiesRoom();
	void closeDoors(sf::FloatRect t_playerBounds); // this takes the whole bounds so to confirm player has fully entered the room and is not on the door
	void openDoors(); // open the doors after all enemies are killed
	sf::Vector2f getSpawnRoomCoords();
private:
	void spawnBox(sf::Vector2f t_topLeftPosition); // initialise floor tiles
	void spawnWalls(sf::Vector2f t_topLeftPosition, std::vector<Direction> t_directions); // initialise walls and doors for the new area
	void initialiseRoomClutter(RoomType t_roomType, sf::Vector2f t_topLeftPos, std::shared_ptr<PurchasableManager> t_purchasables);
	void closeDoorsAnimation();
	void openDoorsAnimation();

	void spawnBridgeWalls(Direction t_spawnDirection, sf::Vector2f t_wallPosition);

	std::vector<Tile> m_tiles;
	std::vector<std::shared_ptr<sf::RectangleShape>> m_bridgeWalls;

	bool m_closed{ false }; // check if the doors are closed
	int m_activeAreaNum{ 0 }; // area the player is in (for door animations)
	float m_animationTimeRemaining{ 0.f };

	static constexpr float DOOR_CLOSE_TIME{ 0.5f };
	static constexpr float TILE_SIZE{ 1024.f };
	static constexpr float HALLWAY_LENGTH{ 300.f };
	static constexpr float WALL_THICKNESS{ 64.f };
	static constexpr float DOOR_SIZE{ 250.f };

};

#endif // !TILE_SET_MANAGER_H
