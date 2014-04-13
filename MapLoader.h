#pragma once
#include "template.h"
#include <string>
#include "track.h"

class MapLoader
{
private:
	Track map;
	string lines[1000];

	string assets[17];
	int track[20][20];
	int objects[80][80];

	string mapName;
	string mapDescription;
	int rows;
	int cols;
	int startPosX;
	int startPosY;

public:
	MapLoader();
	~MapLoader(void);

	void loadFile(string);
	void processTrackRow(string row, int rowNum);
	void processObjectRow(string row, int rowNum);
	void storeData();

	Track getTrack();
};