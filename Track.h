#pragma once
#include "template.h"
#include <string>
using namespace std;

class Track
{
private:
	static const int TRACK_BLOCK_SIZE = 128;
	static const int OBJECT_BLOCK_SIZE = 32;

	static const int TRACK_MAX_SIZE_ROWS = 20;
	static const int TRACK_MAX_SIZE_COLS = 20;
	static const int OBJECT_MAX_SIZE_COLS = 80;
	static const int OBJECT_MAX_SIZE_ROWS = 80;

	string name;
	string description;
	int trackRows;
	int trackCols;
	int objectRows;
	int objectCols;
	int startPosX;
	int startPosY;

public:
	static const int MAX_ASSETS = 17;

	int trackAtlas[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS];
	int objectAtlas[OBJECT_MAX_SIZE_ROWS][OBJECT_MAX_SIZE_COLS];
	string assets[MAX_ASSETS];

	Track();
	Track(string name, string description, int rows, int cols, int posX, int posY,
			 int track[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS],
			 int objects[OBJECT_MAX_SIZE_ROWS][OBJECT_MAX_SIZE_COLS],
			 string a[MAX_ASSETS]);
	~Track(void);

	string getName();
	string getDescription();
	int getRows();
	int getCols();
	int getStartPosX();
	int getStartPosY();
	string getPathToAsset(int assetIndex);

	void setName(string name);
	void setDescription(string description);
	void setRows(int rows);
	void setCols(int cols);
	void setStartPosX(int posX);
	void setStartPosY(int posY);
	void setTrack(int track[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS]);
	void setObjects(int objects[OBJECT_MAX_SIZE_ROWS][OBJECT_MAX_SIZE_COLS]);
	void setAssets(string assets[MAX_ASSETS]);
};
