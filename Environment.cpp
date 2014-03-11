#include "Environment.h"

Environment::Environment(int diff, int t)
{
	difficulty = diff;
	type = t;

	/*
	* Once we know the difficulty and track type we can then call the next
	* two functions to construct what makes up the environment
	*/

	generateTrack(t);
	addObstacles(diff);

	/* 
	* Once we have done all these functions we should have a complete
	* environment to play in and that we can update position of on the fly.
	*/
}

Environment::~Environment(void)
{
}

void Environment::generateTrack(int type)
{
	/*
	* This is where all the logic for building our 
	* track will occure.
	*/
}

void Environment::addObstacles(int difficulty)
{
	/*
	* After we construct the track we want to place obstacles on and around it
	* all the logic for placeing obstacles is here.
	*/
}

void Environment::updateEnvironment()
{
	/*
	* The controller functions on the template will call this function
	* directly to updat ethe environment and everything that comprises the
	* environment based on keyboard and mouse clicks
	*/
}

void Environment::setPositionX(float posX)
{
	positionX = posX;
}

void Environment::setPositionY(float posY)
{
	positionY = posY;
}

float Environment::getPositionX()
{
	return positionX;
}

float Environment::getPositionY()
{
	return positionY;
}

