#ifndef PLAYER_H
#define PLAYER_H

#include "Library.h"
#include "AnimatedSprite.h"
#include "InputSwitcher.hpp"
#include "cameraTracker.h"
#include "GunManager.h"

class Player
{
public:
	Player();
	~Player();
	void init(sf::Vector2f t_position); // initialise the player to the passed position

	void update();
	
	inline sf::Vector2f getPos() { return m_body->getPosition(); } // return the players position

	void setMouse(bool t_) { m_mouseDown = t_; m_equippedWeapon.setMouse(t_); }

	void setAimVector(sf::Vector2f& t_aimToFollow) { m_equippedWeapon.setPositioning(m_body->getPosition(), t_aimToFollow); }
private:
	std::shared_ptr<AnimatedSprite> m_body; // animated body sprite of the player
	std::shared_ptr<InputBasic> m_input;    // input type used by the player
	float m_speed{ 100.f };				    // speed at which the player moves every second (pixels)
	CameraTracker m_followCam;
	bool m_active{ false };
	bool m_mouseDown{ false };

	GunManager m_equippedWeapon;
};

#endif // !PLAYER_H
