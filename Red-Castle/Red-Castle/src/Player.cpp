#include "Player.h"
#include "Game.h"
#include "TextureLoader.h"
#include "RenderObject.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(sf::Vector2f t_position)
{
	// initialise body
	m_body = std::make_shared<AnimatedSprite>(1.f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\Slime.png"));
	m_body->addFrame(sf::IntRect(0, 0, 300, 300));
	m_body->setScale(sf::Vector2f(0.15f, 0.15f));
	RenderObject::getInstance().add(m_body);

	// set origin
	sf::Vector2f playerMidPos = sf::Vector2f(m_body->getLocalBounds().width / 2.f, m_body->getLocalBounds().height / 2.f);
	m_body->setOrigin(playerMidPos);

	// set player spawn
	m_body->setPosition(sf::Vector2f(250.f, 250.f));

	//initialise the input type (standard is keyboard for now)
	m_input = std::make_shared<KeyboardInput>();

	// initialise the camera
	m_followCam.setCameraType(CameraTracker::CameraType::Delayed_Follow);
}

void Player::update()
{
	// move player based on input type (can be used to set up controller input)
	sf::Vector2f playerMove = m_input->calculateDisplacement() * m_speed * Game::deltaTime;
	m_body->move(playerMove);

	// flip the character depending on movement
	if (playerMove.x > 0.f)
	{
		m_body->setScale(sf::Vector2f(-std::abs(m_body->getScale().x), m_body->getScale().y));
	}
	else if (playerMove.x < 0.f)
	{
		m_body->setScale(sf::Vector2f(std::abs(m_body->getScale().x), m_body->getScale().y));
	}

	// set camera to follow player position
	m_followCam.update(m_body->getPosition());
}
