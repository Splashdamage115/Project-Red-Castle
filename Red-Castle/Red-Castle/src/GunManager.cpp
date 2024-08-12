#include "GunManager.h"
#include "BulletManager.h"
#include "simpleMaths.h"
#include "SoundPlayer.h"
#include "Game.h"

GunManager::GunManager()
{
	equipNewGun(std::make_shared<BasicPistol>());
}

void GunManager::equipNewGun(std::shared_ptr<GunBasic> t_newGun)
{
	m_currentWeapon = t_newGun;
	m_shootCooldownMax = m_currentWeapon->cooldown();
	m_shootCooldownRemaining = m_shootCooldownMax;
}

void GunManager::setPositioning(sf::Vector2f& t_startLocation, sf::Vector2f& t_aim)
{
	m_position = t_startLocation;
	m_aim = t_aim;
}

void GunManager::update()
{
	// reduce shot cooldown
	if (m_shootCooldownRemaining > 0.f)
		m_shootCooldownRemaining -= Game::deltaTime;

	if(m_mouseDown)
	{
		if (m_currentWeapon->fullAuto())
		{
			if (m_shootCooldownRemaining <= 0.f)
			{
				m_shootCooldownRemaining = m_shootCooldownMax;
				sf::Vector2f displacement = math::displacement(m_position, m_aim);
				float spreadAngle = m_currentWeapon->spread();
				float moveAngle = math::displacementToDegrees(displacement);
				moveAngle += (rand() % static_cast<int>(spreadAngle)) - (spreadAngle / 2.f);

				int difference = m_currentWeapon->highDamage() - m_currentWeapon->lowDamage();
				int damage = (rand() % difference) + m_currentWeapon->lowDamage();

				int bulletSpread = m_currentWeapon->bulletSpread();

				// fire 1 bullet if 1 or less
				if (bulletSpread <= 1)
				{
					BulletManager::getInstance().initNewBullet(m_position, moveAngle, m_currentWeapon->bulletLife(), damage, m_currentWeapon->bulletSpeed(), m_currentWeapon->explosiveRadius());
				}
				else 
				{
					// amount of steps for shot
					float angleStep = spreadAngle / (bulletSpread - 1);

					// Fire bullets in a spread pattern
					for (int i = 0; i < bulletSpread; ++i) {
						// Calculate the angle for the current bullet
						float currentAngle = moveAngle - (spreadAngle / 2) + (i * angleStep);

						BulletManager::getInstance().initNewBullet(m_position, currentAngle, m_currentWeapon->bulletLife(), damage, m_currentWeapon->bulletSpeed(), m_currentWeapon->explosiveRadius());
					}
				}

				SoundPlayer::getInstance().playNewSound("ASSETS\\SOUNDS\\GunShot-Basic.wav");
			}
		}
	}
}

void GunManager::setMouse(bool t_newMouse) 
{ 
	m_mouseDown = t_newMouse;
	if(m_mouseDown == false)
	{
		if(!m_currentWeapon->fullAuto())
		{
			if (m_shootCooldownRemaining <= 0.f)
			{
				m_shootCooldownRemaining = m_shootCooldownMax;
				sf::Vector2f displacement = math::displacement(m_position, m_aim);
				float spreadAngle = m_currentWeapon->spread();
				float moveAngle = math::displacementToDegrees(displacement);
				moveAngle += (rand() % static_cast<int>(spreadAngle)) - (spreadAngle / 2.f);

				int difference = m_currentWeapon->highDamage() - m_currentWeapon->lowDamage();
				int damage = (rand() % difference) + m_currentWeapon->lowDamage();

				int bulletSpread = m_currentWeapon->bulletSpread();

				// fire 1 bullet if 1 or less
				if (bulletSpread <= 1)
				{
					BulletManager::getInstance().initNewBullet(m_position, moveAngle, m_currentWeapon->bulletLife(), damage, m_currentWeapon->bulletSpeed(), m_currentWeapon->explosiveRadius());
				}
				else
				{
					// amount of steps for shot
					float angleStep = spreadAngle / (bulletSpread - 1);

					// Fire bullets in a spread pattern
					for (int i = 0; i < bulletSpread; ++i) {
						// Calculate the angle for the current bullet
						float currentAngle = moveAngle - (spreadAngle / 2) + (i * angleStep);

						BulletManager::getInstance().initNewBullet(m_position, currentAngle, m_currentWeapon->bulletLife(), damage, m_currentWeapon->bulletSpeed(), m_currentWeapon->explosiveRadius());
					}
				}

				SoundPlayer::getInstance().playNewSound("ASSETS\\SOUNDS\\GunShot-Basic.wav");
			}
		}
	}
}
