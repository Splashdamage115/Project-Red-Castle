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
};

enum class MoveExecute
{
	None, Chase, Melee, Shoot
};

class Enemy
{
public:
	Enemy();
	~Enemy();

	void init(EnemySetupInfo& t_type);
	void update(sf::Vector2f& t_playerPos);

private:
	void calculateMove(sf::Vector2f& t_playerPos);
	void attackMelee();
	void attackShoot();

	std::shared_ptr<AnimatedSprite> m_body; // animated body of the enemy
	//EnemyType m_enemyType{ EnemyType::None };
	std::shared_ptr<EnemyInfo> m_typeInfo;
	MoveExecute m_currentMove{ MoveExecute::None };
	bool m_inAnimation{ false };
	float m_currentAnimTime{ 0.f };
	float m_maxAnimTime{ 0.f };

	float m_moveSpeed{ 0.f };               // distance the enemy moves at every second (pixels)
};

#endif // !ENEMY_H