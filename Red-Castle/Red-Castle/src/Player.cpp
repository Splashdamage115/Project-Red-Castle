#include "Player.h"
#include "Game.h"
#include "TextureLoader.h"
#include "RenderObject.h"
#include "GlobalFontStorage.h"
#include "ExplosiveManager.h"
#include "CollisionDetector.h"

Player::Player() : m_equippedWeapon(true)
{
}

Player::~Player()
{
}

void Player::init(sf::Vector2f t_position)
{
	m_equippedWeapon.equipNewGun(std::make_shared<BasicAssault>());

	m_active = true;
	m_alive = true;

	m_healthMax = 10;
	m_health = m_healthMax;

	// initialise body
	m_body = std::make_shared<AnimatedSprite>(0.1f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\Player.png"));
	m_body->addFrame(sf::IntRect(0, 0, 147, 246));
	m_body->addFrame(sf::IntRect(147 * 1, 0, 147, 246));
	m_body->addFrame(sf::IntRect(147 * 2, 0, 147, 246));
	m_body->addFrame(sf::IntRect(147 * 3, 0, 147, 246));
	m_body->addFrame(sf::IntRect(147 * 4, 0, 147, 246));
	m_body->addFrame(sf::IntRect(147 * 5, 0, 147, 246));
	m_body->addFrame(sf::IntRect(147 * 6, 0, 147, 246));
	m_body->setScale(sf::Vector2f(0.25f, 0.25f));


	m_shadow = std::make_shared<AnimatedSprite>(1.f, *TextureLoader::getInstance().getTexture("ASSETS\\IMAGES\\MISC\\shadowPlayer.png"));
	m_shadow->addFrame(sf::IntRect(0, 0, 64, 16));
	m_shadow->setOrigin(sf::Vector2f(
		((65.f) - m_shadow->getGlobalBounds().width / 2.f),
		((-15.f) - m_shadow->getGlobalBounds().height / 2.f)
	));
	m_shadow->setPosition(m_body->getPosition());
	RenderObject::getInstance().addPlayer(m_shadow);



	RenderObject::getInstance().addPlayer(m_body);

	// initialise XP amt
	m_xpText = std::make_shared<sf::Text>();
	m_xpText->setFont(*GlobalFontStorage::getInstance().getFont());
	m_xpText->setCharacterSize(24u);
	m_xpText->setString(std::to_string(m_xpLvl) + "xp");
	m_xpText->setPosition(sf::Vector2f(30.f, 120.f));

	RenderObject::getInstance().addHUD(m_xpText);
	
		// initialise XP amt
	m_weaponName = std::make_shared<sf::Text>();
	m_weaponName->setFont(*GlobalFontStorage::getInstance().getFont());
	m_weaponName->setCharacterSize(24u);
	m_weaponName->setString(m_equippedWeapon.getWeaponTypeName());
	m_weaponName->setPosition(sf::Vector2f(30.f, 0.f));

	RenderObject::getInstance().addHUD(m_weaponName);
	

	m_hp = std::make_shared<sf::Text>();
	m_hp->setFont(*GlobalFontStorage::getInstance().getFont());
	m_hp->setCharacterSize(24u);
	m_hp->setString(std::to_string(m_health));
	m_hp->setPosition(sf::Vector2f(30.f, 300.f));

	RenderObject::getInstance().addHUD(m_hp);


	m_cashText = std::make_shared<sf::Text>();
	m_cashText->setFont(*GlobalFontStorage::getInstance().getFont());
	m_cashText->setCharacterSize(24u);
	m_cashText->setString("$" + std::to_string(m_cashAmt));
	m_cashText->setPosition(sf::Vector2f(30.f, 90.f));

	RenderObject::getInstance().addHUD(m_cashText);

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
	if (m_deadTimer > 0.f)
	{
		m_deadTimer -= Game::deltaTime;

		if (m_deadTimer <= 2.f)
		{
			m_body->clearFrames();
			m_body->addFrame(sf::IntRect(240 * 2 + 256 + 273, 272, 240, 284));
		}

		if (m_deadTimer <= 0.f)
		{
			m_active = false;
		}
	}
	else if(m_active)
	{
		if (m_invincibilityTime > 0.f)
		{
			m_invincibilityTime -= Game::deltaTime;

			if(m_invincibilityTime <= 0.f)
				m_hp->setFillColor(sf::Color::White);
		}
		else
		{
			std::vector<ExplosiveRadius> e = ExplosiveManager::getInstance().getRadii();
			sf::Vector2f pos = m_body->getPosition();
			for (auto& i : e)
			{
				if (i.active)
				{
					if (math::circleIntersects(pos, i.center, 30.f, i.radius))
					{
						if(CollisionDetector::pixelPerfectTest(m_body->getSprite(), i.body->getSprite()))
						{
							applyDamage(1);
							break;
						}
					}
				}
			}
		}
		

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

		m_shadow->setPosition(m_body->getPosition());

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

void Player::setAimVector(sf::Vector2f& t_aimToFollow) 
{ 
	if (m_deadTimer <= 0.f)
		m_equippedWeapon.setPositioning(m_body->getPosition() + sf::Vector2f(5.f, 10.f), t_aimToFollow);
	else
		m_equippedWeapon.deactivateWeapon();
}

void Player::recieveXp(int t_xpAmt)
{
	m_xpLvl += t_xpAmt;
	m_xpText->setString(std::to_string(m_xpLvl) + "xp");
}

/// <summary>
/// check if the player has enough money
/// </summary>
/// <param name="t_price">price of the product</param>
/// <returns>if the purchase was succesful or not</returns>
bool Player::tryPurchase(int t_price)
{
	if (m_cashAmt >= t_price)
	{
		m_cashAmt -= t_price;
		m_cashText->setString("$" + std::to_string(m_cashAmt));
		return true;
	}
	return false;
}

/// <summary>
/// Same Weapon Type returns true 
/// </summary>
/// <param name="t_newGun"></param>
/// <returns></returns>
bool Player::tryRefillAmmo(std::shared_ptr<GunBasic> t_newGun)
{
	if (t_newGun->name() == m_equippedWeapon.getWeaponTypeName())
	{
		if (tryPurchase(m_equippedWeapon.getAmmoPrice()))
		{
			m_equippedWeapon.purchaseAmmoRefill();
			return true;
		}
	}
	return false;
}

void Player::recieveCash(int t_amtRecieved)
{
	m_cashAmt += t_amtRecieved;
	m_cashText->setString("$" + std::to_string(m_cashAmt));
}

void Player::applyDamage(int t_damageAmt)
{
	if(m_invincibilityTime <= 0.f)
	{
		m_health -= t_damageAmt;
		m_invincibilityTime = 0.5f;
		m_hp->setFillColor(sf::Color::Red);
		m_hp->setString(std::to_string(m_health));

		if (m_health <= 0)
		{
			expire();
		}
	}
}

void Player::followPosition(sf::Vector2f t_pos)
{
	sf::Vector2f move = math::displacement(m_body->getPosition(), t_pos) * 100.f * Game::deltaTime;
	m_body->move(move);

	m_shadow->setPosition(m_body->getPosition());

	m_followCam.update(m_body->getPosition());
}

void Player::expire()
{
	m_alive = false;
	m_deadTimer = 3.f;
	m_body->clearFrames();
	m_body->addFrame(sf::IntRect(0, 272, 240, 284));
	m_body->addFrame(sf::IntRect(240 * 1, 272, 273, 260));
	m_body->addFrame(sf::IntRect(240 * 2, 272, 256, 284));
	m_body->addFrame(sf::IntRect(240 * 2 + 256, 272, 273, 260));
	m_body->addFrame(sf::IntRect(240 * 2 + 256 + 273, 272, 240, 284));
	m_body->addFrame(sf::IntRect(240 * 2 + 256 + 273, 272, 240, 284));
	m_body->addFrame(sf::IntRect(240 * 2 + 256 + 273, 272, 240, 284));
	m_body->addFrame(sf::IntRect(240 * 2 + 256 + 273, 272, 240, 284));
	m_body->addFrame(sf::IntRect(240 * 2 + 256 + 273, 272, 240, 284));
	m_body->addFrame(sf::IntRect(240 * 2 + 256 + 273, 272, 240, 284));
	m_body->addFrame(sf::IntRect(240 * 2 + 256 + 273, 272, 240, 284));
}

void Player::refillHealth()
{
	m_health = m_healthMax;
	m_hp->setString(std::to_string(m_health));
}
