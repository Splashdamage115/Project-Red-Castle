#ifndef BULLET_H
#define BULLET_H

#include "Library.h"
#include "AnimatedSprite.h"

struct Bullet
{
public:
	bool active;
	std::shared_ptr<AnimatedSprite> body;
	sf::Vector2f displacement;
	int damage{ 1 };

	Bullet();
	void init(sf::Vector2f t_start, sf::Vector2f t_aim, float t_bulletSpeed, std::shared_ptr<AnimatedSprite> t_body, float t_spread);
	void update();
	sf::Vector2f getPos();
	void deactivate();
};

#endif // !BULLET_H
