#ifndef LEVELUP_SCREEN_H
#define LEVELUP_SCREEN_H

#include "Library.h"
#include "Button.h"

class LevelUpScreen
{
public:
	void init();

	void update();
	void setMouse(sf::Vector2f& t_mousePos);

	void mouseDown();
	void mouseUp();

	bool checkClosed();
private:
	sf::Vector2f m_mousePos;
	std::shared_ptr<sf::RectangleShape> m_backgroundDarkness;
	float m_animateTimeLeft{ 0.f };
	bool m_closing{ false };
	bool m_closed{ false };

	std::vector<Button> m_buttons;
	static const int BUTTON_AMOUNT = 3;
};

#endif // !LEVELUP_SCREEN_H