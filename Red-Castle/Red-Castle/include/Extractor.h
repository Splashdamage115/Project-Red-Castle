#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include "Library.h"
#include "AnimatedSprite.h"
#include "GunManager.h"
#include "EnemyManager.h"

class ExtractorCharacter
{
public:
	ExtractorCharacter();
	void init(sf::Vector2f t_position, bool t_roper);

	void update(sf::Vector2f& t_playerPos, EnemyManager& t_enemyManager);

	bool getLeaving() { return m_leaving; }
	sf::Vector2f getFollowPos() { return m_body->getPosition(); }
private:
	std::shared_ptr<AnimatedSprite> m_body;
	std::shared_ptr<sf::RectangleShape> m_ropeLine;

	GunManager m_weapon;
	bool m_active{ false };
	float m_moveSpeed{ 100.f };
	bool m_roper{ false };

	bool m_grabbing{ false };
	float m_leavingTime{ -1.0f };
	bool m_leaving{ false };
};
#endif // !EXTRACTOR_H
