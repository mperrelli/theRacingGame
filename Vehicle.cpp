#include "template.h"
#include <string>
#include "Vehicle.h"
#include "Log.h"
#include <iostream>
using namespace std;
using namespace AGK;

// Constructor
Vehicle::Vehicle() : Sprite()
{
    health = 100;
    maxSpeed = 0;
    controlFactor = 0;
    active = false;
	currSpeed = 0.0f;
	surface = TRACK_V;

	setIntervals();
}

Vehicle::Vehicle(int sIndex, string image, int maxSpeed, int controlFactor) : Sprite(sIndex, image)
{
    health = 100;
    maxSpeed = maxSpeed;
    controlFactor = controlFactor;
    active = false;
	currSpeed = 0.0f;
	surface = TRACK_V;

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

// Increases vehicle acceleration by the acceleration interval
void Vehicle::accelerate()
{
	if(currSpeed < getMaxSpeed())
	{
		currSpeed += accelInterval;
	}
}

// Decreases vehicle acceleration by the decceleration interval
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

// Decreases vehicle acceleration by the break interval
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

// returns how easily the car should turn based on speed
int Vehicle::getTurnSpeed()
{
	int turnspeed[12] = {6, 6, 6, 6, 6, 5, 5, 5, 4, 4, 3, 2};

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
	if(surface == BG)
	{
		return maxSpeed - 9;
	}

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
			agk::SetSpriteColor(getSpriteIndex(), 255, 0, 0, 255);
			break;
		case 'G':
			agk::SetSpriteColor(getSpriteIndex(), 0, 255, 0, 255);
			break;
		default:
			agk::SetSpriteColor(getSpriteIndex(), 0, 0, 255, 255);
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

void Vehicle::update()
{
	int sIndex = -1;

	// Set exhaust animation
	if(getCurrSpeed() > 4)
	{
		if(agk::GetSpriteImageID(getSpriteIndex()) != CAR_MOVING)
		{
			setImage(CAR_MOVING);
		}
	}
	else if(agk::GetSpriteImageID(getSpriteIndex()) != CAR)
	{
		setImage(CAR);
	}

	// Get surface
	sIndex = agk::GetSpriteHitGroup(SPRITE_GROUP_TRACK ,getCenterX(), getCenterY());

	surface = agk::GetSpriteImageID(sIndex);

	// Respond to surface
	if(surface == BG)
	{
		if(currSpeed > getMaxSpeed())
		{
			deccelerate();
			deccelerate();
			deccelerate();
		}
	}
	else if(surface == BARRIER_H || 
		    surface == BARRIER_V || 
			surface == BARRIER_TURN_EN || 
			surface == BARRIER_TURN_ES || 
			surface == BARRIER_TURN_WN || 
			surface == BARRIER_TURN_WS || 
			surface == BARRIER_END_EW ||
			surface == BARRIER_END_NS || 
			surface == BARRIER_END_SN || 
			surface == BARRIER_END_WE)
	{
		currSpeed = 0;
	}
}