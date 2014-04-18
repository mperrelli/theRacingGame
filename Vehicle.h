#ifndef VEHICLE_H
#define VEHICLE_H
#include "template.h"
#include <string>
#include "Sprite.h"

class Vehicle : public Sprite{

private:
	float accelInterval;
	float deccelInterval;
	float breakInterval;

	int health, maxSpeed, controlFactor;
	bool active;

	float currSpeed;

	void setIntervals();

public:
	Vehicle();
	Vehicle(int sIndex, string image, int maxSpeed, int controlFactor);
	int getControlFactor();
	int getHealth();
	int getMaxSpeed();
	float getAngle();
	float getCurrSpeed();
	bool isActive();
	void setActive(bool active);
	void setColor(char color);
	void setControlFactor(int controlFactor);
	void setHealth(int health);
	void setMaxSpeed(int maxSpeed);
	void setAngle(float);
	void accelerate();
	void deccelerate();
	void applyBreak();
};

#endif