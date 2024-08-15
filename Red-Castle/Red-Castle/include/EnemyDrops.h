#ifndef ENEMY_DROPS_H
#define ENEMY_DROPS_H

#include "Library.h"
#include "AnimatedSprite.h"
#include "Player.h"

class DropBasic
{
public:
	virtual void initialiseType() = 0;
	void init(sf::Vector2f t_startPosition);

	void update(sf::Vector2f t_playerPosition);

	void checkRadiusCollision(sf::Vector2f t_playerPosition);

	virtual void checkCollidedWithPlayer(Player& t_player) = 0;

	bool getActive() { return m_active; }
private:
	bool m_tracing{ false };
	bool m_fall{ false };
	sf::Vector2f m_fallPosition{ 0.f,0.f };

protected:
	std::shared_ptr<AnimatedSprite> m_body;
	float m_collectRadius{ 100.f };
	float m_animateTime{ 1.f };
	bool m_active{ false };
};

class XPDrop : public DropBasic
{
public:
	virtual void initialiseType()override;
	virtual void checkCollidedWithPlayer(Player& t_player)override;
};

class CashDrop : public DropBasic
{
public:
	virtual void initialiseType()override;
	virtual void checkCollidedWithPlayer(Player& t_player)override;
};

class DropManager
{
public:
	static DropManager& getInstance()
	{
		static DropManager instance;
		return instance;
	}

	// DELETE FUNCTIONS TO AVOID MORE INSTANCES
	DropManager(DropManager const&) = delete;
	void operator=(DropManager const&) = delete;

	void initNewDrops(int t_amtOfDrops, sf::Vector2f t_position);
	void update(Player& t_player);
private:
	DropManager() {}
	std::vector<std::shared_ptr<DropBasic>> m_drops;
};

#endif // !ENEMY_DROPS_H