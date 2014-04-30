#pragma once
#include "template.h"
#include <string>
#include "Track.h"
#include "Globals.h"

class MapLoader
{
private:
	// A track instance
	Track map;

	// Array of all lines in the file that arent commented out
	string lines[1000];

	// All map data that we need to store later
	string assets[17];
	int track[20][20];
	int objects[80][80];
	string mapName;
	string mapDescription;
	int rows;
	int cols;
	int startPosX;
	int startPosY;
	int AIStartPosX;
	int AIStartPosY;
	int time;

	int applyAssetOffset(int);

public:
	MapLoader();
	~MapLoader(void);

	void loadFile(string);
	void processTrackRow(string row, int rowNum);
	void processObjectRow(string row, int rowNum);
	void storeData();

	Track getTrack();
};
