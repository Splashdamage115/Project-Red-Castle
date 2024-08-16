#include "GunManager.h"
#include "BulletManager.h"
#include "simpleMaths.h"
#include "SoundPlayer.h"
#include "Game.h"
#include "TextureLoader.h"
#include "RenderObject.h"
#include "Particles.h"
#include "GlobalFontStorage.h"

GunManager::GunManager(bool t_player)
{
	m_playerDisplay = t_player;
}

void GunManager::equipNewGun(std::shared_ptr<GunBasic> t_newGun)
{
	m_currentWeapon = t_newGun;
	m_shootCooldownMax = m_currentWeapon->cooldown();
	m_shootCooldownRemaining = m_shootCooldownMax;

	m_weaponBody = std::make_shared<AnimatedSprite>(1.f, *TextureLoader::getInstance().getTexture(m_currentWeapon->textureLocation()));
	m_currentWeapon->getAnimation(m_weaponBody);
	m_weaponBody->setPosition(m_position);
	RenderObject::getInstance().addParticles(m_weaponBody);

	m_magazineMax = m_currentWeapon->getMagazine();
	m_magazine = m_magazineMax;
	m_stockpileMax = m_currentWeapon->getStockpile();
	m_stockpile = m_stockpileMax;
	m_reloadTime = m_currentWeapon->reloadTime();

	if(m_playerDisplay)
	{
		m_magazineText = std::make_shared<sf::Text>();
		m_magazineText->setFont(*GlobalFontStorage::getInstance().getFont());
		m_magazineText->setCharacterSize(24u);
		m_magazineText->setString(std::to_string(m_magazine) + " / " + std::to_string(m_stockpile));
		m_magazineText->setPosition(30.f, 30.f);


		RenderObject::getInstance().addHUD(m_magazineText);
	}
}

void GunManager::setPositioning(sf::Vector2f& t_startLocation, sf::Vector2f& t_aim)
{
	if (!m_active)
		return;

	m_position = t_startLocation;
	m_aim = t_aim;

	sf::Vector2f displacement = math::displacement(m_position, m_aim);
	float moveAngle = math::displacementToDegrees(displacement);

	if (m_reloading)
		moveAngle = (m_shootCooldownRemaining) * 360.f + m_startReloadAngle;
	else
		m_startReloadAngle = moveAngle;

	m_weaponBody->setPosition(m_position);
	m_weaponBody->setRotation(moveAngle);
	
	sf::Vector2f originalScale = m_weaponBody->getScale();

	if (moveAngle >= 90.f && moveAngle <= 270.f)
		m_weaponBody->setScale(sf::Vector2f(originalScale.x, -std::abs(originalScale.y)));
	else
		m_weaponBody->setScale(sf::Vector2f(originalScale.x, std::abs(originalScale.y)));
}

void GunManager::update()
{
	if (!m_active)
		return;

	m_weaponBody->update();

	if(m_reloading && m_playerDisplay)
		m_magazineText->setString("RELOADING");

	// reduce shot cooldown
	if (m_shootCooldownRemaining > 0.f)
		m_shootCooldownRemaining -= Game::deltaTime;
	
	if (m_shootCooldownRemaining <= 0.f && m_reloading)
		reloadWeaponToMax();

	if(m_mouseDown)
	{
		if (m_currentWeapon->fullAuto())
		{
			if (m_shootCooldownRemaining <= 0.f)
			{
				if (m_magazine > 0)
				{
					spawnBullet();
				}
			}
		}
	}
}

void GunManager::setMouse(bool t_newMouse) 
{ 
	if(m_active)
	{
		m_mouseDown = t_newMouse;
		if (m_mouseDown == false)
		{
			if (!m_currentWeapon->fullAuto())
			{
				if (m_shootCooldownRemaining <= 0.f)
				{
					if (m_magazine > 0)
					{
						spawnBullet();
					}
				}
			}
		}
	}
}

void GunManager::reload()
{
	if(!m_reloading)
	{
		if (m_magazine < m_magazineMax && m_stockpile > 0)
		{
			m_shootCooldownRemaining = m_reloadTime;
			m_reloading = true;
			m_stockpile += m_magazine;
			m_magazine = 0;
		}
	}
}

void GunManager::reloadWeaponToMax()
{
	m_reloading = false;
	if(m_stockpile >= m_magazineMax)
	{
		m_magazine = m_magazineMax;
		m_stockpile -= m_magazineMax;
	}
	else
	{
		m_magazine = m_stockpile;
		m_stockpile = 0;
	}
	if(m_playerDisplay)
		m_magazineText->setString(std::to_string(m_magazine) + " / " + std::to_string(m_stockpile));
}

void GunManager::purchaseAmmoRefill()
{
	m_reloading = false;
	m_shootCooldownRemaining = 0.f;
	m_stockpile = m_stockpileMax;
	m_magazine = m_magazineMax;
	if(m_playerDisplay)
		m_magazineText->setString(std::to_string(m_magazine) + " / " + std::to_string(m_stockpile));
}

bool GunManager::refillWeapon()
{
	if (m_stockpile < m_stockpileMax)
	{
		m_stockpile = m_stockpileMax;
		return true;
	}
	return false;
}

void GunManager::setGunToFull()
{
	m_magazine = m_magazineMax;
}

void GunManager::deactivateWeapon()
{
	m_weaponBody = nullptr;
	m_active = false;
}

void GunManager::spawnBullet()
{
	if (!m_active)
		return;

	m_shootCooldownRemaining = m_shootCooldownMax; // reset shot cooldown
	m_magazine--; if(m_playerDisplay) m_magazineText->setString(std::to_string(m_magazine) + " / " + std::to_string(m_stockpile));

	// calculate the position of the bullets spawn, making them spawn at the end of the barrel
	sf::Vector2f displacement = math::displacement(m_position, m_aim);
	sf::Vector2f offsetPosition = m_weaponBody->getPosition();
	offsetPosition += displacement * (m_weaponBody->getGlobalBounds().width - m_weaponBody->getOrigin().x);

	float spreadAngle = m_currentWeapon->spread(); // current weapon spread
	float moveAngle = math::displacementToDegrees(displacement);
	moveAngle += (rand() % static_cast<int>(spreadAngle)) - (spreadAngle / 2.f); // make the weapon spread random

	// calculate the weapon damage based highDamage, and LowDamage
	int difference = m_currentWeapon->highDamage() - m_currentWeapon->lowDamage();
	int damage = (rand() % difference) + m_currentWeapon->lowDamage();

	// amount of bullets that are shot (for shotguns and similar)
	int bulletSpread = m_currentWeapon->bulletSpread();

	// fire 1 bullet if 1 or less
	if (bulletSpread <= 1)
	{
		BulletManager::getInstance().initNewBullet(offsetPosition, moveAngle, m_currentWeapon->bulletLife(), damage, m_currentWeapon->bulletSpeed(), m_currentWeapon->explosiveRadius());
	}
	else
	{
		// send bullets at a spaced interval across the "spread vector"
		float angleStep = spreadAngle / (bulletSpread - 1);
		for (int i = 0; i < bulletSpread; ++i) {
			float currentAngle = moveAngle - (spreadAngle / 2) + (i * angleStep);
			BulletManager::getInstance().initNewBullet(offsetPosition, currentAngle, m_currentWeapon->bulletLife(), damage, m_currentWeapon->bulletSpeed(), m_currentWeapon->explosiveRadius());
		}
	}

	ParticleSystem::getInstance().spawnNewParticle(10.f, offsetPosition + (displacement * 9.f), sf::Vector2f(0.f, 0.f), 0.f, 0.1f, sf::Color::Yellow);

	SoundPlayer::getInstance().playNewSound("ASSETS\\SOUNDS\\GunShot-Basic.wav");

	if (m_magazine <= 0)
	{
		reload();
	}
}
