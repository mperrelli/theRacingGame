#pragma once
#include <string>
#include "template.h"
#include "Globals.h"
using namespace std;

class Track
{
private:
	string name;
	string description;
	int trackRows;
	int trackCols;
	int objectRows;
	int objectCols;
	int startPosX;
	int startPosY;
	int AIStartPosX;
	int AIStartPosY;
	int time;

public:
	int trackAtlas[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS];
	int objectAtlas[OBJECT_MAX_SIZE_ROWS][OBJECT_MAX_SIZE_COLS];
	string assets[MAX_ASSETS];

	Track();
	Track(string name, string description, int rows, int cols, int posX, int posY,
			 int AIStartPosX,int AIStartPosY,
			 int track[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS],
			 int objects[OBJECT_MAX_SIZE_ROWS][OBJECT_MAX_SIZE_COLS],
			 string a[MAX_ASSETS], int time);
	~Track(void);

	string getName();
	string getDescription();
	int getRows();
	int getCols();
	int getStartPosX();
	int getStartPosY();
	int getAIStartPosX();
	int getAIStartPosY();
	int getTime();
	string getPathToAsset(int assetIndex);

	void setName(string name);
	void setDescription(string description);
	void setRows(int rows);
	void setCols(int cols);
	void setStartPosX(int posX);
	void setStartPosY(int posY);
	void setAIStartPosX(int posX);
	void setAIStartPosY(int posY);
	void setTrack(int track[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS]);
	void setObjects(int objects[OBJECT_MAX_SIZE_ROWS][OBJECT_MAX_SIZE_COLS]);
	void setAssets(string assets[MAX_ASSETS]);
	void setTime(int time);
};
