#include "AbstractTarget.h"

#include <iostream>

void AbstractTarget::takeDamage(float damage)
{
	health -= damage;
	damage_taken += damage;
	if (health <= 0.0f)
	{
		health = 0.0f;
		destroyed = true;
	}
}

bool AbstractTarget::isMissed()
{
	float chance = 1.0f * rand() / RAND_MAX;

	if (chance <= this->chance)
		return true;

	return false;
}

bool AbstractTarget::isShown()
{
	return !destroyed;
}