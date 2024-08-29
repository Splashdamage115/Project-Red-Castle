#include "TileSetManager.h"
#include "RenderObject.h"
#include "Game.h"
#include "simpleMaths.h"

void TileSetManager::init()
{
	spawnBox(sf::Vector2f(0.f, 0.f));
	spawnWalls(sf::Vector2f(0.f, 0.f));

	spawnBox(sf::Vector2f(0.f, 3000.f));
	spawnWalls(sf::Vector2f(0.f, 3000.f));
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
	for (unsigned int i = 0; i < m_activeArea.size(); i++)
	{
		if (m_activeArea.at(i)->getGlobalBounds().contains(t_playerPos))
		{
			return m_activeArea.at(i)->getGlobalBounds();
		}
	}
	return m_activeArea.at(0)->getGlobalBounds();
}

std::vector<std::shared_ptr<sf::RectangleShape>>& TileSetManager::getWalls(sf::Vector2f t_playerPos)
{
	for (unsigned int i = 0; i < m_walls.size(); i++)
	{
		if (m_activeArea.at(i)->getGlobalBounds().contains(t_playerPos))
		{
			return m_walls.at(i);
		}
	}
	return m_walls.at(0); // make this return bridge walls!
}

bool TileSetManager::closeDoors(sf::FloatRect t_playerBounds)
{
	if (m_closed == true || m_animationTimeRemaining > 0.f)
		return false;

	for (unsigned int i = 0; i < m_activeArea.size(); i++)
	{
		if (m_activeArea.at(i)->getGlobalBounds().contains(t_playerBounds.getPosition())) // check if the player is in an area
		{
			if (m_activeArea.at(i)->getGlobalBounds().contains(t_playerBounds.getPosition() + t_playerBounds.getSize())) // check if fully contained in that area
			{
				m_activeAreaNum = i;
				if(m_enemyRoom.at(m_activeAreaNum))
				{
					m_animationTimeRemaining = DOOR_CLOSE_TIME;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return false;
}

void TileSetManager::openDoors()
{
	m_animationTimeRemaining = DOOR_CLOSE_TIME;
}

void TileSetManager::spawnBox(sf::Vector2f t_topLeftPosition)
{
	std::shared_ptr<sf::RectangleShape> newArea;
	newArea = std::make_shared<sf::RectangleShape>(sf::Vector2f(2000.f, 2000.f));
	newArea->setPosition(sf::Vector2f(-1000.f, -50.f) + t_topLeftPosition);
	newArea->setFillColor(sf::Color(41, 87, 100));
	RenderObject::getInstance().addBG(newArea);

	m_activeArea.push_back(newArea);
}

void TileSetManager::spawnWalls(sf::Vector2f t_topLeftPosition)
{
	std::vector<std::shared_ptr<sf::RectangleShape>> wallHolder;

	std::vector<bool> doorDirections; // used for temporary assigning, future will change directions
	//doorDirections.push_back(Direction::North);

	for (int i = 0; i < 4; i++)
	{
		if (rand() % 2 == 1)
		{
			doorDirections.push_back(true);
		}
		else
		{
			doorDirections.push_back(false);
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
			newDoorCollision = std::make_shared<sf::RectangleShape>(sf::Vector2f(410.f, 50.f));
			newDoorCollision->setPosition(sf::Vector2f(-200.f, -100.f) + t_topLeftPosition);
			RenderObject::getInstance().addBG(newDoorCollision);
			wallHolder.push_back(newDoorCollision);
			if(doorDirections.at(i))
			{
				newDoor.m_doorSprite = newDoorCollision;
				newDoorCollision->setFillColor(sf::Color(219, 155, 7));
				newDoor.m_closedPos = newDoorCollision->getPosition();
				newDoor.m_openPos = newDoorCollision->getPosition() + sf::Vector2f(-400.f, 0.f);
				holdVector.push_back(newDoor);
			}
			else
			{
				newDoorCollision->setFillColor(sf::Color(43, 148, 41));
			}
			break;
		case Direction::East:
			newDoorCollision = std::make_shared<sf::RectangleShape>(sf::Vector2f(50.f, 410.f));
			newDoorCollision->setPosition(sf::Vector2f(-1050.f, 700.f) + t_topLeftPosition);
			RenderObject::getInstance().addBG(newDoorCollision);
			wallHolder.push_back(newDoorCollision);
			if (doorDirections.at(i))
			{
				newDoor.m_doorSprite = newDoorCollision;
				newDoorCollision->setFillColor(sf::Color(219, 155, 7));
				newDoor.m_closedPos = newDoorCollision->getPosition();
				newDoor.m_openPos = newDoorCollision->getPosition() + sf::Vector2f(0.f, -400.f);
				holdVector.push_back(newDoor);
			}
			else
			{
				newDoorCollision->setFillColor(sf::Color(43, 148, 41));
			}
			break;
		case Direction::South:
			newDoorCollision = std::make_shared<sf::RectangleShape>(sf::Vector2f(410.f, 50.f));
			newDoorCollision->setPosition(sf::Vector2f(-200.f, 1950.f) + t_topLeftPosition);
			RenderObject::getInstance().addBG(newDoorCollision);
			wallHolder.push_back(newDoorCollision);
			if (doorDirections.at(i))
			{
				newDoor.m_doorSprite = newDoorCollision;
				newDoorCollision->setFillColor(sf::Color(219, 155, 7));
				newDoor.m_closedPos = newDoorCollision->getPosition();
				newDoor.m_openPos = newDoorCollision->getPosition() + sf::Vector2f(-400.f, 0.f);
				holdVector.push_back(newDoor);
			}
			else
			{
				newDoorCollision->setFillColor(sf::Color(43, 148, 41));
			}
			break;
		case Direction::West:
			newDoorCollision = std::make_shared<sf::RectangleShape>(sf::Vector2f(50.f, 410.f));
			newDoorCollision->setPosition(sf::Vector2f(1000.f, 700.f) + t_topLeftPosition);
			RenderObject::getInstance().addBG(newDoorCollision);
			wallHolder.push_back(newDoorCollision);
			if (doorDirections.at(i))
			{
				newDoor.m_doorSprite = newDoorCollision;
				newDoorCollision->setFillColor(sf::Color(219, 155, 7));
				newDoor.m_closedPos = newDoorCollision->getPosition();
				newDoor.m_openPos = newDoorCollision->getPosition() + sf::Vector2f(0.f, -400.f);
				holdVector.push_back(newDoor);
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
	m_doors.push_back(holdVector);
	
	// TOP WALLS
	std::shared_ptr<sf::RectangleShape> newWall;
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(850.f, 50.f));
	newWall->setPosition(sf::Vector2f(-1050.f, -100.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addBG(newWall);
	wallHolder.push_back(newWall);
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(850.f, 50.f));
	newWall->setPosition(sf::Vector2f(200.f, -100.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addBG(newWall);
	wallHolder.push_back(newWall);


	// LEFT WALLS
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(50.f, 850.f));
	newWall->setPosition(sf::Vector2f(-1050.f, -100.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addBG(newWall);
	wallHolder.push_back(newWall);
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(50.f, 850.f));
	newWall->setPosition(sf::Vector2f(-1050.f, 1100.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addBG(newWall);
	wallHolder.push_back(newWall);


	// RIGHT WALLS
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(50.f, 850.f));
	newWall->setPosition(sf::Vector2f(1000.f, -100.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addBG(newWall);
	wallHolder.push_back(newWall);
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(50.f, 850.f));
	newWall->setPosition(sf::Vector2f(1000.f, 1100.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addBG(newWall);
	wallHolder.push_back(newWall);

	// BOTTOM WALLS
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(850.f, 50.f));
	newWall->setPosition(sf::Vector2f(-1050.f, 1950.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addBG(newWall);
	wallHolder.push_back(newWall);
	newWall = std::make_shared<sf::RectangleShape>(sf::Vector2f(850.f, 50.f));
	newWall->setPosition(sf::Vector2f(200.f, 1950.f) + t_topLeftPosition);
	newWall->setFillColor(sf::Color(43, 148, 41));
	RenderObject::getInstance().addBG(newWall);
	wallHolder.push_back(newWall);

	
	wallHolder.push_back(newWall);
	m_walls.push_back(wallHolder);
	m_enemyRoom.push_back(true);
}

void TileSetManager::closeDoorsAnimation()
{
	for (unsigned int i = 0; i < m_doors.at(m_activeAreaNum).size(); i++)
	{
		if(math::distance(m_doors.at(m_activeAreaNum).at(i).m_doorSprite->getPosition(), m_doors.at(m_activeAreaNum).at(i).m_closedPos) > 5.f)
			m_doors.at(m_activeAreaNum).at(i).m_doorSprite->move(math::displacement(m_doors.at(m_activeAreaNum).at(i).m_doorSprite->getPosition(), m_doors.at(m_activeAreaNum).at(i).m_closedPos) * 800.f * Game::deltaTime);
	}
	if (m_animationTimeRemaining <= 0.f)
	{
		m_closed = true;
	}
}

void TileSetManager::openDoorsAnimation()
{
	for (unsigned int i = 0; i < m_doors.at(m_activeAreaNum).size(); i++)
	{
		if (math::distance(m_doors.at(m_activeAreaNum).at(i).m_doorSprite->getPosition(), m_doors.at(m_activeAreaNum).at(i).m_openPos) > 5.f)
			m_doors.at(m_activeAreaNum).at(i).m_doorSprite->move(math::displacement(m_doors.at(m_activeAreaNum).at(i).m_doorSprite->getPosition(), m_doors.at(m_activeAreaNum).at(i).m_openPos) * 800.f * Game::deltaTime);
	}
	if (m_animationTimeRemaining <= 0.f)
	{
		m_closed = false;
		m_enemyRoom.at(m_activeAreaNum) = false;
	}
}
