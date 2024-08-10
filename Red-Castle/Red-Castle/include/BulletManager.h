#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "Bullet.h"

class BulletManager
{
public:
	BulletManager();

	void initNewBullet(sf::Vector2f t_pawnPos, sf::Vector2f t_aimPos, float t_spread);
	void updateBullets();

	inline std::vector<Bullet>& getBulets() { return m_bullets; }
private:
	std::vector<Bullet> m_bullets;
};

#endif // !BULLET_MANAGER_H
