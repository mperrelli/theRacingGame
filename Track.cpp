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
	rows = TRACK_MAX_SIZE_ROWS;
	cols = TRACK_MAX_SIZE_COLS;
	startPosX = 50;
	startPosY = 50;

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			trackAtlas[i][j] = 0;
		}
	}


	for(int i = 0; i < MAX_ASSETS; i++)
	{
		assets[i] = "";
	}
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
	return rows;
}

int Track::getCols()
{
	return cols;
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
	rows = r;
}

void Track::setCols(int c)
{
	cols = c;
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
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			trackAtlas[i][j] = track[i][j];
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
