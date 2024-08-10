#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Enemy.h"
#include "Bullet.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void spawnNewEnemy(EnemySetupInfo& t_enemyInfo);

	void update(sf::Vector2f& t_playerPos);

	void checkHits(std::vector<Bullet>& t_bullets);
	void checkExplosions();
private:
	std::vector<Enemy> m_enemies; // vector of all enemies
};

#endif // !ENEMY_MANAGER_H