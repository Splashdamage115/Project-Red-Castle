#include "Bullet.h"
#include "simpleMaths.h"
#include "RenderObject.h"
#include "Game.h"

Bullet::Bullet()
{
}

void Bullet::init(sf::Vector2f t_start, sf::Vector2f t_aim, float t_bulletSpeed, std::shared_ptr<AnimatedSprite> t_body, float t_spread)
{
    active = true;

    body = t_body;
    RenderObject::getInstance().add(body);

    displacement = math::displacement(t_start, t_aim);

    float moveAngle = math::displacementToDegrees(displacement);
    moveAngle += (rand() % static_cast<int>(t_spread)) - (t_spread / 2.f);

    displacement = math::degreesToDisplacement(moveAngle) * t_bulletSpeed;

    body->setRotation(moveAngle + 90.f); // 90.f to compensate for the sprite
    body->setScale(sf::Vector2f(3.f, 3.f));
    body->setPosition(t_start);
}

void Bullet::update()
{
    if(active)
    {
        body->update();
        body->setPosition(body->getPosition() + (displacement * Game::deltaTime));
    }
}

sf::Vector2f Bullet::getPos()
{
    return body->getPosition();
}

void Bullet::deactivate()
{
    active = false;
    body->setActive(false);
    body->setPosition(sf::Vector2f(-100000.f, -100000.f));
}
