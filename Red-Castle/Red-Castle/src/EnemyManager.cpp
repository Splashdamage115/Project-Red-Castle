#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::spawnNewEnemy(EnemySetupInfo& t_enemyInfo)
{
	// initialise enemy into a vector (no overflow protection yet)
	Enemy newEnemy;
	newEnemy.init(t_enemyInfo);
	m_enemies.push_back(newEnemy);
}

void EnemyManager::update(sf::Vector2f& t_playerPos)
{
	// update all enemies with the position
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i).update(t_playerPos);
	}
}
