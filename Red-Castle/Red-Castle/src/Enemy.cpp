#include "Enemy.h"
#include "TextureLoader.h"
#include "RenderObject.h"
#include "simpleMaths.h"
#include "Game.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(EnemyInfo& t_type)
{
	m_moveSpeed = t_type.moveSpeed;


	// set the sprite based off the enemy type, and set other relevant parameters
	switch (t_type.enemyType)
	{
	case EnemyType::Slime:
		m_body = std::make_shared<AnimatedSprite>(1.f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\Slime.png"));
		m_body->addFrame(sf::IntRect(0, 0, 300, 300));
		m_body->setScale(sf::Vector2f(0.15f, 0.15f));
		break;


	default:
		// default type is a barrel (no movement)
		m_body = std::make_shared<AnimatedSprite>(1.f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\ExplosiveBarrel.png"));
		m_body->addFrame(sf::IntRect(0, 0, 40, 63));
		m_moveSpeed = 0.f;
		break;
	}

	
	// set the enemy to the position passed
	m_body->setPosition(t_type.spawnPos);

	// set origin
	m_body->setOrigin(sf::Vector2f(m_body->getLocalBounds().width / 2.f, m_body->getLocalBounds().height / 2.f));

	// assign to be drawn
	RenderObject::getInstance().add(m_body);
}

void Enemy::update(sf::Vector2f& t_playerPos)
{
	// move enemy towards player
	sf::Vector2f enemyMove = math::displacement(m_body->getPosition(), t_playerPos) * m_moveSpeed * Game::deltaTime;
	m_body->move(enemyMove);

	// flip the character depending on movement
	if (enemyMove.x > 0.f)
	{
		m_body->setScale(sf::Vector2f(-std::abs(m_body->getScale().x), m_body->getScale().y));
	}
	else if (enemyMove.x < 0.f)
	{
		m_body->setScale(sf::Vector2f(std::abs(m_body->getScale().x), m_body->getScale().y));
	}
}
