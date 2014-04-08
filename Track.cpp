#include "template.h"
#include <string>
#include "Track.h"
using namespace std;

Track::Track()
{
	name = "none";
	description = "none";
	rows = TRACK_MAX_SIZE_ROWS;
	cols = TRACK_MAX_SIZE_COLS;

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			trackAtlas[i][j] = 0;
		}
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

