#ifndef EXPLOSIVE_MANAGER_H
#define EXPLOSIVE_MANAGER_H

#include "Library.h"
#include "AnimatedSprite.h"
#include "RenderObject.h"
#include "TextureLoader.h"
#include "SoundPlayer.h"

struct ExplosiveRadius
{
    bool active{ false };
    sf::Vector2f center{ 0.f,0.f };
    float radius{ 0.f };
    std::shared_ptr<AnimatedSprite> body;
    float timeLeft{ 0.f };
    int damage{ 3 };

    void activateAnimation()
    {
        body = std::make_shared<AnimatedSprite>(0.1f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\FireCircle.png"));
        body->addFrame(sf::IntRect(0, 0, 500, 500));
        body->setOrigin(sf::Vector2f(body->getGlobalBounds().width / 2.f, body->getGlobalBounds().height / 2.f));
        RenderObject::getInstance().add(body);
        SoundPlayer::getInstance().playNewSound("ASSETS\\SOUNDS\\ExplosionSound.wav");
    }
};

class ExplosiveManager {
public:
    static ExplosiveManager& getInstance()
    {
        static ExplosiveManager instance;
        return instance;
    }

    // DELETE FUNCTIONS TO AVOID MORE INSTANCES
    ExplosiveManager(ExplosiveManager const&) = delete;
    void operator=(ExplosiveManager const&) = delete;

    void createNewExplosion(sf::Vector2f t_position, float t_radius) 
    {
        for (unsigned int i = 0; i < m_explosions.size(); i++)
        {
            if (!m_explosions.at(i).active)
            {
                m_explosions.at(i).activateAnimation();
                m_explosions.at(i).body->setPosition(t_position);
                m_explosions.at(i).radius = t_radius;
                m_explosions.at(i).body->setScale(sf::Vector2f(1.f / m_explosions.at(i).body->getGlobalBounds().width * t_radius, 1.f / m_explosions.at(i).body->getGlobalBounds().height * t_radius));
                m_explosions.at(i).active = true;
                m_explosions.at(i).center = t_position;
                m_explosions.at(i).timeLeft = 5.f;
                return;
            }
        }
        ExplosiveRadius newExplosion;
        newExplosion.activateAnimation();
        newExplosion.body->setPosition(t_position);
        newExplosion.radius = t_radius;
        newExplosion.body->setScale(sf::Vector2f(1.f / newExplosion.body->getGlobalBounds().width * t_radius, 1.f / newExplosion.body->getGlobalBounds().height * t_radius));
        newExplosion.active = true;
        newExplosion.center = t_position;
        newExplosion.timeLeft = 5.f;
        m_explosions.push_back(newExplosion);
    }

    void updateExplosions();

    std::vector<ExplosiveRadius>& getRadii() { return m_explosions; }

private:
    ExplosiveManager() {}

    std::vector<ExplosiveRadius> m_explosions;
};
#endif // !EXPLOSIVE_MANAGER_H