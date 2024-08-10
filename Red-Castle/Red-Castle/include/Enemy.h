#ifndef ENEMY_H
#define ENEMY_H

#include "Library.h"
#include "AnimatedSprite.h"
#include "EnemyInfo.h"

// all enemy types
enum class EnemyType
{
	None, Slime, Goblin
};

struct EnemySetupInfo
{
	EnemyType enemyType{ EnemyType::None }; // initilise enemy to a type
	sf::Vector2f spawnPos{ 0.f,0.f };       // where the enemy spawns
	float moveSpeed{ 0.f };                 // speed the enemy moves at
	int health{ 10 };
};

enum class MoveExecute
{
	None, Chase, Melee, Shoot, Expire, ExpireFade
};

class Enemy
{
public:
	Enemy();
	~Enemy();

	void init(EnemySetupInfo& t_type);
	void update(sf::Vector2f& t_playerPos);

	bool inline getActive() { return m_active; }
	sf::FloatRect getBounds() { return m_body->getGlobalBounds(); }
	sf::Sprite getSprite() { return m_body->getSprite(); }
	void applyDamage(int t_damage);
	bool canApplyDamage() { return (m_currentMove != MoveExecute::Expire && m_currentMove != MoveExecute::ExpireFade); }
	sf::Vector2f getPos() { return m_body->getPosition(); }
	float getRadius() { return m_collisionRadius; }
private:
	void calculateMove(sf::Vector2f& t_playerPos);
	void attackMelee();
	void attackShoot();
	void expire();
	void expireFade();

	std::shared_ptr<AnimatedSprite> m_body; // animated body of the enemy
	//EnemyType m_enemyType{ EnemyType::None };
	std::shared_ptr<EnemyInfo> m_typeInfo;
	MoveExecute m_currentMove{ MoveExecute::None };
	bool m_inAnimation{ false };
	float m_currentAnimTime{ 0.f };
	float m_maxAnimTime{ 0.f };
	int m_health{ 10 };

	float m_moveSpeed{ 0.f };               // distance the enemy moves at every second (pixels)
	bool m_active{ false };
	float m_collisionRadius{ 100.f };
};

#endif // !ENEMY_H