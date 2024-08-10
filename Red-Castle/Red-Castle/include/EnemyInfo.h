#ifndef ENEMY_INFO_H
#define ENEMY_INFO_H

#include "AnimatedSprite.h"
#include "TextureLoader.h"
#include "ExplosiveManager.h"

class EnemyInfo
{
public:
	virtual void getMoveFrames(std::shared_ptr<AnimatedSprite> t_body) = 0;
	virtual void getMeleeFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		// dont change frames here (in case of no melee attack)
	}
	virtual float getMeleeTime()
	{
		return -1.f;
	}
	virtual float getExpireTime()
	{
		return 0.f;
	}
	virtual float getExpireFadeTime()
	{
		return 0.f;
	}
	virtual void getShootFrames()
	{
		// dont change frames here (in case of no Shoot attack)
	}
	virtual float getMeleeRadius()
	{
		return -1.f; // for no melee characters
	}
	virtual float getShootRadius()
	{
		return -1.f;
	}
	virtual void getExpireFrames(std::shared_ptr<AnimatedSprite> t_body)
	{

	}
	virtual void getExpireFadeFrames(std::shared_ptr<AnimatedSprite> t_body)
	{

	}
};

class Barrel : public EnemyInfo
{
public:
	virtual void getMoveFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->addFrame(sf::IntRect(0, 0, 100, 100));
	}
	virtual void getExpireFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(0.125f);
		t_body->addFrame(sf::IntRect(100, 0, 100, 100));
		t_body->addFrame(sf::IntRect(200, 0, 100, 100));
		t_body->addFrame(sf::IntRect(300, 0, 100, 100));
	}
	virtual void getExpireFadeFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		ExplosiveManager::getInstance().createNewExplosion(t_body->getPosition(), 250.f);

		t_body->clearFrames();
		t_body->changeTiming(1.f);
		t_body->addFrame(sf::IntRect(400, 0, 100, 100));

	}
	virtual float getExpireTime()
	{
		return 0.375f;
	}
	virtual float getExpireFadeTime()
	{
		return 1.f;
	}
};

class Slime : public EnemyInfo
{
public:
	virtual void getMoveFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->addFrame(sf::IntRect(0, 0, 300, 300));
		t_body->addFrame(sf::IntRect(300, 0, 300, 300));
		t_body->addFrame(sf::IntRect(600, 0, 300, 300));
		t_body->addFrame(sf::IntRect(900, 0, 300, 300));
		t_body->addFrame(sf::IntRect(1200, 0, 300, 300));
		t_body->changeTiming(0.25f);
	}
	virtual void getMeleeFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(0.125f);
		t_body->addFrame(sf::IntRect(0, 300, 300, 300));
		t_body->addFrame(sf::IntRect(300, 300, 300, 300));
		t_body->addFrame(sf::IntRect(600, 300, 300, 300));
		t_body->addFrame(sf::IntRect(900, 300, 300, 300));
		t_body->addFrame(sf::IntRect(1200, 300, 300, 300));
	}
	virtual float getMeleeRadius()
	{
		return 50.f; // for no melee characters
	}
	virtual float getMeleeTime()
	{
		return 0.625f;
	}
	virtual void getExpireFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(0.125f);
		t_body->addFrame(sf::IntRect(0, 600, 300, 300));
		t_body->addFrame(sf::IntRect(300, 600, 300, 300));
		t_body->addFrame(sf::IntRect(600, 600, 300, 300));
		t_body->addFrame(sf::IntRect(900, 600, 300, 300));
		t_body->addFrame(sf::IntRect(1200, 600, 300, 300));
	}
	virtual void getExpireFadeFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(1.f);
		t_body->addFrame(sf::IntRect(0, 900, 300, 300));
		t_body->addFrame(sf::IntRect(300, 900, 300, 300));
		t_body->addFrame(sf::IntRect(600, 900, 300, 300));
		t_body->addFrame(sf::IntRect(900, 900, 300, 300));
		t_body->addFrame(sf::IntRect(1200, 900, 300, 300));
	}
	virtual float getExpireTime()
	{
		return 0.5f;
	}
	virtual float getExpireFadeTime()
	{
		return 4.f;
	}
};

class Goblin : public EnemyInfo
{
public:
	virtual void getMoveFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->addFrame(sf::IntRect(0, 0, 300, 300));
		t_body->addFrame(sf::IntRect(300, 0, 300, 300));
		t_body->addFrame(sf::IntRect(600, 0, 300, 300));
		t_body->addFrame(sf::IntRect(900, 0, 300, 300));
		t_body->addFrame(sf::IntRect(1200, 0, 300, 300));
		t_body->changeTiming(0.1f);
	}
	virtual void getMeleeFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(0.125f);
		t_body->addFrame(sf::IntRect(0, 300, 300, 300));
		t_body->addFrame(sf::IntRect(300, 300, 300, 300));
		t_body->addFrame(sf::IntRect(600, 300, 300, 300));
		t_body->addFrame(sf::IntRect(900, 300, 300, 300));
		t_body->addFrame(sf::IntRect(1200, 300, 300, 300));
		t_body->addFrame(sf::IntRect(0, 600, 300, 300));
	}
	virtual float getMeleeRadius()
	{
		return 70.f; // for no melee characters
	}
	virtual float getMeleeTime()
	{
		return 0.75f;
	}
	virtual void getExpireFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(0.125f);
		t_body->addFrame(sf::IntRect(0, 900, 300, 300));
		t_body->addFrame(sf::IntRect(300, 900, 300, 300));
		t_body->addFrame(sf::IntRect(600, 900, 300, 300));
		t_body->addFrame(sf::IntRect(900, 900, 300, 300));
		t_body->addFrame(sf::IntRect(1200, 900, 300, 300));
		t_body->addFrame(sf::IntRect(0   , 1200, 300, 300));
	}
	virtual void getExpireFadeFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(1.f);
		t_body->addFrame(sf::IntRect(0, 1500, 300, 300));
		t_body->addFrame(sf::IntRect(300, 1500, 300, 300));
		t_body->addFrame(sf::IntRect(600, 1500, 300, 300));
		t_body->addFrame(sf::IntRect(900, 1500, 300, 300));
		t_body->addFrame(sf::IntRect(1200, 1800, 300, 300));
	}
	virtual float getExpireTime()
	{
		return 0.5f;
	}
	virtual float getExpireFadeTime()
	{
		return 4.f;
	}
};

#endif // !ENEMY_INFO_H
