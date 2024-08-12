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
	float lifeTime{ 3.f };
	float explosiveRadius{ -1.f };

	Bullet();
	void init(sf::Vector2f t_start, float t_angle, float t_bulletSpeed, std::shared_ptr<AnimatedSprite> t_body, int t_damage, float t_timeAlive, float t_explosiveRadius = -1.f);
	void update();
	sf::Vector2f getPos();
	void deactivate();
};

#endif // !BULLET_H
