#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <string>
#include "Sprite.h"

class Vehicle : public Sprite{

private:
	int health, maxSpeed, controlFactor;
	bool active;

public:
	Vehicle();
	int getControlFactor();
	int getHealth();
	int getMaxSpeed();
	bool isActive();
	void setActive(bool active);
	void setColor(char color);
	void setControlFactor(int controlFactor);
	void setHealth(int health);
	void setMaxSpeed(int maxSpeed);
};

#endif