#pragma once
#include "template.h"
#include <string>
#include "track.h"
using namespace std;

class Environment
{
private:
	static const int SCREEN_WIDTH  = 640;
	static const int SCREEN_HEIGHT = 480;

	static const int SCREEN_CENTER_X = SCREEN_WIDTH / 2;
	static const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;

	static const int TRACK_TILE_SIZE = 128;
	static const int OBJECT_TILE_SIZE = 32;

	static const int TRACK_ATLAST_START_INDEX = 50;

	// Constants for the image indecies
	static const int ASSETS_START_INDEX = 10;
	static const int BG               = 10;
	static const int TRACK_H          = 11;
	static const int TRACK_V          = 12;
	static const int TRACK_TURN_EN    = 13;
	static const int TRACK_TURN_ES    = 14;
	static const int TRACK_TURN_WN    = 15;
	static const int TRACK_TURN_WS    = 16;
	static const int BARRIER_H        = 17;
	static const int BARRIER_V        = 18;
	static const int BARRIER_TURN_EN  = 19;
	static const int BARRIER_TURN_ES  = 20;
	static const int BARRIER_TURN_WN  = 21;
	static const int BARRIER_TURN_WS  = 22;
	static const int BARRIER_END_EW   = 23;
	static const int BARRIER_END_NS   = 24;
	static const int BARRIER_END_SN   = 25;
	static const int BARRIER_END_WE   = 26;
	
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
	void updateEnvironment();
	void setPositionX(float posX);
	void setPositionY(float posY);
	void draw();
	void setTrack(Track t);

	float getPositionX();
	float getPositionY();
};
