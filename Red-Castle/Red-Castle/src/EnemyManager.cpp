#include "EnemyManager.h"
#include "CollisionDetector.h"
#include "ExplosiveManager.h"
#include "simpleMaths.h"
#include "SoundPlayer.h"
#include "Particles.h"
#include "BulletManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

// start a new enemy
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

// pass update
void EnemyManager::update(sf::Vector2f& t_playerPos)
{
	// update all enemies with the position
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i).update(t_playerPos);
	}
}

// check if collidiing with any bullet
void EnemyManager::checkHits()
{
	std::vector<Bullet>t_bullets = BulletManager::getInstance().getBullets();

	for (unsigned int bullet = 0; bullet < t_bullets.size(); bullet++)
	{
		if (!t_bullets.at(bullet).active)
		{
			//DEBUG_MSG("body inactive");
			continue;
		}
		if (t_bullets.at(bullet).body == nullptr)
		{
			//DEBUG_MSG("body NULL");
			continue;
		}

		for (unsigned int enemy = 0; enemy < m_enemies.size(); enemy++)
		{
			if (!m_enemies.at(enemy).getActive())
				continue;
			if(!m_enemies.at(enemy).canApplyDamage())
				continue;
			if (m_enemies.at(enemy).getSprite().getTexture()->getSize().x <= 0)
				continue;
			if (m_enemies.at(enemy).getSprite().getTexture()->getSize().y <= 0)
				continue;

			if (m_enemies.at(enemy).getBounds().intersects(t_bullets.at(bullet).body->getGlobalBounds()))
			{
				//if (CollisionDetector::pixelPerfectTest(m_enemies.at(enemy).getSprite(), t_bullets.at(bullet).body->getSprite()))
				//{
					SoundPlayer::getInstance().playNewSound("ASSETS\\SOUNDS\\ShotHit-basic.wav");
					m_enemies.at(enemy).applyDamage(t_bullets.at(bullet).damage);

					ParticleSystem::getInstance().spawnNewParticle(std::string(std::to_string(t_bullets.at(bullet).damage)),m_enemies.at(enemy).getPos(), 24u, sf::Vector2f(0.f, -1.f), 50.f, 1.f,60.f);

					t_bullets.at(bullet).deactivate();
					break;
				//}
			}
		}

	}
}

// check collision with any explosive radius
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
					ParticleSystem::getInstance().spawnNewParticle("FIRE", m_enemies.at(enemy).getPos(), 24u, sf::Vector2f(0.f, -1.f), 50.f, 1.f, 60.f, sf::Color::Red);
				}
			}
		}
	}
	
}
