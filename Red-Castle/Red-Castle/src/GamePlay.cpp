#include "GamePlay.h"
#include "ExplosiveManager.h"
#include "Particles.h"
#include <ctime>


/// <summary>
/// default constructor
/// </summary>
GamePlay::GamePlay()
{
	resetLevel();
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
	// spawn enemy on random type, position and speed
	if (t_event.key.code == sf::Keyboard::Space)
	{
		EnemySetupInfo enemyInfo;
		enemyInfo.enemyType = static_cast<EnemyType>(rand() % 3);
		enemyInfo.moveSpeed = (rand() % 100) + 10;
		enemyInfo.spawnPos = sf::Vector2f(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		m_enemyManager.spawnNewEnemy(enemyInfo);
	}
}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GamePlay::update()
{
	findMousePosGlobal(); // mouse in the world
	ParticleSystem::getInstance().update();
	m_bulletManager.updateBullets();
	m_player.update();
	m_enemyManager.update(m_player.getPos()); // enemies always chase player

	m_enemyManager.checkHits(m_bulletManager.getBulets());
	ExplosiveManager::getInstance().updateExplosions();
	m_enemyManager.checkExplosions();
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void GamePlay::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		//mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		m_bulletManager.initNewBullet(m_player.getPos(), m_mousePosGlobal, 20.f);
	}
}
