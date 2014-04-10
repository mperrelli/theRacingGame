#include "template.h"
#include <string>
#include "Vehicle.h"

using namespace std;

// Constructor
Vehicle::Vehicle(int sIndex, int maxSpeed, int controlFactor){}

void Vehicle::setColor(string color)
{
	// SetSpriteColor(sIndex, INT, INT, INT, INT);
}

int Vehicle::getHealth()
{
	return this->health;
}

void Vehicle::setHealth(int health)
{
	this->health = health;
}