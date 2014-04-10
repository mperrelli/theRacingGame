#include "template.h"
#include <string>
#include "Globals.h"
#include "Vehicle.h"
#include "template.h"
#include <iostream>

using namespace std;
using namespace AGK;

// Constructor
Vehicle::Vehicle()
{
	// These values can change, just temporary place holders
	health = 100;
	maxSpeed = 100;
	controlFactor = 1;
	active = false;
}

int Vehicle::getControlFactor()
{
	return controlFactor;
}

int Vehicle::getHealth()
{
	return health;
}

int Vehicle::getMaxSpeed()
{
	return maxSpeed;
}

void Vehicle::setActive(bool a)
{
	active = a;
}

void Vehicle::setColor(char color)
{
	// 'R' for RED
	// 'G' for GREEN
	// 'B' FOR BLUE
	switch(color)
	{
		case 'R': 
			agk::SetSpriteColor(spriteIndex, 255, 0, 0, 255);
			break;
		case 'G':
			agk::SetSpriteColor(spriteIndex, 50, 205, 50, 255);
			break;
		default:
			agk::SetSpriteColor(spriteIndex, 0, 199, 255, 255);
	}
}

void Vehicle::setControlFactor(int cf)
{
	controlFactor = cf;
}

void Vehicle::setHealth(int h)
{
	health = h;
}

void Vehicle::setMaxSpeed(int ms)
{
	maxSpeed = ms;
}

bool Vehicle::isActive()
{
	return active;
}