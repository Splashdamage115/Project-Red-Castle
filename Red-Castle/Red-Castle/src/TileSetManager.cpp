#include "TileSetManager.h"
#include "RenderObject.h"
#include "Game.h"
#include "simpleMaths.h"

void TileSetManager::init(std::shared_ptr<PurchasableManager> t_purchasables)
{
	m_tiles.clear();
	m_bridgeWalls.clear();

	int X_SIZE = 3;
	int Y_SIZE = 3;

	int spawnRoom = rand() % (X_SIZE * Y_SIZE);
	int shopRoom  = rand() % (X_SIZE * Y_SIZE);
	int exitRoom  = rand() % (X_SIZE * Y_SIZE);

	while (shopRoom == spawnRoom)
		shopRoom = rand() % (X_SIZE * Y_SIZE);

	while(shopRoom == exitRoom || exitRoom == spawnRoom)
		exitRoom = rand() % (X_SIZE * Y_SIZE);

	DEBUG_MSG("Exit: " + std::to_string(exitRoom));
	DEBUG_MSG("Shop: " + std::to_string(shopRoom));
	DEBUG_MSG("Spawn: " + std::to_string(spawnRoom));


	for (int x = 0; x < X_SIZE; x++)
	{
		for (int y = 0; y < Y_SIZE; y++)
		{
			std::vector<Direction> doorDirections;
			if (y - 1 >= 0)
			{
				// check if that tile is active here!
				doorDirections.push_back(Direction::North);
			}
			if (y + 1 < Y_SIZE)
			{
				// check if that tile is active here!
				doorDirections.push_back(Direction::South);
			}
			if (x - 1 >= 0)
			{
				// check if that tile is active here!
				doorDirections.push_back(Direction::West);
			}
			if (x + 1 < X_SIZE)
			{
				// check if that tile is active here!
				doorDirections.push_back(Direction::East);
			}
			spawnBox(sf::Vector2f(x * (TILE_SIZE + HALLWAY_LENGTH), y * (TILE_SIZE + HALLWAY_LENGTH)));
			spawnWalls(sf::Vector2f(x * (TILE_SIZE + HALLWAY_LENGTH), y * (TILE_SIZE + HALLWAY_LENGTH)), doorDirections);

			int roomIndex = x + y * X_SIZE;

			if (roomIndex == spawnRoom)
			{
				initialiseRoomClutter(RoomType::Spawn, sf::Vector2f(x * (TILE_SIZE + HALLWAY_LENGTH), y * (TILE_SIZE + HALLWAY_LENGTH)), t_purchasables);
			}
			else if (roomIndex == shopRoom)
			{
				initialiseRoomClutter(RoomType::Shop, sf::Vector2f(x * (TILE_SIZE + HALLWAY_LENGTH), y * (TILE_SIZE + HALLWAY_LENGTH)), t_purchasables);
			}
			else if (roomIndex == exitRoom)
			{
				initialiseRoomClutter(RoomType::Exit, sf::Vector2f(x * (TILE_SIZE + HALLWAY_LENGTH), y * (TILE_SIZE + HALLWAY_LENGTH)), t_purchasables);
			}
			else
			{
				initialiseRoomClutter(RoomType::Enemy, sf::Vector2f(x * (TILE_SIZE + HALLWAY_LENGTH), y * (TILE_SIZE + HALLWAY_LENGTH)), t_purchasables);
			}
		}
	}

	//spawnBox(sf::Vector2f(0.f, -2800.f));
	//spawnWalls(sf::Vector2f(0.f, -2800.f));
}

void TileSetManager::update()
{
	if (m_animationTimeRemaining > 0.f)
	{
		m_animationTimeRemaining -= Game::deltaTime;
		if (!m_closed)
			closeDoorsAnimation();
		else
			openDoorsAnimation();
	}
}

sf::FloatRect TileSetManager::getActiveBounds(sf::Vector2f t_playerPos)
{
	for (unsigned int i = 0; i < m_tiles.size(); i++)
	{
		if (m_tiles.at(i).m_activeArea->getGlobalBounds().contains(t_playerPos))
		{
			return m_tiles.at(i).m_activeArea->getGlobalBounds();
		}
	}
	DEBUG_MSG("ACTIVE AREA NOT CORRECT! RESET!");
	return m_tiles.at(0).m_activeArea->getGlobalBounds(); // this should never be called for spawning
}

std::vector<std::shared_ptr<sf::RectangleShape>>& TileSetManager::getWalls(sf::Vector2f t_playerPos)
{
	for (unsigned int i = 0; i < m_tiles.size(); i++)
	{
		if (m_tiles.at(i).m_activeArea->getGlobalBounds().contains(t_playerPos))
		{
			return m_tiles.at(i).m_walls;
		}
	}
	return m_bridgeWalls; // make this return bridge walls!
}

bool TileSetManager::checkSpawnEnemiesRoom()
{
	if (m_closed && m_tiles.at(m_activeAreaNum).m_closeDoors)
	{
		m_tiles.at(m_activeAreaNum).m_closeDoors = false;
		return true;
	}
	return false;
}

void TileSetManager::closeDoors(sf::FloatRect t_playerBounds)
{
	if (m_animationTimeRemaining > 0.f || m_closed)
		return;

	for (unsigned int i = 0; i < m_tiles.size(); i++)
	{
		if (m_tiles.at(i).m_activeArea->getGlobalBounds().contains(t_playerBounds.getPosition())) // check if the player is in an area
		{
			if (m_tiles.at(i).m_activeArea->getGlobalBounds().contains(t_playerBounds.getPosition() + t_playerBounds.getSize())) // check if fully contained in that area
			{
				m_activeAreaNum = i;
				if(m_tiles.at(m_activeAreaNum).m_closeDoors)
				{
					m_animationTimeRemaining = DOOR_CLOSE_TIME;
				}
			}
		}
	}
}

void TileSetManager::openDoors()
{
	m_animationTimeRemaining = DOOR_CLOSE_TIME;
}

sf::Vector2f TileSetManager::getSpawnRoomCoords()
{
	for (unsigned int i = 0; i < m_tiles.size(); i++)
	{
		if (m_tiles.at(i).m_roomType == RoomType::Spawn)
		{
			return m_tiles.at(i).m_activeArea->getPosition() + sf::Vector2f(TILE_SIZE / 2.f, TILE_SIZE / 2.f);
		}
	}
	DEBUG_MSG("SPAWN ROOM UNINITIALISED");
	return sf::Vector2f(0.f, 0.f);
}

void TileSetManager::spawnBox(sf::Vector2f t_topLeftPosition)
{
	m_tiles.emplace_back();
	std::shared_ptr<sf::RectangleShape> newArea;
	newArea = std::make_shared<sf::RectangleShape>(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	newArea->setPosition(sf::Vector2f(-TILE_SIZE / 2.f, -TILE_SIZE / 2.f) + t_topLeftPosition);
	newArea->setFillColor(sf::Color(41, 87, 100));
	RenderObject::getInstance().addFloor(newArea);

	m_tiles.back().m_activeArea = newArea;

	// INITIALISE FLOOR
	m_tiles.back().m_floor = std::make_shared<FloorTile>();
	std::vector<int> level;
	for (int i = 0; i < static_cast<int>(TILE_SIZE / 4.f); i++)
	{
		level.push_back(rand() % 2 + 2);
	}
	m_tiles.back().m_floor->load(sf::Vector2u(64.f,64.f), level, static_cast<unsigned int>(TILE_SIZE / 64.f), static_cast<unsigned int>(TILE_SIZE / 64.f));
	m_tiles.back().m_floor->setPosition(sf::Vector2f(-TILE_SIZE / 2.f, -TILE_SIZE / 2.f) + t_topLeftPosition);
	RenderObject::getInstance().addFloor(m_tiles.back().m_floor);
}

void TileSetManager::spawnWalls(sf::Vector2f t_topLeftPosition, std::vector<Direction> t_directions)
{
	std::vector<std::shared_ptr<sf::RectangleShape>> wallHolder;

	std::vector<bool> doorDirections; // used for temporary assigning, future will change directions
	//doorDirections.push_back(Direction::North);

	for (int i = 0; i < 4; i++)
	{
		doorDirections.push_back(false);
		for (unsigned int dir = 0; dir < t_directions.size(); dir++)
		{
			if (t_directions.at(dir) == static_cast<Direction>(i))
			{
				doorDirections.at(i) = true;
				break;
			}
		}
	}

	std::shared_ptr<sf::RectangleShape> newDoorCollision;
	door newDoor;
	std::vector<door> holdVector;

	for (unsigned int i = 0; i < doorDirections.size(); i++)
	{
		switch (static_cast<Direction>(i))
		{
		case Direction::North:
			newDoorCollision = std::make_shared<sf::RectangleShape>(sf::Vector2f(DOOR_SIZE + 10.f, WALL_THICKNESS));
			newDoorCollision->setPosition(sf::Vector2f(-DOOR_SIZE / 2.f, -TILE_SIZE / 2.f - WALL_THICKNESS) + t_topLeftPosition);
			RenderObject::getInstance().addBridgeWalls(newDoorCollision);
			wallHolder.push_back(newDoorCollision);
			if(doorDirections.at(i))
			{
				newDoor.m_doorSprite = newDoorCollision;
				newDoorCollision->setFillColor(sf::Color(219, 155, 7));
				newDoor.m_closedPos = newDoorCollision->getPosition();
				newDoor.m_openPos = newDoorCollision->getPosition() + sf::Vector2f(-DOOR_SIZE, 0.f);
				holdVector.push_back(newDoor);
				spawnBridgeWalls(Direction::North, t_topLeftPosition);
			}
			else
			{
				newDoorCollision->setFillColor(sf::Color(43, 148, 41));
			}
			break;
		case Direction::East:
			newDoorCollision = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, DOOR_SIZE + 10.f));
			newDoorCollision->setPosition(sf::Vector2f(TILE_SIZE / 2.f, -DOOR_SIZE / 2.f) + t_topLeftPosition);
			RenderObject::getInstance().addBridgeWalls(newDoorCollision);
			wallHolder.push_back(newDoorCollision);
			if (doorDirections.at(i))
			{
				newDoor.m_doorSprite = newDoorCollision;
				newDoorCollision->setFillColor(sf::Color(219, 155, 7));
				newDoor.m_closedPos = newDoorCollision->getPosition();
				newDoor.m_openPos = newDoorCollision->getPosition() + sf::Vector2f(0.f, -DOOR_SIZE);
				holdVector.push_back(newDoor);
				spawnBridgeWalls(Direction::East, t_topLeftPosition);
			}
			else
			{
				newDoorCollision->setFillColor(sf::Color(43, 148, 41));
			}
			break;
		case Direction::South:
			newDoorCollision = std::make_shared<sf::RectangleShape>(sf::Vector2f(DOOR_SIZE + 10.f, WALL_THICKNESS));
			newDoorCollision->setPosition(sf::Vector2f(-DOOR_SIZE / 2.f, TILE_SIZE / 2.f) + t_topLeftPosition);
			RenderObject::getInstance().addBridgeWalls(newDoorCollision);
			wallHolder.push_back(newDoorCollision);
			if (doorDirections.at(i))
			{
				newDoor.m_doorSprite = newDoorCollision;
				newDoorCollision->setFillColor(sf::Color(219, 155, 7));
				newDoor.m_closedPos = newDoorCollision->getPosition();
				newDoor.m_openPos = newDoorCollision->getPosition() + sf::Vector2f(-DOOR_SIZE, 0.f);
				holdVector.push_back(newDoor);
				spawnBridgeWalls(Direction::South, t_topLeftPosition);
			}
			else
			{
				newDoorCollision->setFillColor(sf::Color(43, 148, 41));
			}
			break;
		case Direction::West:
			newDoorCollision = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, DOOR_SIZE + 10.f));
			newDoorCollision->setPosition(sf::Vector2f(-TILE_SIZE / 2.f - WALL_THICKNESS, -DOOR_SIZE / 2.f) + t_topLeftPosition);
			RenderObject::getInstance().addWalls(newDoorCollision);
			wallHolder.push_back(newDoorCollision);
			if (doorDirections.at(i))
			{
				newDoor.m_doorSprite = newDoorCollision;
				newDoorCollision->setFillColor(sf::Color(219, 155, 7));
				newDoor.m_closedPos = newDoorCollision->getPosition();
				newDoor.m_openPos = newDoorCollision->getPosition() + sf::Vector2f(0.f, -DOOR_SIZE);
				holdVector.push_back(newDoor);
				spawnBridgeWalls(Direction::West, t_topLeftPosition);
			}
			else
			{
				newDoorCollision->setFillColor(sf::Color(43, 148, 41));
			}
			break;
		}
	}

	for (unsigned int i = 0; i < holdVector.size(); i++)
	{
		holdVector.at(i).m_doorSprite->setPosition(holdVector.at(i).m_openPos);
	}
	m_tiles.back().m_doors = holdVector;
	
	// TOP WALLS
	std::shared_ptr<sf::RectangleShape> newWall;
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f((TILE_SIZE - DOOR_SIZE) / 2.f + WALL_THICKNESS, WALL_THICKNESS));
	newWall->setPosition(sf::Vector2f(-TILE_SIZE / 2.f - WALL_THICKNESS, -TILE_SIZE / 2.f - WALL_THICKNESS) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addWalls(newWall);
	wallHolder.push_back(newWall);
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f((TILE_SIZE - DOOR_SIZE) / 2.f + WALL_THICKNESS, WALL_THICKNESS));
	newWall->setPosition(sf::Vector2f(DOOR_SIZE / 2.f, -TILE_SIZE / 2.f - WALL_THICKNESS) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addWalls(newWall);
	wallHolder.push_back(newWall);


	// LEFT WALLS
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, (TILE_SIZE - DOOR_SIZE) / 2.f + WALL_THICKNESS));
	newWall->setPosition(sf::Vector2f(-TILE_SIZE / 2.f - WALL_THICKNESS, -TILE_SIZE / 2.f - WALL_THICKNESS) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addWalls(newWall);
	wallHolder.push_back(newWall);
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, (TILE_SIZE - DOOR_SIZE) / 2.f + WALL_THICKNESS));
	newWall->setPosition(sf::Vector2f(-TILE_SIZE / 2.f - WALL_THICKNESS, DOOR_SIZE / 2.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addWalls(newWall);
	wallHolder.push_back(newWall);


	// RIGHT WALLS
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, (TILE_SIZE - DOOR_SIZE) / 2.f + WALL_THICKNESS));
	newWall->setPosition(sf::Vector2f(TILE_SIZE / 2.f, -TILE_SIZE / 2.f - WALL_THICKNESS) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addWalls(newWall);
	wallHolder.push_back(newWall);
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, (TILE_SIZE - DOOR_SIZE) / 2.f + WALL_THICKNESS));
	newWall->setPosition(sf::Vector2f(TILE_SIZE / 2.f, DOOR_SIZE / 2.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addWalls(newWall);
	wallHolder.push_back(newWall);

	// BOTTOM WALLS
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f((TILE_SIZE - DOOR_SIZE) / 2.f + WALL_THICKNESS, WALL_THICKNESS));
	newWall->setPosition(sf::Vector2f(-TILE_SIZE / 2.f - WALL_THICKNESS, TILE_SIZE / 2.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addWalls(newWall);
	wallHolder.push_back(newWall);
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f((TILE_SIZE - DOOR_SIZE) / 2.f + WALL_THICKNESS, WALL_THICKNESS));
	newWall->setPosition(sf::Vector2f(DOOR_SIZE / 2.f, TILE_SIZE / 2.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addWalls(newWall);
	wallHolder.push_back(newWall);

	
	wallHolder.push_back(newWall);
	m_tiles.back().m_walls = wallHolder;
}

void TileSetManager::initialiseRoomClutter(RoomType t_roomType, sf::Vector2f t_topLeftPos, std::shared_ptr<PurchasableManager> t_purchasables)
{
	m_tiles.back().m_roomType = t_roomType;

	switch (t_roomType)
	{
	case RoomType::Enemy:
		m_tiles.back().m_closeDoors = true;
		break;
	case RoomType::Spawn:
		m_tiles.back().m_closeDoors = false;
		break;
	case RoomType::Shop:
		m_tiles.back().m_closeDoors = false;
		t_purchasables->initNewWeapon(sf::Vector2f(-400.f, -400.f) + t_topLeftPos, std::make_shared<BasicSMG>());
		t_purchasables->initNewWeapon(sf::Vector2f(400.f, -400.f) + t_topLeftPos, std::make_shared<BasicPistol>());
		t_purchasables->initNewWeapon(sf::Vector2f(-400.f, 400.f) + t_topLeftPos, std::make_shared<BasicShotgun>());
		t_purchasables->initNewWeapon(sf::Vector2f(0.f, 0.f) + t_topLeftPos, std::make_shared<BasicLMG>());
		t_purchasables->initNewWeapon(sf::Vector2f(400.f, 400.f) + t_topLeftPos,  std::make_shared<BasicAssault>());
		break;
	case RoomType::Exit:
		m_tiles.back().m_closeDoors = false;
		break;
	default:
		break;
	}
}

void TileSetManager::closeDoorsAnimation()
{
	for (unsigned int i = 0; i < m_tiles.at(m_activeAreaNum).m_doors.size(); i++)
	{
		if(math::distance(m_tiles.at(m_activeAreaNum).m_doors.at(i).m_doorSprite->getPosition(), m_tiles.at(m_activeAreaNum).m_doors.at(i).m_closedPos) > 5.f)
			m_tiles.at(m_activeAreaNum).m_doors.at(i).m_doorSprite->move(math::displacement(m_tiles.at(m_activeAreaNum).m_doors.at(i).m_doorSprite->getPosition(), m_tiles.at(m_activeAreaNum).m_doors.at(i).m_closedPos) * 800.f * Game::deltaTime);
	}
	if (m_animationTimeRemaining <= 0.f)
	{
		m_closed = true;
	}
}

void TileSetManager::openDoorsAnimation()
{
	for (unsigned int i = 0; i < m_tiles.at(m_activeAreaNum).m_doors.size(); i++)
	{
		if (math::distance(m_tiles.at(m_activeAreaNum).m_doors.at(i).m_doorSprite->getPosition(), m_tiles.at(m_activeAreaNum).m_doors.at(i).m_openPos) > 5.f)
			m_tiles.at(m_activeAreaNum).m_doors.at(i).m_doorSprite->move(math::displacement(m_tiles.at(m_activeAreaNum).m_doors.at(i).m_doorSprite->getPosition(), m_tiles.at(m_activeAreaNum).m_doors.at(i).m_openPos) * 800.f * Game::deltaTime);
	}
	if (m_animationTimeRemaining <= 0.f)
	{
		m_closed = false;
	}
}

void TileSetManager::spawnBridgeWalls(Direction t_spawnDirection, sf::Vector2f t_wallPosition)
{
	std::shared_ptr<sf::RectangleShape> newWall;

	std::shared_ptr<FloorTile> newTile;
	newTile = std::make_shared<FloorTile>();

	
	int number = 0;
	

	switch (t_spawnDirection)
	{
	case Direction::North:
		newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, HALLWAY_LENGTH));
		newWall->setPosition(sf::Vector2f(-DOOR_SIZE / 2.f - WALL_THICKNESS, -TILE_SIZE / 2.f - HALLWAY_LENGTH) + t_wallPosition);

		newTile->setPosition(sf::Vector2f(-DOOR_SIZE / 2.f - WALL_THICKNESS, -TILE_SIZE / 2.f - HALLWAY_LENGTH) + t_wallPosition);
		RenderObject::getInstance().addFloor(newTile);
		m_bridgeAssets.push_back(newTile);

		newWall->setFillColor(sf::Color(145, 26, 196));
		RenderObject::getInstance().addBridgeWalls(newWall);
		m_bridgeWalls.push_back(newWall);
		newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, HALLWAY_LENGTH));
		newWall->setPosition(sf::Vector2f(DOOR_SIZE / 2.f, -TILE_SIZE / 2.f - HALLWAY_LENGTH) + t_wallPosition);
		newWall->setFillColor(sf::Color(145, 26, 196));
		RenderObject::getInstance().addBridgeWalls(newWall);
		m_bridgeWalls.push_back(newWall);
		break;
	case Direction::East:
		newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(HALLWAY_LENGTH, WALL_THICKNESS));
		newWall->setPosition(sf::Vector2f(TILE_SIZE / 2.f, -DOOR_SIZE / 2.f - WALL_THICKNESS) + t_wallPosition);

		newTile->setPosition(sf::Vector2f(TILE_SIZE / 2.f, -DOOR_SIZE / 2.f - WALL_THICKNESS) + t_wallPosition);
		RenderObject::getInstance().addFloor(newTile);
		m_bridgeAssets.push_back(newTile);
		number = 1;

		newWall->setFillColor(sf::Color(145, 26, 196));
		RenderObject::getInstance().addBridgeWalls(newWall);
		m_bridgeWalls.push_back(newWall);
		newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(HALLWAY_LENGTH, WALL_THICKNESS));
		newWall->setPosition(sf::Vector2f(TILE_SIZE / 2.f, DOOR_SIZE / 2.f) + t_wallPosition);
		newWall->setFillColor(sf::Color(145, 26, 196));
		RenderObject::getInstance().addBridgeWalls(newWall);
		m_bridgeWalls.push_back(newWall);
		break;
	case Direction::South:
		newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, HALLWAY_LENGTH));
		newWall->setPosition(sf::Vector2f(-DOOR_SIZE / 2.f - WALL_THICKNESS, TILE_SIZE / 2.f) + t_wallPosition);
		newWall->setFillColor(sf::Color(145, 26, 196));
		RenderObject::getInstance().addBridgeWalls(newWall);
		m_bridgeWalls.push_back(newWall);
		newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(WALL_THICKNESS, HALLWAY_LENGTH));
		newWall->setPosition(sf::Vector2f(DOOR_SIZE / 2.f, TILE_SIZE / 2.f) + t_wallPosition);
		newWall->setFillColor(sf::Color(145, 26, 196));
		RenderObject::getInstance().addBridgeWalls(newWall);
		m_bridgeWalls.push_back(newWall);
		break;
	case Direction::West:
		newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(HALLWAY_LENGTH, WALL_THICKNESS));
		newWall->setPosition(sf::Vector2f(-TILE_SIZE / 2.f - HALLWAY_LENGTH, -DOOR_SIZE / 2.f - WALL_THICKNESS) + t_wallPosition);
		newWall->setFillColor(sf::Color(145, 26, 196));
		RenderObject::getInstance().addBridgeWalls(newWall);
		m_bridgeWalls.push_back(newWall);
		newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(HALLWAY_LENGTH, WALL_THICKNESS));
		newWall->setPosition(sf::Vector2f(-TILE_SIZE / 2.f - HALLWAY_LENGTH, DOOR_SIZE / 2.f) + t_wallPosition);
		newWall->setFillColor(sf::Color(145, 26, 196));
		RenderObject::getInstance().addBridgeWalls(newWall);
		m_bridgeWalls.push_back(newWall);
		break;
	case Direction::None:
		DEBUG_MSG("SPAWNING NONE!");
		break;
	default:
		DEBUG_MSG("DEFAULT CASE FOR BRIDGE WALLS");
		break;
	}

	std::vector<int> level;
	for (int i = 0; i < static_cast<int>(DOOR_SIZE * HALLWAY_LENGTH); i++)
	{
		level.push_back(number);
	}
	newTile->load(sf::Vector2u(64, 64), level, static_cast<unsigned int>(DOOR_SIZE / 64.f + 2), static_cast<unsigned int>(HALLWAY_LENGTH / 64.f));

}
