#include "LevelUpScreen.h"
#include "Game.h"
#include "RenderObject.h"
#include "BuffHolder.h"
#include "TextureLoader.h"

void LevelUpScreen::init()
{
	m_backgroundDarkness = std::make_shared<sf::RectangleShape>(sf::Vector2f(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)));

	m_backgroundDarkness->setFillColor(sf::Color(0, 0, 0, 0));

	RenderObject::getInstance().addHUD(m_backgroundDarkness);

	for (int i = 0; i < BUTTON_AMOUNT; i++)
	{
		m_buttons.push_back(Button());
		m_buttons.at(i).init(*TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\Level\\Button.png"), sf::Vector2i(176, 320), sf::Vector2f(600.f + (300.f * i), 450.f), 5, 0.8f);
		//m_buttons.at(i).init(m_buttonTexture, sf::Vector2i(256, 128), sf::Vector2f(100.f, 600.f + (150 * i)), 4, 0.5f);
	}

	m_animateTimeLeft = 0.5f;
}

void LevelUpScreen::update()
{
	for (unsigned int i = 0; i < m_buttons.size(); i++)
		m_buttons.at(i).updateFrame();

	if (m_closing)
	{
		m_animateTimeLeft -= Game::deltaTime;
		if (m_animateTimeLeft > 0.f)
		{
			float alphaFactor = m_animateTimeLeft / 0.5f;
			sf::Color color = m_backgroundDarkness->getFillColor();
			color.a = static_cast<int>(160 * alphaFactor);
			m_backgroundDarkness->setFillColor(color);
		}
		else
		{
			m_backgroundDarkness->setFillColor(sf::Color(0, 0, 0, 0));
			m_closed = true;
		}
	}
	else
	{
		m_animateTimeLeft -= Game::deltaTime;
		if (m_animateTimeLeft > 0.f)
		{
			float alphaFactor = (0.5f - m_animateTimeLeft) / 0.5f;
			sf::Color color = m_backgroundDarkness->getFillColor();
			color.a = static_cast<int>(160 * alphaFactor);
			m_backgroundDarkness->setFillColor(color);
		}
		else
		{
			m_backgroundDarkness->setFillColor(sf::Color(0, 0, 0, 160));
		}
	}
}

void LevelUpScreen::setMouse(sf::Vector2f& t_mousePos)
{
	m_mousePos = t_mousePos;

	if(!m_closing)
		for (unsigned int i = 0; i < m_buttons.size(); i++)
			m_buttons.at(i).checkBounds(m_mousePos);
}

void LevelUpScreen::mouseDown()
{
}

void LevelUpScreen::mouseUp()
{
	for (unsigned int i = 0; i < m_buttons.size(); i++)
		if(m_buttons.at(i).releaseButton())
		{ 
			// NOTE: ADD FUNCTION TO ADD BUFF HERE!
			m_closing = true;
			m_animateTimeLeft = 0.5f;
		}
}

bool LevelUpScreen::checkClosed()
{
	return m_closed;
}
