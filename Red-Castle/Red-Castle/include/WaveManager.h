#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include "Library.h"
#include "EnemyManager.h"
#include "TileSetManager.h"

class WaveManager
{
public:
	void init(std::shared_ptr<EnemyManager> t_enemyManager, std::shared_ptr<TileSetManager> t_tileSet);

	void update();
private:
	std::shared_ptr<EnemyManager> m_enemyManager;
	std::shared_ptr<TileSetManager> m_tileSet;

	float m_spawnDelay{ 5.f };
};

#endif // !WAVE_MANAGER_H
