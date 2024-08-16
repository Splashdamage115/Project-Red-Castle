#include "ExtractManager.h"
#include "RenderObject.h"
#include "Game.h"

void ExtractManager::checkExtract(Player& t_player, EnemyManager& t_enemyManager)
{
	if (m_fadeLast)
	{
		m_fadeTime -= Game::deltaTime;
		if (m_fadeTime > 0.f)
		{
			float alphaFactor = (3.f - m_fadeTime) / 3.f;
			sf::Color color = m_fadeSquare->getFillColor();
			color.a = static_cast<int>(255 * alphaFactor);
			m_fadeSquare->setFillColor(color);
		}
		else
		{
			m_fadeSquare->setFillColor(sf::Color(0, 0, 0, 255));
		}
		m_extractors.at(0).update(t_player.getPos() - sf::Vector2f(100.f, 30.f), t_enemyManager);
		m_extractors.at(1).update(t_player.getPos() - sf::Vector2f(100.f, -30.f), t_enemyManager);
		m_extractors.at(2).update(t_player.getPos() - sf::Vector2f(10.f, 0.f), t_enemyManager);

		t_player.followPosition(m_extractors.at(2).getFollowPos());
		return;
	}
	if (!t_player.getAlive() && !m_dying)
	{
		m_dying = true;

		m_fadeSquare = std::make_shared<sf::RectangleShape>(sf::Vector2f(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)));
		m_fadeSquare->setFillColor(sf::Color(0, 0, 0, 0));
		RenderObject::getInstance().addHUD(m_fadeSquare);

		m_fadeTime = 3.f;
	}
	if (m_dying)
	{

		m_fadeTime -= Game::deltaTime;

		if (m_fadeTime > 0.f)
		{
			float alphaFactor = (3.f - m_fadeTime) / 3.f;
			sf::Color color = m_fadeSquare->getFillColor();
			color.a = static_cast<int>(255 * alphaFactor);
			m_fadeSquare->setFillColor(color);
		}
		else
		{
			m_fadeSquare->setFillColor(sf::Color(0, 0, 0, 255));

			if (!m_leave)
			{
				m_extractors.emplace_back();
				m_extractors.emplace_back();
				m_extractors.emplace_back();

				m_extractors.at(0).init(sf::Vector2f(0.f, 0.f), false);
				m_extractors.at(1).init(sf::Vector2f(0.f, 100.f), false);
				m_extractors.at(2).init(sf::Vector2f(-80.f, 50.f), true);

				m_wait = 2.f;
				m_leave = true;
			}
		}

		if (m_leave)
		{
			if (m_wait > 0.f)
			{
				m_wait -= Game::deltaTime;
				if (m_wait <= 0.f)
				{
					m_fadeTime = 3.f;
				}
			}
			else
			{
				m_fadeTime -= Game::deltaTime;

				float alphaFactor = m_fadeTime / 3.f;
				sf::Color color = m_fadeSquare->getFillColor();
				color.a = static_cast<int>(255 * alphaFactor);
				m_fadeSquare->setFillColor(color);

			}
			m_extractors.at(0).update(t_player.getPos() - sf::Vector2f(100.f, 30.f), t_enemyManager);
			m_extractors.at(1).update(t_player.getPos() - sf::Vector2f(100.f, -30.f), t_enemyManager);
			m_extractors.at(2).update(t_player.getPos() - sf::Vector2f(10.f, 0.f), t_enemyManager);

			if (m_extractors.at(2).getLeaving())
			{
				t_player.followPosition(m_extractors.at(2).getFollowPos());
				m_fadeLast = true;
				m_fadeTime = 3.f;
			}
		}
	}
}
