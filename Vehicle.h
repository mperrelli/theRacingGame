#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>

using namespace std;


class Vehicle{

private:
	int health;
	bool active;

	Vehicle(){} // Private default constructor

public:
	Vehicle(int sIndex);
	void setColor(string color);
	int getHealth();
	void setHealth(int health);
};

#endif