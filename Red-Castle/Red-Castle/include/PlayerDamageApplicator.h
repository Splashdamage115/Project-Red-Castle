#ifndef PLAYER_DAMAGE_APPLICATOR_H
#define PLAYER_DAMAGE_APPLICATOR_H

#include "Player.h"
#include "Enemy.h"
#include "BulletManager.h"

class PlayerDamageApplicator
{
public:
	static void checkHits(Player& t_player, std::vector<Enemy> t_enemies)
	{
		for (unsigned int i = 0; i < t_enemies.size(); i++)
		{
			if (t_player.getBounds().intersects(t_enemies.at(i).getdamageBox()))
			{
				t_player.applyDamage(1);
			}
		}
	}

	static void checkHitsBullets(Player& t_player)
	{
		std::vector<Bullet>& enemyBullets = BulletManager::getInstance().getBulletsEnemy();
		for (unsigned int i = 0; i < enemyBullets.size(); i++)
		{
			if (t_player.getBounds().intersects(enemyBullets.at(i).body->getGlobalBounds()))
			{
				t_player.applyDamage(1);
				enemyBullets.at(i).deactivate();
				
			}
		}
	}
};

#endif // !PLAYER_DAMAGE_APPLICATOR_H
