#include "SplashScreen.h"
#include "Game.h"
#include "TextureLoader.h"
#include "RenderObject.h"

/// <summary>
/// default constructor
/// </summary>
SplashScreen::SplashScreen()
{
	resetLevel();
}

/// <summary>
/// default deconstructor
/// </summary>
SplashScreen::~SplashScreen()
{
}



/// <summary>
/// resets all values to default as needed
/// </summary>
void SplashScreen::resetLevel()
{
	m_logo = std::make_shared<AnimatedSprite>(0.075f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\logo.png"));

	m_logo->addFrame(sf::IntRect(0, 0, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 1, 0, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 2, 0, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 0, 1200, 240));
	m_logo->addFrame(sf::IntRect(0, 240, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 1, 240, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 2, 240, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 240, 1200, 240));
	m_logo->addFrame(sf::IntRect(0, 480, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 1, 480, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 2, 480, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 480, 1200, 240));
	m_logo->addFrame(sf::IntRect(0, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 1, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 2, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));
	m_logo->addFrame(sf::IntRect(1200 * 3, 720, 1200, 240));

	RenderObject::getInstance().add(m_logo);

	m_logo->setOrigin(sf::Vector2f(m_logo->getGlobalBounds().width / 2.f, m_logo->getGlobalBounds().height / 2.f));
	m_logo->setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f));
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void SplashScreen::events(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type || sf::Event::KeyReleased == t_event.type) //user pressed a key
	{
		processKeys(t_event);
	}
	else
	{
		processMouse(t_event);
	}
}

/// !!!---Private function---!!!
/// <summary>
/// process any input from the user
/// </summary>
/// <param name="t_event">use this for the key press</param>
void SplashScreen::processKeys(sf::Event& t_event)
{
	Game::s_changeGameMode = true;
	Game::s_currentGameMode = GameModeClass::Menu;
}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void SplashScreen::update()
{
	m_logo->update();
	m_currentTime += Game::deltaTime;
	if (m_currentTime >= m_targetTime)
	{
		Game::s_changeGameMode = true;
		Game::s_currentGameMode = GameModeClass::Menu;
	}
}

/// <summary>
/// Process mouse inputs and actions
/// </summary>
void SplashScreen::processMouse(sf::Event& t_event)
{
	if(sf::Event::MouseMoved == t_event.type)
	{
		findMousePos(t_event);
	}
	else if (sf::Event::MouseButtonPressed == t_event.type)
	{
		//mouseButtonDown();
	}
	else if (sf::Event::MouseButtonReleased == t_event.type)
	{
		//mouseButtonUp();
	}
}

