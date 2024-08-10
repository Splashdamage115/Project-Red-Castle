#ifndef BULLET_H
#define BULLET_H

#include "Library.h"
#include "AnimatedSprite.h"

struct Bullet
{
public:
	bool active{ false };
	std::shared_ptr<AnimatedSprite> body;
	sf::Vector2f displacement{ 0.f,0.f };
	int damage{ 1 };

	Bullet();
	void init(sf::Vector2f t_start, sf::Vector2f t_aim, float t_bulletSpeed, std::shared_ptr<AnimatedSprite> t_body, float t_spread, int t_damage);
	void update();
	sf::Vector2f getPos();
	void deactivate();
};

#endif // !BULLET_H
