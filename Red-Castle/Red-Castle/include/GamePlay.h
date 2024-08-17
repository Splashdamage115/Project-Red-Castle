#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "GameMode.h"

// stuff to do with the game
#include "EnemyManager.h"
#include "Player.h"
#include "BulletManager.h"
#include "GunManager.h"
#include "PurchasableManager.h"
#include "ExtractManager.h"
#include "TileSetManager.h"
#include "WaveManager.h"

class GamePlay : public GameMode
{
public:
	GamePlay();  // standard constructor
	~GamePlay(); // standard deconstructor (shouldnt be used)

	void resetLevel()override;                         // used to reset the level for each session instead of reconstructing
	void events(sf::Event& t_event)override;           // used to handle all new events outside key presses
	void update()override;         // all update events

private:
	void processKeys(sf::Event& t_event)override;      // handles all key inputs
	void processMouse(sf::Event& t_event)override;     // handles all mouse events

	std::shared_ptr<EnemyManager> m_enemyManager;
	std::shared_ptr<PurchasableManager> m_purchasables;
	std::shared_ptr<TileSetManager> m_tileSet;
	WaveManager m_waveManager;
	ExtractManager m_extractors;
	Player m_player;
};

#endif // !GAMEPLAY_H
