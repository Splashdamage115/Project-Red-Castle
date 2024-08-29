#include "BulletManager.h"
#include "TextureLoader.h"


BulletManager::BulletManager()
{
}

// implement spread here somehow
void BulletManager::initNewBullet(sf::Vector2f t_pawnPos, float t_angle, float t_timeAlive, int t_damage, float t_speed, float t_explosiveRadius)
{
	float moveSpeed = t_speed;

	std::shared_ptr<AnimatedSprite> bulletSprite;
	
	// sort out what sprite is required by the gun here
	bulletSprite = std::make_shared<AnimatedSprite>(0.1f, *TextureLoader::getInstance().getTexture(".\\ASSETS\\IMAGES\\Misc\\BulletAnimBasic.png"));
	// frames for the bullet animation
	bulletSprite->addFrame(sf::IntRect(0, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(16, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(32, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(48, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(64, 0, 16, 16));

	for(auto& i : m_bullets)
		if (!i.active)
		{
			i.init(t_pawnPos, t_angle, moveSpeed, bulletSprite, t_damage, t_timeAlive, t_explosiveRadius);
			return;
		}

	Bullet newBullet;
	newBullet.init(t_pawnPos, t_angle, moveSpeed, bulletSprite, t_damage, t_timeAlive, t_explosiveRadius);
	m_bullets.push_back(newBullet);
}

void BulletManager::initNewEnemyBullet(sf::Vector2f t_pawnPos, float t_angle, float t_timeAlive, int t_damage, float t_speed, float t_explosiveRadius)
{
	float moveSpeed = t_speed;

	std::shared_ptr<AnimatedSprite> bulletSprite;

	// sort out what sprite is required by the gun here
	bulletSprite = std::make_shared<AnimatedSprite>(0.1f, *TextureLoader::getInstance().getTexture(".\\ASSETS\\IMAGES\\Misc\\BulletAnimBasic.png"));
	// frames for the bullet animation
	bulletSprite->addFrame(sf::IntRect(0, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(16, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(32, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(48, 0, 16, 16));
	bulletSprite->addFrame(sf::IntRect(64, 0, 16, 16));

	for (auto& i : m_bulletsEnemy)
		if (!i.active)
		{
			i.init(t_pawnPos, t_angle, moveSpeed, bulletSprite, t_damage, t_timeAlive, t_explosiveRadius);
			return;
		}

	Bullet newBullet;
	newBullet.init(t_pawnPos, t_angle, moveSpeed, bulletSprite, t_damage, t_timeAlive, t_explosiveRadius);
	m_bulletsEnemy.push_back(newBullet);
}

void BulletManager::updateBullets()
{
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.at(i).update();
	}
	for (unsigned int i = 0; i < m_bulletsEnemy.size(); i++)
	{
		m_bulletsEnemy.at(i).update();
	}
}

void BulletManager::checkWallCollisions(std::vector<std::shared_ptr<sf::RectangleShape>>& t_walls)
{
	for (unsigned int i = 0; i < m_bullets.size(); i++)
	{
		for (unsigned int j = 0; j < t_walls.size(); j++)
		{
			if (m_bullets.at(i).body->getGlobalBounds().intersects(t_walls.at(j)->getGlobalBounds()))
			{
				m_bullets.at(i).deactivate();
				break;
			}
		}
	}
}
