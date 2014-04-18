#pragma once
#include "template.h"
#include <string>
#include "Globals.h"
#include "track.h"
#include "Vehicle.h"
using namespace std;

class Environment
{
private:
	static const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;
	static const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;

	static const int TRACK_ATLAS_START_INDEX = 200;
	
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
	int objectRows;
	int objectCols;

	void loadTiles();
	void createSprites();

public:
	Environment();
	~Environment(void);

	void processTrack();
	void updateEnvironment(float x, float y, float);
	void setPositionX(float posX);
	void setPositionY(float posY);
	void draw();
	void setTrack(Track t);

	float getPositionX();
	float getPositionY();
};
