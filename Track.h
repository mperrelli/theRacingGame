#pragma once
#include "template.h"
#include <string>
using namespace std;

class Track
{
private:
	static const int TRACK_MAX_SIZE_ROWS = 20;
	static const int TRACK_MAX_SIZE_COLS = 20;

	string name;
	string description;
	int rows;
	int cols;
	int startPosX;
	int startPosY;

public:
	static const int MAX_ASSETS = 17;

	int trackAtlas[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS];
	string assets[MAX_ASSETS];

	Track();
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
	void setAssets(string assets[MAX_ASSETS]);
};
