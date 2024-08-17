#include "WaveManager.h"
#include "Game.h"

void WaveManager::init(std::shared_ptr<EnemyManager> t_enemyManager, std::shared_ptr<TileSetManager> t_tileSet)
{
	m_enemyManager = t_enemyManager;
	m_tileSet = t_tileSet;
}

void WaveManager::update()
{
	m_spawnDelay -= Game::deltaTime;

	if(m_spawnDelay <= 0.f)
	{
		sf::Vector2i currentTileStart = sf::Vector2i(static_cast<int>(m_tileSet->getActiveBounds().left), static_cast<int>(m_tileSet->getActiveBounds().top));
		sf::Vector2i currentTileSize = sf::Vector2i(static_cast<int>(m_tileSet->getActiveBounds().width), static_cast<int>(m_tileSet->getActiveBounds().height));

		EnemySetupInfo enemyInfo;
		enemyInfo.enemyType = static_cast<EnemyType>(rand() % 3);
		enemyInfo.moveSpeed = (rand() % 100) + 10;
		enemyInfo.spawnPos = sf::Vector2f(rand() % currentTileSize.x + currentTileStart.x, rand() % currentTileSize.y + currentTileStart.y);
		m_enemyManager->spawnNewEnemy(enemyInfo);

		m_spawnDelay = 2.f;
	}
}
