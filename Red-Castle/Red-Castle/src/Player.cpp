#include "Player.h"
#include "Game.h"
#include "TextureLoader.h"
#include "RenderObject.h"
#include "GlobalFontStorage.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(sf::Vector2f t_position)
{
	m_active = true;

	// initialise body
	m_body = std::make_shared<AnimatedSprite>(0.1f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\Player.png"));
	m_body->addFrame(sf::IntRect(0, 0, 186, 291));
	m_body->addFrame(sf::IntRect(186 * 1, 0, 186, 291));
	m_body->addFrame(sf::IntRect(186 * 2, 0, 186, 291));
	m_body->addFrame(sf::IntRect(186 * 3, 0, 186, 291));
	m_body->addFrame(sf::IntRect(186 * 4, 0, 186, 291));
	m_body->addFrame(sf::IntRect(186 * 5, 0, 186, 291));
	m_body->addFrame(sf::IntRect(186 * 6, 0, 186, 291));
	m_body->setScale(sf::Vector2f(0.25f, 0.25f));
	RenderObject::getInstance().add(m_body);

	// initialise XP amt
	m_xpText = std::make_shared<sf::Text>();
	m_xpText->setFont(*GlobalFontStorage::getInstance().getFont());
	m_xpText->setCharacterSize(24u);
	m_xpText->setString(std::to_string(m_xpLvl));
	m_xpText->setPosition(sf::Vector2f(0.f, 30.f));

	RenderObject::getInstance().addHUD(m_xpText);

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
	if(m_active)
	{
		m_equippedWeapon.update();
		// move player based on input type (can be used to set up controller input)
		sf::Vector2f playerMove = m_input->calculateDisplacement() * m_speed * Game::deltaTime;
		m_body->move(playerMove);

		// update player animation frames
		if (playerMove.x != 0.f || playerMove.y != 0.f)
			m_body->update();

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
}

void Player::buttonReleased(sf::Keyboard::Key t_keyReleased)
{
	if (t_keyReleased == sf::Keyboard::R)
	{
		m_equippedWeapon.reload();
	}
}

void Player::recieveXp(int t_xpAmt)
{
	m_xpLvl += t_xpAmt;
	m_xpText->setString(std::to_string(m_xpLvl));
}
