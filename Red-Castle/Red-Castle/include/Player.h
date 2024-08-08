#ifndef PLAYER_H
#define PLAYER_H

#include "Library.h"
#include "AnimatedSprite.h"
#include "InputSwitcher.hpp"
#include "cameraTracker.h"

class Player
{
public:
	Player();
	~Player();
	void init(sf::Vector2f t_position); // initialise the player to the passed position

	void update(); 
	
	sf::Vector2f getPos() { return m_body->getPosition(); } // return the players position


private:
	std::shared_ptr<AnimatedSprite> m_body; // animated body sprite of the player
	std::shared_ptr<InputBasic> m_input;    // input type used by the player
	float m_speed{ 100.f };				    // speed at which the player moves every second (pixels)
	CameraTracker m_followCam;
};

#endif // !PLAYER_H
