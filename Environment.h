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

	static const int TRACK_ATLAST_START_INDEX = 100;

	// Constants for the image indecies
	static const int ASSETS_START_INDEX = 50;
	static const int BG               = ASSETS_START_INDEX;
	static const int TRACK_H          = ASSETS_START_INDEX + 1;
	static const int TRACK_V          = ASSETS_START_INDEX + 2;
	static const int TRACK_TURN_EN    = ASSETS_START_INDEX + 3;
	static const int TRACK_TURN_ES    = ASSETS_START_INDEX + 4;
	static const int TRACK_TURN_WN    = ASSETS_START_INDEX + 5;
	static const int TRACK_TURN_WS    = ASSETS_START_INDEX + 6;
	static const int BARRIER_H        = ASSETS_START_INDEX + 7;
	static const int BARRIER_V        = ASSETS_START_INDEX + 8;
	static const int BARRIER_TURN_EN  = ASSETS_START_INDEX + 9;
	static const int BARRIER_TURN_ES  = ASSETS_START_INDEX + 10;
	static const int BARRIER_TURN_WN  = ASSETS_START_INDEX + 11;
	static const int BARRIER_TURN_WS  = ASSETS_START_INDEX + 12;
	static const int BARRIER_END_EW   = ASSETS_START_INDEX + 13;
	static const int BARRIER_END_NS   = ASSETS_START_INDEX + 14;
	static const int BARRIER_END_SN   = ASSETS_START_INDEX + 15;
	static const int BARRIER_END_WE   = ASSETS_START_INDEX + 16;
	
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
