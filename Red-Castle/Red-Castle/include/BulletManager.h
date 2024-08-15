#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "Bullet.h"

class BulletManager
{
public:
	static BulletManager& getInstance()
	{
		static BulletManager instance;
		return instance;
	}
	// DELETE FUNCTIONS TO AVOID MORE INSTANCES
	BulletManager(BulletManager const&) = delete;
	void operator=(BulletManager const&) = delete;


	void initNewBullet(sf::Vector2f t_pawnPos, float t_angle, float t_timeAlive, int t_damage, float t_speed, float t_explosiveRadius);
	void initNewEnemyBullet(sf::Vector2f t_pawnPos, float t_angle, float t_timeAlive, int t_damage, float t_speed, float t_explosiveRadius);
	void updateBullets();

	inline std::vector<Bullet>& getBullets() { return m_bullets; }
	inline std::vector<Bullet>& getBulletsEnemy() { return m_bulletsEnemy; }
private:
	BulletManager();
	std::vector<Bullet> m_bullets;
	std::vector<Bullet> m_bulletsEnemy;
};

#endif // !BULLET_MANAGER_H
