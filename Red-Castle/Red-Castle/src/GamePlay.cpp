#include "GamePlay.h"
#include "ExplosiveManager.h"
#include "Particles.h"
#include <ctime>
#include "BulletManager.h"
#include "EnemyDrops.h"
#include "PlayerDamageApplicator.h"
#include "Game.h"
#include "BuffHolder.h"
#include "PlayerBuffInterpretter.hpp"


/// <summary>
/// default constructor
/// </summary>
GamePlay::GamePlay()
{
	resetLevel();

	m_simpleButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("close doors"));
	m_simpleButtons.push_back(SimpleButtonHolder::getInstance().spawnNewButton("open doors"));
}

/// <summary>
/// default deconstructor
/// </summary>
GamePlay::~GamePlay()
{
}

/// <summary>
/// resets all values to default as needed
/// </summary>
void GamePlay::resetLevel()
{
	m_player.init(sf::Vector2f(250.f, 250.f));

	m_enemyManager = std::make_shared<EnemyManager>();
	m_purchasables = std::make_shared<PurchasableManager>();

	m_tileSet = std::make_shared<TileSetManager>();
	m_tileSet->init(m_purchasables);

	m_waveManager.init(m_enemyManager, m_tileSet);

	srand(static_cast<unsigned int>(time(nullptr)));
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void GamePlay::events(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type || sf::Event::KeyReleased == t_event.type) //user pressed a key
	{
		processKeys(t_event);
	}
	else
	{
		processMouse(t_event);
	}
}

/// !!!---Private function---!!!
/// <summary>
/// process any input from the user
/// </summary>
/// <param name="t_event">use this for the key press</param>
void GamePlay::processKeys(sf::Event& t_event)
{
	if (t_event.key.code == sf::Keyboard::Space)
	{
		//m_levelUp = true;

		//m_levelUpScreen = std::make_shared<LevelUpScreen>();
		//m_levelUpScreen->init();
	}
	if (t_event.key.code == sf::Keyboard::F)
	{
		m_purchasables->tryPurchase(m_player);
	}
	if (sf::Event::KeyReleased == t_event.type)
	{
		m_player.buttonReleased(t_event.key.code);
	}
}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GamePlay::update()
{
	// ***********************************************
	// DEBUG PURPOSSES OF APPLICATION
	// ***********************************************
	if(m_simpleButtons.at(0)->clicked())
	{
		
	}
	if (m_simpleButtons.at(1)->clicked())
	{
		m_tileSet->openDoors();
	}
	// ***********************************************

	if (m_levelUp)
	{
		m_levelUpScreen->update();
		if (m_levelUpScreen->checkClosed())
		{
			m_levelUp = false;
			m_levelUpScreen = nullptr;

			if (BuffHolder::getInstance().getAlert())
				interpretApplicators();

			m_player.refillHealth();
		}
	}
	else
	{
		m_tileSet->closeDoors(m_player.getBounds());
		if (m_tileSet->checkSpawnEnemiesRoom())
			m_waveManager.enteredNewRoom();

		m_purchasables->update();
		findMousePosGlobal(); // mouse in the world
		m_player.setAimVector(m_mousePosGlobal);
		ParticleSystem::getInstance().update();
		BulletManager::getInstance().updateBullets();
		BulletManager::getInstance().checkWallCollisions(m_tileSet->getWalls(m_player.getPos()));
		m_player.update(m_tileSet->getWalls(m_player.getPos()));
		m_enemyManager->update(m_player.getPos()); // enemies always chase player
		m_tileSet->update();

		m_enemyManager->checkHits();
		ExplosiveManager::getInstance().updateExplosions();
		m_enemyManager->checkExplosions();
		m_purchasables->checkCollisions(m_player.getBounds());
		DropManager::getInstance().update(m_player);

		PlayerDamageApplicator::checkHits(m_player, m_enemyManager->getEnemies());
		PlayerDamageApplicator::checkHitsBullets(m_player);

		m_extractors.checkExtract(m_player, *m_enemyManager);

		m_waveManager.update(m_player.getPos());

		if (BuffHolder::getInstance().getAlert())
			interpretApplicators();
		else
			if (m_levelHandler.checkXp(m_player))
			{
				m_levelUp = true;

				m_levelUpScreen = std::make_shared<LevelUpScreen>();
				m_levelUpScreen->init();
			}
	}
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void GamePlay::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		if (m_levelUp)
		{
			m_levelUpScreen->setMouse(m_mousePos);
		}
		findMousePos(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (m_levelUp)
		{
			m_levelUpScreen->mouseDown();
		}
		m_player.setMouse(true);
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		if (m_levelUp)
		{
			m_levelUpScreen->mouseUp();
		}
		m_player.setMouse(false);
		//BulletManager::getInstance().initNewBullet(m_player.getPos(), m_mousePosGlobal, 20.f);
	}
}

void GamePlay::interpretApplicators()
{
	std::vector<std::shared_ptr<Buff>> buffs = BuffHolder::getInstance().getOneTimeApplicators();

	for (auto& buff : buffs)
	{
		if (buff->active)
		{
			if (buff->applyLocation == AlertClassName::Player)
			{
				PlayerBuffInterpretter::InterpretPlayerBuffs(m_player, buff);
			}
		}
	}
}

