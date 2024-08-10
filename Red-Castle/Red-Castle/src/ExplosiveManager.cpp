#include "ExplosiveManager.h"
#include "Game.h"

void ExplosiveManager::updateExplosions()
{
    for (unsigned int i = 0; i < m_explosions.size(); i++)
    {
        if (!m_explosions.at(i).active)
            continue;

        m_explosions.at(i).body->update();
        m_explosions.at(i).timeLeft -= Game::deltaTime;
        if (m_explosions.at(i).timeLeft <= 0.f)
        {
            m_explosions.at(i).active = false;
            m_explosions.at(i).body = nullptr;
        }
    }
}
