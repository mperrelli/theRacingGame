#include "template.h"
#include <string>
#include <sstream>
#include "Track.h"
#include "Log.h"
using namespace std;

Track::Track()
{
	name = "none";
	description = "none";
	trackRows = TRACK_MAX_SIZE_ROWS;
	trackCols = TRACK_MAX_SIZE_COLS;
	objectRows = OBJECT_MAX_SIZE_ROWS;
	objectCols = OBJECT_MAX_SIZE_COLS;
	startPosX = 50;
	startPosY = 50;

	for(int i = 0; i < trackRows; i++)
	{
		for(int j = 0; j < trackCols; j++)
		{
			trackAtlas[i][j] = 0;
		}
	}

	for(int i = 0; i < objectRows; i++)
	{
		for(int j = 0; j < objectCols; j++)
		{
			objectAtlas[i][j] = 0;
		}
	}


	for(int i = 0; i < MAX_ASSETS; i++)
	{
		assets[i] = "";
	}
}

Track::Track(string name, string desc, int rows, int cols, int startPosX, int startPosY,
			 int track[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS],
			 int objects[OBJECT_MAX_SIZE_ROWS][OBJECT_MAX_SIZE_COLS],
			 string assets[MAX_ASSETS])
{
	setName(name);
	setDescription(desc);
	setStartPosX(startPosX);
	setStartPosY(startPosY);
	setRows(rows);
	setCols(cols);
	setAssets(assets);
	setTrack(track);
	setObjects(objects);
}

Track::~Track(void)
{
}

string Track::getName()
{
	return name;
}

string Track::getDescription()
{
	return description;
}

int Track::getRows()
{
	return trackRows;
}

int Track::getCols()
{
	return trackCols;
}

void Track::setName(string n)
{
	name = n;
}

void Track::setDescription(string d)
{
	description = d;
}

void Track::setRows(int r)
{
	trackRows = r;
	objectRows = r * 4;
}

void Track::setCols(int c)
{
	trackCols = c;
	objectCols = c * 4;
}

void Track::setStartPosX(int posX)
{
	startPosX = posX;
}

void Track::setStartPosY(int posY)
{
	startPosY = posY;
}

int Track::getStartPosX()
{
	return startPosX;
}

int Track::getStartPosY()
{
	return startPosY;
}

void Track::setTrack(int track[TRACK_MAX_SIZE_ROWS][TRACK_MAX_SIZE_COLS])
{
	for(int i = 0; i < trackRows; i++)
	{
		for(int j = 0; j < trackCols; j++)
		{
			trackAtlas[i][j] = track[i][j];
		}
	}
}

void Track::setObjects(int objects[OBJECT_MAX_SIZE_ROWS][OBJECT_MAX_SIZE_COLS])
{
	for(int i = 0; i < objectRows; i++)
	{
		for(int j = 0; j < objectRows; j++)
		{
			objectAtlas[i][j] = objects[i][j];
		}
	}
}

/*
*	Loads all the images names from the map into a track instance.
*/
void Track::setAssets(string a[MAX_ASSETS])
{
	for(int i = 0; i < MAX_ASSETS; i++)
	{
		assets[i] = a[i];
	}
}

/*
*	Returns the path to a particular image for the map.
*/
string Track::getPathToAsset(int index)
{
	string path = "resources/" + getName() + "/" + assets[index] + "";

	return path;
}
