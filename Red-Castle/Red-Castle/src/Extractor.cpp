#include "Extractor.h"
#include "TextureLoader.h"
#include "RenderObject.h"
#include "simpleMaths.h"
#include "Game.h"

ExtractorCharacter::ExtractorCharacter() : m_weapon(false)
{
}

void ExtractorCharacter::init(sf::Vector2f t_position, bool t_roper)
{
	m_active = true;

	// initialise body
	m_body = std::make_shared<AnimatedSprite>(0.1f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\Extractor.png"));
	if (!t_roper)
	{
		m_body->addFrame(sf::IntRect(0, 0, 128, 256));
		m_body->addFrame(sf::IntRect(128 * 1, 0, 128, 256));
		m_body->addFrame(sf::IntRect(128 * 2, 0, 128, 256));
		m_body->addFrame(sf::IntRect(128 * 3, 0, 128, 256));
		m_body->addFrame(sf::IntRect(128 * 4, 0, 128, 256));

		m_weapon.equipNewGun(std::make_shared<BasicLMG>());
		m_weapon.setMouse(true);
	}
	else
	{
		m_body->addFrame(sf::IntRect(0, 256, 128, 256));
		m_body->addFrame(sf::IntRect(128 * 1, 256, 128, 256));
		m_body->addFrame(sf::IntRect(128 * 2, 256, 128, 256));
		m_body->addFrame(sf::IntRect(128 * 3, 256, 128, 256));
		m_body->addFrame(sf::IntRect(128 * 4, 256, 128, 256));
		m_roper = true;
	}

	m_body->setScale(sf::Vector2f(0.35f, 0.35f));
	RenderObject::getInstance().add(m_body);


	sf::Vector2f midPos = sf::Vector2f(m_body->getLocalBounds().width / 2.f, m_body->getLocalBounds().height / 2.f);
	m_body->setOrigin(midPos);

	// set player spawn
	m_body->setPosition(sf::Vector2f(250.f, 250.f));
}

void ExtractorCharacter::update(sf::Vector2f& t_playerPos, EnemyManager& t_enemyManager)
{
	if(m_active)
	{
		sf::Vector2f targetPos = t_playerPos;
		if(m_leaving)
			targetPos = sf::Vector2f(0.f, 0.f);

		if (m_leavingTime > 0.f)
		{
			m_leavingTime -= Game::deltaTime;

			if (m_leavingTime <= 0.f)
			{
				m_leaving = true;

				if (m_roper)
				{
					m_body->clearFrames();
					m_body->addFrame(sf::IntRect(0, 256, 128, 256));
					m_body->addFrame(sf::IntRect(128 * 1, 256, 128, 256));
					m_body->addFrame(sf::IntRect(128 * 2, 256, 128, 256));
					m_body->addFrame(sf::IntRect(128 * 3, 256, 128, 256));
					m_body->addFrame(sf::IntRect(128 * 4, 256, 128, 256));

					m_ropeLine = std::make_shared<sf::RectangleShape>(sf::Vector2f(math::distance(t_playerPos, m_body->getPosition()), 1.f));
					m_ropeLine->setRotation(math::displacementToDegrees(math::displacement(m_body->getPosition(), t_playerPos)));
					m_ropeLine->setFillColor(sf::Color(102, 57, 49));
					m_ropeLine->setPosition(m_body->getPosition());
					RenderObject::getInstance().add(m_ropeLine);
				}
			}
		}
		if(!m_roper)
		{
			std::vector<Enemy> enemies = t_enemyManager.getEnemies();

			if (!enemies.empty()) // Check if there are any enemies
			{
				size_t closestNum = 0;
				float closestDistance = math::distance(m_body->getPosition(), enemies.at(0).getPos());

				for (size_t i = 1; i < enemies.size(); i++)
				{
					if (!enemies.at(i).getAlive())
						continue;

					float currentDistance = math::distance(m_body->getPosition(), enemies.at(i).getPos());
					if (currentDistance < closestDistance)
					{
						closestNum = i;
						closestDistance = currentDistance;
					}
				}
				if (enemies.at(closestNum).getAlive())
				{
					m_weapon.setPositioning(m_body->getPosition(), enemies.at(closestNum).getPos());
					m_weapon.update();
					m_weapon.setGunToFull();
				}
				else
				{
					m_weapon.setPositioning(m_body->getPosition(), targetPos);
				}
			}
			else
			{
				m_weapon.setPositioning(m_body->getPosition(), targetPos);
			}
		}

		if (!math::positionInCircle(targetPos, 50.f, m_body->getPosition()))
		{
			if (m_roper && m_leaving)
			{
				m_ropeLine->setPosition(m_body->getPosition());
				m_ropeLine->setRotation(math::displacementToDegrees(math::displacement(m_body->getPosition(), t_playerPos)));
			}
			m_body->update();

			// move enemy towards player
			sf::Vector2f enemyMove = math::displacement(m_body->getPosition(), targetPos) * m_moveSpeed * Game::deltaTime;
			m_body->move(enemyMove);

			// flip the character depending on movement
			if (enemyMove.x > 0.f)
			{
				m_body->setScale(sf::Vector2f(-std::abs(m_body->getScale().x), m_body->getScale().y));
			}
			else if (enemyMove.x < 0.f)
			{
				m_body->setScale(sf::Vector2f(std::abs(m_body->getScale().x), m_body->getScale().y));
			}
		}
		else
		{
			if(!m_leaving)
			{
				if (m_roper && !m_grabbing)
				{
					m_body->clearFrames();
					m_body->addFrame(sf::IntRect(0, 512, 128, 256));
					m_body->addFrame(sf::IntRect(128 * 1, 512, 128, 256));
					m_body->addFrame(sf::IntRect(128 * 2, 512, 128, 256));
					m_grabbing = true;

					m_leavingTime = 3.f;
				}
				else if (m_roper)
				{
					m_body->update();
				}
				else if(m_leavingTime <= 0.f)
				{
					m_leavingTime = 3.f;
				}
			}
		}
	}
}
