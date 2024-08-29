#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "Library.h"
#include "EnemyManager.h"
#include "TileSetManager.h"

class WaveManager
{
public:
	void init(std::shared_ptr<EnemyManager> t_enemyManager, std::shared_ptr<TileSetManager> t_tileSet);

	void enteredNewRoom();

	void update(sf::Vector2f t_playerPos);
private:
	std::shared_ptr<EnemyManager> m_enemyManager;
	std::shared_ptr<TileSetManager> m_tileSet;

	float m_spawnDelay{ 5.f };
	int m_roomSpawnAmt{ 10 };
	int m_roomSpawnRemaining{ 10 };
	bool m_waitingForNewRoom{ false };
};

#endif // !WAVE_MANAGER_H
