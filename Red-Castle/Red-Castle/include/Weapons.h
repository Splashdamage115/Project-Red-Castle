#ifndef WEAPONS_H
#define WEAPONS_H

#include "Library.h"
#include "AnimatedSprite.h"

enum class WeaponType
{
	Gun, ChargeUp
};

class GunBasic
{
public:
	virtual std::string textureLocation() = 0;
	virtual float cooldown() = 0;     // time between shots
	virtual float spread() = 0;       // spread angle
	virtual int bulletSpread() = 0; // amount of bullets that are spread
	virtual float bulletLife() = 0;
	virtual float bulletSpeed() = 0;
	virtual int lowDamage() = 0; // least damage a bullet will do
	virtual int highDamage() = 0;
	virtual bool fullAuto() = 0;
	// only needed if gun is explosive
	virtual float explosiveRadius() { return -1.f; }

	virtual void getAnimation(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->addFrame(sf::IntRect(0, 0, static_cast<int>(t_body->getGlobalBounds().width), static_cast<int>(t_body->getGlobalBounds().height)));
	}

	virtual int getStockpile() = 0;
	virtual int getMagazine() = 0;
	virtual float reloadTime() = 0;
	virtual int price() = 0;
};

class BasicPistol : public GunBasic
{
public:
	virtual std::string textureLocation() { return "ASSETS\\IMAGES\\MISC\\BasicPistol.png"; }
	virtual float cooldown()              { return 0.5f; }       // time between shots
	virtual float spread()                { return 20.f; }         // spread angle
	virtual int bulletSpread()            { return 1; }          // amount of bullets that are spread (shotguns)
	virtual float bulletLife()            { return 2.f; }        // how long the bullets stay alive
	virtual float bulletSpeed()           { return 450.f; }      // speed the bullets travel
	virtual int lowDamage()               { return 1; }          // least damage a bullet will do
	virtual int highDamage()              { return 3; }          // most damage the bullet will do
	virtual float explosiveRadius()       { return -1.f; }      // how big the explosion will be (-1.f if not explosive)
	virtual bool fullAuto()               { return false; }       // is the weapon full auto or semi auto?
	virtual void getAnimation(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(0.125f);
		t_body->addFrame(sf::IntRect(0, 0, 64, 32));

		t_body->setScale(sf::Vector2f(0.5f, 0.5f));
		t_body->setOrigin(sf::Vector2f(0.f,12.f)); // set origin to position at the start of the barrel (furthest from tip) (0.f, y = height of barrel)
	}

	virtual int getStockpile() { return 80; }
	virtual int getMagazine() { return 8; }
	virtual float reloadTime() { return 1.5f; }
	virtual int price() { return 350; }
};

class BasicSMG : public GunBasic
{
public:
	virtual std::string textureLocation() { return "ASSETS\\IMAGES\\MISC\\BasicSMG.png"; }
	virtual float cooldown() { return 0.1f; }       // time between shots
	virtual float spread() { return 40.f; }         // spread angle
	virtual int bulletSpread() { return 1; }          // amount of bullets that are spread (shotguns)
	virtual float bulletLife() { return 2.f; }        // how long the bullets stay alive
	virtual float bulletSpeed() { return 800.f; }      // speed the bullets travel
	virtual int lowDamage() { return 2; }          // least damage a bullet will do
	virtual int highDamage() { return 5; }          // most damage the bullet will do
	virtual float explosiveRadius() { return -1.f; }      // how big the explosion will be (-1.f if not explosive)
	virtual bool fullAuto() { return true; }       // is the weapon full auto or semi auto?
	virtual void getAnimation(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(0.125f);
		t_body->addFrame(sf::IntRect(0, 0, 64, 32));

		t_body->setScale(sf::Vector2f(0.75f, 0.75f));
		t_body->setOrigin(sf::Vector2f(24.f, 9.f)); // set origin to position at the start of the barrel (furthest from tip) (0.f, y = height of barrel)
	}

	virtual int getStockpile() { return 180; }
	virtual int getMagazine() { return 36; }
	virtual float reloadTime() { return 2.f; }
	virtual int price() { return 1800; }
};

class BasicShotgun : public GunBasic
{
public:
	virtual std::string textureLocation() { return "ASSETS\\IMAGES\\MISC\\ShotgunBasic.png"; }
	virtual float cooldown() { return 0.6f; }       // time between shots
	virtual float spread() { return 30.f; }         // spread angle
	virtual int bulletSpread() { return 5; }          // amount of bullets that are spread (shotguns)
	virtual float bulletLife() { return 1.f; }        // how long the bullets stay alive
	virtual float bulletSpeed() { return 1000.f; }      // speed the bullets travel
	virtual int lowDamage() { return 1; }          // least damage a bullet will do
	virtual int highDamage() { return 3; }          // most damage the bullet will do
	virtual float explosiveRadius() { return -1.f; }      // how big the explosion will be (-1.f if not explosive)
	virtual bool fullAuto() { return false; }       // is the weapon full auto or semi auto?
	virtual void getAnimation(std::shared_ptr<AnimatedSprite> t_body)
	{
		t_body->clearFrames();
		t_body->changeTiming(0.125f);
		t_body->addFrame(sf::IntRect(0, 0, 80, 32));

		t_body->setScale(sf::Vector2f(0.8f, 0.8f));
		t_body->setOrigin(sf::Vector2f(30.f, 8.f)); // set origin to position at the start of the barrel (furthest from tip) (0.f, y = height of barrel)
	}

	virtual int getStockpile() { return 35; }
	virtual int getMagazine() { return 5; }
	virtual float reloadTime() { return 4.f; }
	virtual int price() { return 1200; }
};

#endif // !WEAPONS_H