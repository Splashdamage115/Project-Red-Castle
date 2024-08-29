#include "WaveManager.h"
#include "Game.h"

void WaveManager::init(std::shared_ptr<EnemyManager> t_enemyManager, std::shared_ptr<TileSetManager> t_tileSet)
{
	m_enemyManager = t_enemyManager;
	m_tileSet = t_tileSet;
}

void WaveManager::enteredNewRoom()
{
	m_roomSpawnAmt += 2;
	m_roomSpawnRemaining = m_roomSpawnAmt;
	m_waitingForNewRoom = false;
}

void WaveManager::update(sf::Vector2f t_playerPos)
{
	m_spawnDelay -= Game::deltaTime;

	if(m_spawnDelay <= 0.f)
	{
		if(m_roomSpawnRemaining >= 0)
		{
			sf::FloatRect bounds = m_tileSet->getActiveBounds(t_playerPos);
			sf::Vector2i currentTileStart = sf::Vector2i(static_cast<int>(bounds.left), static_cast<int>(bounds.top));
			sf::Vector2i currentTileSize = sf::Vector2i(static_cast<int>(bounds.width), static_cast<int>(bounds.height));

			EnemySetupInfo enemyInfo;
			enemyInfo.enemyType = static_cast<EnemyType>(rand() % 3);
			enemyInfo.moveSpeed = (rand() % 100) + 10;
			enemyInfo.spawnPos = sf::Vector2f(rand() % currentTileSize.x + currentTileStart.x, rand() % currentTileSize.y + currentTileStart.y);
			m_enemyManager->spawnNewEnemy(enemyInfo);

			m_spawnDelay = 2.f;
			m_roomSpawnRemaining--;
		}
		else if (!m_waitingForNewRoom)
		{
			if(m_enemyManager->getActiveEnemyCount() <= 0)
			{
				// TO DO: LEVEL CLEAR FAN FAIR
				m_tileSet->openDoors();
				m_waitingForNewRoom = true;
			}
		}
	}
}
