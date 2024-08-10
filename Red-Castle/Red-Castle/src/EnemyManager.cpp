#include "EnemyManager.h"
#include "CollisionDetector.h"
#include "ExplosiveManager.h"
#include "simpleMaths.h"
#include "SoundPlayer.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::spawnNewEnemy(EnemySetupInfo& t_enemyInfo)
{
	// initialise enemy into a vector (no overflow protection yet)
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		if (!m_enemies.at(i).getActive())
		{
			m_enemies.at(i).init(t_enemyInfo);
			return;
		}
	}

	Enemy newEnemy;
	newEnemy.init(t_enemyInfo);
	m_enemies.push_back(newEnemy);
}

void EnemyManager::update(sf::Vector2f& t_playerPos)
{
	// update all enemies with the position
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i).update(t_playerPos);
	}
}

void EnemyManager::checkHits(std::vector<Bullet>& t_bullets)
{
	for (unsigned int bullet = 0; bullet < t_bullets.size(); bullet++)
	{
		if (!t_bullets.at(bullet).active)
			continue;

		for (unsigned int enemy = 0; enemy < m_enemies.size(); enemy++)
		{
			if (!m_enemies.at(enemy).getActive())
				continue;
			if(!m_enemies.at(enemy).canApplyDamage())
				continue;

			if (m_enemies.at(enemy).getBounds().intersects(t_bullets.at(bullet).body->getGlobalBounds()))
			{
				if (CollisionDetector::pixelPerfectTest(m_enemies.at(enemy).getSprite(), t_bullets.at(bullet).body->getSprite()))
				{
					SoundPlayer::getInstance().playNewSound("ASSETS\\SOUNDS\\ShotHit-basic.wav");
					m_enemies.at(enemy).applyDamage(t_bullets.at(bullet).damage);
					t_bullets.at(bullet).deactivate();
					break;
				}
			}
		}
	}
}

void EnemyManager::checkExplosions()
{
	std::vector<ExplosiveRadius> radii = ExplosiveManager::getInstance().getRadii();
	for (unsigned int enemy = 0; enemy < m_enemies.size(); enemy++)
	{
		if (!m_enemies.at(enemy).getActive())
			continue;
		if (!m_enemies.at(enemy).canApplyDamage())
			continue;

		for (unsigned int Explosive = 0; Explosive < radii.size(); Explosive++)
		{
			if (!radii.at(Explosive).active)
				continue;

			if (math::circleIntersects(radii.at(Explosive).center, m_enemies.at(enemy).getPos(), radii.at(Explosive).radius,m_enemies.at(enemy).getRadius()))
			{
				if (CollisionDetector::pixelPerfectTest(radii.at(Explosive).body->getSprite(), m_enemies.at(enemy).getSprite()))
				{
					m_enemies.at(enemy).applyDamage(radii.at(Explosive).damage);
				}
			}
		}
	}
	
}
