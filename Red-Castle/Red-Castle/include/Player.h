#ifndef PLAYER_H
#define PLAYER_H

#include "Library.h"
#include "AnimatedSprite.h"
#include "InputSwitcher.hpp"
#include "cameraTracker.h"
#include "GunManager.h"

class PlayerBuffInterpretter;
class LevelUpHandler;

class Player
{
friend class PlayerBuffInterpretter;
friend class LevelUpHandler;
public:
	Player();
	~Player();
	void init(sf::Vector2f t_position); // initialise the player to the passed position

	void update();
	
	inline sf::Vector2f getPos() { return m_body->getPosition(); } // return the players position

	void setMouse(bool t_) { m_mouseDown = t_; m_equippedWeapon.setMouse(t_); }
	void buttonReleased(sf::Keyboard::Key t_keyReleased);
	void buyNewGun(std::shared_ptr<GunBasic> t_newGun) { m_equippedWeapon.equipNewGun(t_newGun); m_weaponName->setString(m_equippedWeapon.getWeaponTypeName());}

	void setAimVector(sf::Vector2f& t_aimToFollow);
	sf::FloatRect getBounds() { return m_body->getGlobalBounds(); }

	void recieveXp(int t_xpAmt);
	bool tryPurchase(int t_price);
	bool tryRefillAmmo(std::shared_ptr<GunBasic> t_newGun);
	void recieveCash(int t_amtRecieved);

	void applyDamage(int t_damageAmt);

	bool getAlive() { return m_alive; }
	void followPosition(sf::Vector2f t_pos);
	void refillHealth();
private:
	void expire();

	std::shared_ptr<AnimatedSprite> m_body; // animated body sprite of the player
	std::shared_ptr<AnimatedSprite> m_shadow;
	std::shared_ptr<InputBasic> m_input;    // input type used by the player
	float m_speed{ 100.f };				    // speed at which the player moves every second (pixels)
	CameraTracker m_followCam;
	bool m_active{ false };
	bool m_mouseDown{ false };

	GunManager m_equippedWeapon;

	int m_xpLvl{ 0 };
	std::shared_ptr<sf::Text> m_xpText;
	int m_cashAmt{ 0 };
	std::shared_ptr<sf::Text> m_cashText;
	std::shared_ptr<sf::Text> m_weaponName;
	std::shared_ptr<sf::Text> m_hp;

	int m_health{ 0 };
	int m_healthMax{ 0 };
	float m_invincibilityTime{ 1.0f };

	float m_deadTimer{ 0.f };
	bool m_alive{ false };
};

#endif // !PLAYER_H
