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

public:
	int trackAtlas[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS];

	Track();
	~Track(void);

	string getName();
	string getDescription();
	int getRows();
	int getCols();

	void setName(string name);
	void setDescription(string description);
	void setRows(int rows);
	void setCols(int cols);
	void setTrack(int track[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS]);
};
