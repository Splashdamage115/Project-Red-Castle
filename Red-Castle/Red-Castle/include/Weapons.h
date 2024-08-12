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
};

class BasicPistol : public GunBasic
{
public:
	virtual std::string textureLocation() { return "UNAVAILABLE"; }
	virtual float cooldown()              { return 0.5f; }     // time between shots
	virtual float spread()                { return 20; }         // spread angle
	virtual int bulletSpread()            { return 4; }          // amount of bullets that are spread
	virtual float bulletLife()            { return 2.f; }
	virtual float bulletSpeed()           { return 450.f; }
	virtual int lowDamage()               { return 1; }          // least damage a bullet will do
	virtual int highDamage()              { return 3; }
	virtual float explosiveRadius()       { return 100.f; }
	virtual bool fullAuto()               { return true; }
};

#endif // !WEAPONS_H