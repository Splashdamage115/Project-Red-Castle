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

// used for setting up a new enemy
struct EnemySetupInfo
{
	EnemyType enemyType{ EnemyType::None }; // initilise enemy to a type
	sf::Vector2f spawnPos{ 0.f,0.f };       // where the enemy spawns
	float moveSpeed{ 0.f };                 // speed the enemy moves at
	int health{ 10 };
};

// used for state machine
enum class MoveExecute
{
	None, Chase, Melee, Shoot, Expire, ExpireFade
};

class Enemy
{
public:
	// *******************************************
	// normal spawn / update calls
	// *******************************************
	Enemy();
	~Enemy();

	void init(EnemySetupInfo& t_type);
	void update(sf::Vector2f& t_playerPos);
	// *******************************************

	void applyDamage(int t_damage);

	sf::FloatRect getdamageBox();

	// *******************************************
	// standard getters / setters
	// *******************************************
	bool inline getActive() { return m_active; }
	sf::FloatRect getBounds() { return m_body->getGlobalBounds(); }
	sf::Sprite getSprite() { return m_body->getSprite(); }
	bool canApplyDamage() { return (m_currentMove != MoveExecute::Expire && m_currentMove != MoveExecute::ExpireFade); }
	sf::Vector2f getPos() { return m_body->getPosition(); }
	float getRadius() { return m_collisionRadius; }
	bool getAlive() { return m_alive; }
	// *******************************************
private:

	// *******************************************
	// used for simple state machine
	// *******************************************
	void calculateMove(sf::Vector2f& t_playerPos);

	void attackMelee();
	void attackShoot(sf::Vector2f& t_playerPos);
	void expire();
	void expireFade();
	// *******************************************

	std::shared_ptr<AnimatedSprite> m_body; // animated body of the enemy
	std::shared_ptr<AnimatedSprite> m_spawnAnim;
	std::shared_ptr<AnimatedSprite> m_shadow;
	std::shared_ptr<EnemyInfo> m_typeInfo; // used to get the used animation
	MoveExecute m_currentMove{ MoveExecute::None }; // current state of the enemy

	// used for animations
	bool m_inAnimation{ false };
	float m_currentAnimTime{ 0.f };
	float m_maxAnimTime{ 0.f };
	bool m_spawning{ false };
	//
	
	int m_health{ 10 };						// health == 0 moves enemy to death
	float m_moveSpeed{ 0.f };               // distance the enemy moves at every second (pixels)
	bool m_active{ false };                 // for speed checks and pointer checks
	float m_collisionRadius{ 30.f };       // distance to check collisions in

	std::shared_ptr<sf::RectangleShape> m_stabBox;
	bool m_alive{ false };

	float m_damageTime{ 0.f };
	std::shared_ptr<sf::Shader> m_fragmentShader;
};

#endif // !ENEMY_H