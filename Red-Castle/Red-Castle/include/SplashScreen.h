// SplashScreen plays on launch
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "GameMode.h"
#include "AnimatedSprite.h"

class SplashScreen : public GameMode
{
public:
	SplashScreen();  // standard constructor
	~SplashScreen(); // standard deconstructor (shouldnt be used)

	virtual void resetLevel();                         // used to reset the level for each session instead of reconstructing
	virtual void events(sf::Event& t_event);           // used to handle all new events outside key presses
	virtual void update();         // all update events

private:
	virtual void processKeys(sf::Event& t_event);      // handles all key inputs
	virtual void processMouse(sf::Event& t_event);     // handles all mouse events

	std::shared_ptr<AnimatedSprite> m_logo;
	float m_currentTime{ 0.f };
	float m_targetTime{ 3.f };
};

#endif // !SPLASHSCREEN_H