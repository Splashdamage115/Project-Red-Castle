#ifndef ENEMY_H
#define ENEMY_H

#include "Library.h"
#include "AnimatedSprite.h"

// all enemy types
enum class EnemyType
{
	None, Slime
};

struct EnemyInfo
{
	EnemyType enemyType{ EnemyType::None }; // initilise enemy to a type
	sf::Vector2f spawnPos{ 0.f,0.f };       // where the enemy spawns
	float moveSpeed{ 0.f };                 // speed the enemy moves at
};

class Enemy
{
public:
	Enemy();
	~Enemy();

	void init(EnemyInfo& t_type);
	void update(sf::Vector2f& t_playerPos);

private:
	std::shared_ptr<AnimatedSprite> m_body; // animated body of the enemy

	float m_moveSpeed{ 0.f };               // distance the enemy moves at every second (pixels)
};

#endif // !ENEMY_H