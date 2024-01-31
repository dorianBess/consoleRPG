#include "Entity.h"
#include <iostream>

Entity::Entity() : name("default"), healthPoints(10), attackPoints(5),defensePoints(0)
{
	currentHealth = healthPoints;
}

Entity::Entity(const std::string& name, int healthPoints, int attackPoints,int defensePoints) : name(name), healthPoints(healthPoints + defensePoints), attackPoints(attackPoints),defensePoints(defensePoints)
{
	currentHealth = healthPoints;
}

int Entity::TakeDamage(int value)
{
	value -= defensePoints;
	if (value <= 0)
	{
		value = 1;
	}
	currentHealth -= value;
	if (currentHealth < 0) currentHealth = 0;
	std::cout << this->name << " a recu " << value << " degats." << std::endl;
	return value;
}

int Entity::Attack(Entity* cible)
{
	std::cout << this->name << " attaque " << cible->name << " avec ses poings. " << std::endl;
	return cible->TakeDamage(attackPoints);
}

bool Entity::isAlive()
{
	return currentHealth > 0;
}


