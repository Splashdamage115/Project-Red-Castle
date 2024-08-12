#include "Bullet.h"
#include "simpleMaths.h"
#include "RenderObject.h"
#include "Game.h"
#include "ExplosiveManager.h"

Bullet::Bullet()
{
}

void Bullet::init(sf::Vector2f t_start, float t_angle, float t_bulletSpeed, std::shared_ptr<AnimatedSprite> t_body, int t_damage, float t_timeAlive, float t_explosiveRadius)
{
    explosiveRadius = t_explosiveRadius;

    lifeTime = t_timeAlive;

    active = true;

    damage = t_damage;

    body = t_body;
    RenderObject::getInstance().add(body);

    displacement = math::degreesToDisplacement(t_angle) * t_bulletSpeed;

    body->setRotation(t_angle + 90.f); // 90.f to compensate for the sprite
    body->setScale(sf::Vector2f(3.f, 3.f));
    body->setPosition(t_start);
   // body->setOrigin(sf::Vector2f(body->getGlobalBounds().width / 2.f , body->getGlobalBounds().height / 2.f) * 3.f);
}

void Bullet::update()
{
    if(active)
    {
        body->update();
        body->setPosition(body->getPosition() + (displacement * Game::deltaTime));
        lifeTime -= Game::deltaTime;
        if (lifeTime <= 0.f)
        {
            deactivate();
        }
    }
}

sf::Vector2f Bullet::getPos()
{
    return body->getPosition();
}

void Bullet::deactivate()
{
    if(explosiveRadius > 0.f)
        ExplosiveManager::getInstance().createNewExplosion(body->getPosition(), explosiveRadius);
    active = false;
    body->setActive(false);
    body->setPosition(sf::Vector2f(-100000.f, -100000.f));
}
