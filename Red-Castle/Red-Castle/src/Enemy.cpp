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

void Enemy::init(EnemySetupInfo& t_type)
{
	m_health = t_type.health;
	m_active = true;
	m_moveSpeed = t_type.moveSpeed;

	m_currentMove = MoveExecute::None;
	// set the sprite based off the enemy type, and set other relevant parameters
	switch (t_type.enemyType)
	{
	case EnemyType::Slime:
		m_body = std::make_shared<AnimatedSprite>(0.25f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\Slime.png")); // initialisse the slime texture
		m_typeInfo = std::make_shared<Slime>();

		m_body->setScale(sf::Vector2f(0.15f, 0.15f)); // make the slime smaller
		m_currentMove = MoveExecute::Chase;
		m_collisionRadius = 100.f;
		break;
	case EnemyType::Goblin:
		m_body = std::make_shared<AnimatedSprite>(0.25f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\Goblin.png"));
		m_typeInfo = std::make_shared<Goblin>();

		m_body->setScale(sf::Vector2f(0.25f, 0.25f)); // make the Goblin smaller
		m_currentMove = MoveExecute::Chase;
		m_collisionRadius = 100.f;
		break;
	default:
		// default type is a barrel (no movement)
		m_body = std::make_shared<AnimatedSprite>(1.f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\ExplosiveBarrel.png"));
		m_typeInfo = std::make_shared<Barrel>();
		m_moveSpeed = 0.f;

		m_currentMove = MoveExecute::None;
		m_collisionRadius = 100.f;
		break;
	}

	m_typeInfo->getMoveFrames(m_body);

	//m_enemyType = t_type.enemyType;
	
	// set the enemy to the position passed
	m_body->setPosition(t_type.spawnPos);

	// set origin
	m_body->setOrigin(sf::Vector2f(m_body->getLocalBounds().width / 2.f, m_body->getLocalBounds().height / 2.f));

	// assign to be drawn
	RenderObject::getInstance().add(m_body);
}

void Enemy::update(sf::Vector2f& t_playerPos)
{
	if(m_active)
	{
		// update the animation
		m_body->update();

		switch (m_currentMove)
		{
		case MoveExecute::None:
			break;
		case MoveExecute::Chase:
			calculateMove(t_playerPos);
			break;
		case MoveExecute::Melee:
			attackMelee();
			break;
		case MoveExecute::Shoot:
			attackShoot();
			break;
		case MoveExecute::Expire:
			expire();
			break;
		case MoveExecute::ExpireFade:
			expireFade();
			break;
		default:
			break;
		}
	}
}

void Enemy::applyDamage(int t_damage)
{
	m_health -= t_damage;

	if (m_health <= 0)
	{
		m_currentMove = MoveExecute::Expire;
		m_inAnimation = false;
	}
}

// different Execute move types
void Enemy::calculateMove(sf::Vector2f& t_playerPos)
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

	if (math::distance(m_body->getPosition(), t_playerPos) <= m_typeInfo->getMeleeRadius())
		m_currentMove = MoveExecute::Melee;
	if (math::distance(m_body->getPosition(), t_playerPos) <= m_typeInfo->getShootRadius())
		m_currentMove = MoveExecute::Shoot;
}

void Enemy::attackMelee()
{
	if(!m_inAnimation)
	{
		m_typeInfo->getMeleeFrames(m_body);
			
		// change back when exiting attack
		m_inAnimation = true;
		m_maxAnimTime = m_typeInfo->getMeleeTime();
		m_currentAnimTime = 0.f;
	}
	if (m_currentAnimTime > m_maxAnimTime)
	{
		m_currentMove = MoveExecute::Chase;
		m_inAnimation = false;
		m_typeInfo->getMoveFrames(m_body);
	}
	m_currentAnimTime += Game::deltaTime;
}

void Enemy::attackShoot()
{
	/*switch (m_enemyType)
	{
	default:
		break;
	}*/
}

void Enemy::expire()
{
	if (!m_inAnimation)
	{
		m_typeInfo->getExpireFrames(m_body);

		// change back when exiting attack
		m_inAnimation = true;
		m_maxAnimTime = m_typeInfo->getExpireTime();
		m_currentAnimTime = 0.f;
	}
	if (m_currentAnimTime > m_maxAnimTime)
	{
		m_currentMove = MoveExecute::ExpireFade;
		m_inAnimation = false;
	}
	m_currentAnimTime += Game::deltaTime;
}

void Enemy::expireFade()
{
	if (!m_inAnimation)
	{
		m_typeInfo->getExpireFadeFrames(m_body);

		// change back when exiting attack
		m_inAnimation = true;
		m_maxAnimTime = m_typeInfo->getExpireFadeTime();
		m_currentAnimTime = 0.f;
	}
	if (m_currentAnimTime > m_maxAnimTime)
	{
		m_active = false;
		m_body->setActive(false);
		m_body->setPosition(sf::Vector2f(-100000.f, -100000.f));
	}
	m_currentAnimTime += Game::deltaTime;
}
