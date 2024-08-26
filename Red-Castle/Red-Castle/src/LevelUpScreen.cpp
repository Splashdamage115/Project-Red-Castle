#include "LevelUpScreen.h"
#include "Game.h"
#include "RenderObject.h"
#include "BuffHolder.h"
#include "TextureLoader.h"
#include "GlobalFontStorage.h"

void LevelUpScreen::init()
{
	m_backgroundDarkness = std::make_shared<sf::RectangleShape>(sf::Vector2f(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)));
	m_backgroundDarkness->setFillColor(sf::Color(0, 0, 0, 0));
	RenderObject::getInstance().addHUD(m_backgroundDarkness);

	for (int i = 0; i < BUTTON_AMOUNT; i++)
	{
		m_buttons.push_back(Button());
		m_buttons.at(i).init(*TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\Level\\Button.png"), sf::Vector2i(320, 620), sf::Vector2f(200.f + (600.f * i), 250.f), 5, 0.8f);
		//m_buttons.at(i).init(m_buttonTexture, sf::Vector2i(256, 128), sf::Vector2f(100.f, 600.f + (150 * i)), 4, 0.5f);
	}
	m_animateTimeLeft = 0.5f;

	for (int i = 0; i < BUTTON_AMOUNT; i++)
	{
		std::shared_ptr <sf::Text> newName;
		newName = std::make_shared<sf::Text>();
		newName->setFont(*GlobalFontStorage::getInstance().getFont());
		newName->setCharacterSize(28u);
		newName->setOutlineColor(sf::Color::Black);
		newName->setOutlineThickness(1.f);
		newName->setPosition(sf::Vector2f(360.f + (600.f * i), 650.f));
		RenderObject::getInstance().addHUD(newName);
		m_names.push_back(newName);

		std::shared_ptr <sf::Text> newDescription;
		newDescription = std::make_shared<sf::Text>();
		newDescription->setFont(*GlobalFontStorage::getInstance().getFont());
		newDescription->setCharacterSize(16u);
		newDescription->setOutlineColor(sf::Color::Black);
		newDescription->setOutlineThickness(1.f);
		newDescription->setPosition(sf::Vector2f(360.f + (600.f * i), 750.f));
		RenderObject::getInstance().addHUD(newDescription);
		m_descriptions.push_back(newDescription);
	}

	initBuffs();
}

void LevelUpScreen::update()
{
	for (unsigned int i = 0; i < m_buttons.size(); i++)
		m_buttons.at(i).updateFrame();
	for (unsigned int i = 0; i < m_icons.size(); i++)
		m_icons.at(i)->update();

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
	if (m_closing)
		return;
	for (unsigned int i = 0; i < m_buttons.size(); i++)
		if(m_buttons.at(i).releaseButton())
		{ 
			BuffHolder::getInstance().initNew(m_buffs.at(i));

			m_closing = true;
			m_animateTimeLeft = 0.5f;
		}
}

bool LevelUpScreen::checkClosed()
{
	return m_closed;
}

void LevelUpScreen::initBuffs()
{
	for (int i = 0; i < BUTTON_AMOUNT; i++)
	{
		std::shared_ptr<Buff> newBuff;
		newBuff = std::make_shared<Buff>();
		newBuff->active = true;
		newBuff->applier = ApplicationType::Once;
		newBuff->applyLocation = AlertClassName::Player;
		newBuff->name = static_cast<BuffName>(rand() % BUFF_AMOUNT);
		std::shared_ptr<AnimatedSprite> newIcon;
		switch (newBuff->name)
		{
		case BuffName::PlayerSpeed:
			newBuff->increase = static_cast<float>(rand() % 10) + 5.f;
			m_names.at(i)->setString("Player Speed");
			m_descriptions.at(i)->setString("Increase the player\nSpeed by " + std::to_string(static_cast<int>(newBuff->increase)));

			m_names.at(i)->setOrigin(m_names.at(i)->getGlobalBounds().getSize() / 2.f);
			m_descriptions.at(i)->setOrigin(m_descriptions.at(i)->getGlobalBounds().getSize() / 2.f);

			newIcon = std::make_shared<AnimatedSprite>(0.2f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\Level\\Legs.png"));
			newIcon->addFrame(sf::IntRect(0, 0, 32, 32));
			newIcon->setScale(sf::Vector2f(4.f, 4.f));
			break;
		case BuffName::PlayerSpeedPercentage:
			newBuff->increase = static_cast<float>(rand() % 10) / 100.f + 1.05f;
			m_names.at(i)->setString("Player Speed");
			m_descriptions.at(i)->setString("Increase the player\nSpeed by " + std::to_string(static_cast<int>(newBuff->increase * 100.f - 100.f)) + "%");

			m_names.at(i)->setOrigin(m_names.at(i)->getGlobalBounds().getSize() / 2.f);
			m_descriptions.at(i)->setOrigin(m_descriptions.at(i)->getGlobalBounds().getSize() / 2.f);


			newIcon = std::make_shared<AnimatedSprite>(0.2f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\Level\\Legs.png"));
			newIcon->addFrame(sf::IntRect(0, 0, 32, 32));
			newIcon->setScale(sf::Vector2f(4.f, 4.f));
			break;
		case BuffName::PlayerHealth:
			newBuff->increase = static_cast<float>(rand() % 8) + 2.f;
			m_names.at(i)->setString("Player Health");
			m_descriptions.at(i)->setString("Increase the player\nHealth by " + std::to_string(static_cast<int>(newBuff->increase)));

			m_names.at(i)->setOrigin(m_names.at(i)->getGlobalBounds().getSize() / 2.f);
			m_descriptions.at(i)->setOrigin(m_descriptions.at(i)->getGlobalBounds().getSize() / 2.f);

			newIcon = std::make_shared<AnimatedSprite>(0.2f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\Level\\Heart.png"));
			newIcon->addFrame(sf::IntRect(0, 0, 32, 32));
			newIcon->addFrame(sf::IntRect(32, 0, 32, 32));
			newIcon->addFrame(sf::IntRect(64, 0, 32, 32));
			newIcon->addFrame(sf::IntRect(96, 0, 32, 32));
			newIcon->addFrame(sf::IntRect(128, 0, 32, 32));
			newIcon->setScale(sf::Vector2f(4.f, 4.f));
			break;
		case BuffName::PlayerHealthPercentage:
			newBuff->increase = static_cast<float>(rand() % 5) / 100.f + 1.1f;
			m_names.at(i)->setString("Player Health");
			m_descriptions.at(i)->setString("Increase the player\nHealth by " + std::to_string(static_cast<int>(newBuff->increase * 100.f - 100.f)) + "%");

			m_names.at(i)->setOrigin(m_names.at(i)->getGlobalBounds().getSize() / 2.f);
			m_descriptions.at(i)->setOrigin(m_descriptions.at(i)->getGlobalBounds().getSize() / 2.f);

			newIcon = std::make_shared<AnimatedSprite>(0.2f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\Level\\Heart.png"));
			newIcon->addFrame(sf::IntRect(0, 0, 32, 32));
			newIcon->addFrame(sf::IntRect(32, 0, 32, 32));
			newIcon->addFrame(sf::IntRect(64, 0, 32, 32));
			newIcon->addFrame(sf::IntRect(96, 0, 32, 32));
			newIcon->addFrame(sf::IntRect(128, 0, 32, 32));
			newIcon->setScale(sf::Vector2f(4.f, 4.f));
			break;
		default:
			newBuff->increase = 0.f;
			break;
		}
		if(newIcon != nullptr)
		{
			newIcon->setPosition(sf::Vector2f(360.f + (600.f * i) - newIcon->getGlobalBounds().width / 2.f, 400.f - newIcon->getGlobalBounds().height / 2.f));
			RenderObject::getInstance().addHUD(newIcon);
			m_icons.push_back(newIcon);
		}

		m_buffs.push_back(newBuff);
	}
}
