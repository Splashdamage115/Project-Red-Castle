#include "EnemyDrops.h"
#include "simpleMaths.h"
#include "Game.h"
#include "TextureLoader.h"
#include "RenderObject.h"



// **********************************************************************
//						BASIC
// **********************************************************************
void DropBasic::init(sf::Vector2f t_startPosition)
{
	if (m_body != nullptr)
	{
		m_body->setPosition(t_startPosition);

		m_fallPosition = t_startPosition + sf::Vector2f(static_cast<float>(rand() % 200) - 100.f, static_cast<float>(rand() % 200) - 100.f);
		m_fall = true;

		m_active = true;

		m_body->jumpToRandomFrame();
	}
}

void DropBasic::update(sf::Vector2f t_playerPosition)
{
	m_body->update();
	if (m_animateTime > 0.f)
	{
		m_animateTime -= Game::deltaTime;

		if (m_fall)
		{
			m_body->move(math::displacement(m_body->getPosition(), m_fallPosition) * 400.f * Game::deltaTime);

			if (math::positionInCircle(m_fallPosition, 5.f, m_body->getPosition()))
			{
				m_animateTime = 0.f;
				m_fall = false;
			}
				
		}
	}
	else if (!m_tracing)
		checkRadiusCollision(t_playerPosition);
	else
	{
		m_body->move(math::displacement(m_body->getPosition(), t_playerPosition) * 200.f * Game::deltaTime);
	}
}

void DropBasic::checkRadiusCollision(sf::Vector2f t_playerPosition)
{
	if (math::positionInCircle(m_body->getPosition(), m_collectRadius, t_playerPosition))
	{
		m_tracing = true;
	}
}






// **********************************************************************
//						XP
// **********************************************************************
void XPDrop::initialiseType()
{
	m_body = std::make_shared<AnimatedSprite>(0.125f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\xpOrb.png"));

	m_body->addFrame(sf::IntRect(0, 0, 32, 48));
	m_body->addFrame(sf::IntRect(32, 0, 32, 48));
	m_body->addFrame(sf::IntRect(64, 0, 32, 48));
	m_body->addFrame(sf::IntRect(96, 0, 32, 48));
	m_body->addFrame(sf::IntRect(128, 0, 32, 48));
	m_body->addFrame(sf::IntRect(160, 0, 32, 48));
	m_body->addFrame(sf::IntRect(192, 0, 32, 48));

	m_body->setScale(sf::Vector2f(0.5f, 0.5f));

	RenderObject::getInstance().addParticles(m_body);
}

void XPDrop::checkCollidedWithPlayer(Player& t_player)
{
	if (m_body->getGlobalBounds().intersects(t_player.getBounds()))
	{
		t_player.recieveXp(1);

		// deactivate
		m_active = false;
		m_body->setActive(false);
		m_body = nullptr;
	}
}




// **********************************************************************
//						Cash
// **********************************************************************
void CashDrop::initialiseType()
{
	m_body = std::make_shared<AnimatedSprite>(0.125f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\Coin.png"));

	m_body->addFrame(sf::IntRect(0, 0, 32, 40));
	m_body->addFrame(sf::IntRect(32, 0, 32, 40));
	m_body->addFrame(sf::IntRect(64, 0, 32, 40));
	m_body->addFrame(sf::IntRect(96, 0, 32, 40));
	m_body->addFrame(sf::IntRect(128, 0, 32, 40));
	m_body->addFrame(sf::IntRect(160, 0, 32, 40));
	m_body->addFrame(sf::IntRect(192, 0, 32, 40));
	m_body->addFrame(sf::IntRect(224, 0, 32, 40));

	m_body->setScale(sf::Vector2f(0.5f, 0.5f));

	RenderObject::getInstance().addParticles(m_body);
}

void CashDrop::checkCollidedWithPlayer(Player& t_player)
{
	if (m_body->getGlobalBounds().intersects(t_player.getBounds()))
	{
		t_player.recieveCash(1);

		// deactivate
		m_active = false;
		m_body->setActive(false);
		m_body = nullptr;
	}
}




// **********************************************************************
//						Drop manager
// **********************************************************************

void DropManager::initNewDrops(int t_amtOfDrops, sf::Vector2f t_position)
{
	for (int i = 0; i < t_amtOfDrops; i++)
	{

		int randType = rand() % 10;
		std::shared_ptr<DropBasic> newDrop;
		if (randType == 0)
			newDrop = std::make_shared<XPDrop>();
		if (randType == 9)
			newDrop = std::make_shared<CashDrop>();
		else
			newDrop = std::make_shared<XPDrop>();

		newDrop->initialiseType();
		newDrop->init(t_position);

		for (unsigned int i = 0; i < m_drops.size(); i++)
		{
			if(!m_drops.at(i)->getActive())
			{
				m_drops.at(i) = newDrop;
				continue;
			}
		}

		if (m_drops.size() > 400)
		{
			m_drops.at(rand() % static_cast<int>(m_drops.size())) = newDrop;
			continue;
		}
		m_drops.push_back(newDrop);
	}
}

void DropManager::update(Player& t_player)
{
	for (unsigned int i = 0; i < m_drops.size(); i++)
	{
		if (!m_drops.at(i)->getActive())
			continue;

		m_drops.at(i)->update(t_player.getPos());
		m_drops.at(i)->checkCollidedWithPlayer(t_player);
	}
}

