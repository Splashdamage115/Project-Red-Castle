#ifndef ENEMY_INFO_H
#define ENEMY_INFO_H

#include "AnimatedSprite.h"
#include "TextureLoader.h"

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
	virtual void getShootFrames(std::shared_ptr<AnimatedSprite> t_body)
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
};

class Barrel : public EnemyInfo
{
public:
	virtual void getMoveFrames(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->addFrame(sf::IntRect(0, 0, 40, 63));
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
};

#endif // !ENEMY_INFO_H
