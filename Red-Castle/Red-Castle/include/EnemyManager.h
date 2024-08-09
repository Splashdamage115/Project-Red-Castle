#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void spawnNewEnemy(EnemySetupInfo& t_enemyInfo);

	void update(sf::Vector2f& t_playerPos);

private:
	std::vector<Enemy> m_enemies; // vector of all enemies
};

#endif // !ENEMY_MANAGER_H