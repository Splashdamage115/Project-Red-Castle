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

	void reload();
	void reloadWeaponToMax();
	bool refillWeapon();
private:
	void spawnBullet();

	sf::Vector2f m_position;
	sf::Vector2f m_aim;

	std::shared_ptr<AnimatedSprite> m_weaponBody;
	std::shared_ptr<sf::Text> m_magazineText;

	bool m_mouseDown{ false };

	std::shared_ptr<GunBasic> m_currentWeapon;
	float m_shootCooldownRemaining{ 0.f };
	float m_shootCooldownMax{ 0.f };
	float m_reloadTime{ 0.f };
	bool m_reloading{ false };

	int m_stockpileMax{ 0 };
	int m_stockpile{ 0 };
	int m_magazine{ 0 };
	int m_magazineMax{ 0 };
	float m_startReloadAngle{ 0.f };
};

#endif // !GUN_MANAGER_H
