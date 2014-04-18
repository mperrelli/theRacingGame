#include "template.h"
#include <string>
#include "Globals.h"
#include "Vehicle.h"
#include "Log.h"
#include <iostream>
using namespace std;
using namespace AGK;

// Constructor
Vehicle::Vehicle() : Sprite()
{
    health = 100;
    maxSpeed = 100;
    controlFactor = 0;
    active = false;
	currSpeed = 0.0f;
	velocityX = 0.0f;

	setIntervals();
}

Vehicle::Vehicle(int sIndex, string image, int maxSpeed, int controlFactor) : Sprite(sIndex, image)
{
    health = 100;
    maxSpeed = maxSpeed;
    controlFactor = controlFactor;
    active = false;
	currSpeed = 0.0f;

	setIntervals();
}

void Vehicle::setIntervals()
{
	accelInterval = 0.1f;
	deccelInterval = -0.05f;
	breakInterval = -0.1f;
}

void Vehicle::setAngle(int a)
{
	agk::SetSpriteAngle(spriteIndex, (float)a);
}

void Vehicle::accelerate()
{
	if(currSpeed < maxSpeed)
	{
		currSpeed += accelInterval;
	}
}

void Vehicle::deccelerate()
{
	if(currSpeed > 0)
	{
		currSpeed += deccelInterval;
	}
	else if(currSpeed <= 0)
	{
		currSpeed = 0;
	}
}

void Vehicle::applyBreak()
{
	if(currSpeed > 0)
	{
		currSpeed += breakInterval;
	}
	else if(currSpeed <= 0)
	{
		currSpeed = 0;
	}
}

int Vehicle::getTurnSpeed()
{
	int turnspeed[12] = {6, 6, 6, 6, 6, 5, 5, 5, 4, 4, 3, 2};

	Log::Instance()->writeToLogFile((int)floor(currSpeed));

	return turnspeed[(int)floor(currSpeed) - 1] + controlFactor;
}

float Vehicle::getAngle()
{
	return agk::GetSpriteAngle(spriteIndex);
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

float Vehicle::getCurrSpeed()
{
	return currSpeed;
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