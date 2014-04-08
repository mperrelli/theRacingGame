#pragma once
#include "template.h"
#include <string>
#include "track.h"
using namespace std;

class Environment
{
private:
	static const int TRACK_TILE_SIZE = 128;
	static const int OBSTACLE_TILE_SIZE = 32;

	static const int TRACK_ATLAST_START_INDEX = 50;

	// Constants for the image indecies
	static const int GRASS         = 10;
	static const int TRACK         = 11;
	static const int TRACK_TURN    = 12;
	static const int BARRIER       = 13;
	static const int BARRIER_TURN  = 14;
	
	/*
	* This is the map instance that is loaded into the game currently.
	*
	* This should be changed to a pointer later
	*/
	Track map;

	float positionX;
	float positionY;

	int tileRows;
	int tileCols;

	void loadTiles();
	void createSprites();

public:
	Environment();
	~Environment(void);

	void processTrack();
	void updateEnvironment();
	void setPositionX(float posX);
	void setPositionY(float posY);
	void draw();
	void setTrack(Track t);

	float getPositionX();
	float getPositionY();
};
