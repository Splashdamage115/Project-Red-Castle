#ifndef GUN_MANAGER_H
#define GUN_MANAGER_H

#include "Library.h"
#include "Weapons.h"

class GunManager
{
public:
	GunManager();
	void equipNewGun(std::shared_ptr<GunBasic> t_newGun);
	void setPositioning(sf::Vector2f& t_startLocation, sf::Vector2f& t_aim);

	void update();

	void setMouse(bool t_newMouse);
private:
	sf::Vector2f m_position;
	sf::Vector2f m_aim;

	bool m_mouseDown{ false };

	std::shared_ptr<GunBasic> m_currentWeapon;
	float m_shootCooldownRemaining{ 0.f };
	float m_shootCooldownMax{ 0.f };
};

#endif // !GUN_MANAGER_H
