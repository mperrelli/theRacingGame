#include "Vehicle.h"
#include <iostream>

using namespace std;

// Constructor
Vehicle::Vehicle(int sIndex){}

void Vehicle::setColor(string color){
	SetSpriteColor(sIndex, INT, INT, INT, INT);
}

int Vehicle::getHealth(){
	return this->health;
}

void Vehicle::setHealth(int health){
	this->health = health;
}