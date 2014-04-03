#include "template.h"
#include "Environment.h"
#include <string>
#include <vector>
using namespace AGK;

Environment::Environment(int diff, int t)
{
	difficulty = diff;
	type = t;
	positionX = 0;
	positionY = 0;
	tileRows = 0;
	tileCols = 0;
	trackAtlas = NULL;

	/*
	* Once we know the difficulty and track type we can then call the next
	* two functions to construct what makes up the environment
	*/

	loadTiles();

	generateTrack(t);

	createSprites();

	draw();

	/* 
	* Once we have done all these functions we should have a complete
	* environment to play in and that we can update position of on the fly.
	*/
}

Environment::~Environment(void)
{
}

void Environment::generateTrack(int type)
{
	/*
	* This is where all the logic for building our 
	* track will occure. 
	*/

	switch(type)
	{
	case LINEAR:

		int track[LINEAR_ROWS][LINEAR_COLS] =
		{ {GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS},
		  {GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS},
		  {TRACK, TRACK, TRACK, TRACK, TRACK, TRACK, TRACK, TRACK, TRACK, TRACK},
		  {GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS},
		  {GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS},
		};

		trackAtlas = track;

		positionX = 0;
		positionY = -80;

		tileRows = LINEAR_ROWS;
		tileCols = LINEAR_COLS;

		break;
	case CYCLICAL:

		break;
	}
}

void Environment::updateEnvironment()
{
	/*
	* The controller functions on the template will call this function
	* directly to updat ethe environment and everything that comprises the
	* environment based on keyboard and mouse clicks
	*/
}

void Environment::setPositionX(float posX)
{
	positionX = posX;
}

void Environment::setPositionY(float posY)
{
	positionY = posY;
}

float Environment::getPositionX()
{
	return positionX;
}

float Environment::getPositionY()
{
	return positionY;
}

void Environment::draw()
{
	// Variables for the tile coordinates
	float x = 0, y = 0;

	// Variable to temporarily hold a sprite index
	int spriteIndex = TRACK_ATLAST_START_INDEX;

	// Display all the tiles specified in the map.
	for (int r = 0; r < tileRows; r++)
	{
		// Set x to 0.
		x = 0;

		// Display all the tiles in this row.
		for (int c = 0; c < tileCols; c++)
		{
			// Set the tile's position.
			agk::SetSpritePosition(spriteIndex, x, y);

			// Increment sprite Index
			spriteIndex++;

			// Update the X coordinate for the next tile.
			x += TRACK_TILE_SIZE;
		}

		// Increase y for the next row.
		y += TRACK_TILE_SIZE;
	}
}

void Environment::loadTiles()
{  
   agk::LoadImage(GRASS,          "Resources/grass.png");
   agk::LoadImage(TRACK,          "Resources/track.png");
   agk::LoadImage(TRACK_TURN,     "Resources/trackturn.png");
   agk::LoadImage(BARRIER,        "Resources/barrier.png");
   agk::LoadImage(BARRIER_TURN,   "Resources/barrierturn.png");
}

void Environment::createSprites()
{
	int spriteIndex = TRACK_ATLAST_START_INDEX;

	for (int r = 0; r < tileRows; r++)
	{
		// Display all the tiles in this row.
		for (int c = 0; c < tileCols; c++)
		{
			// Create a sprite for this tile.
			agk::CreateSprite(spriteIndex, trackAtlas[r][c]);

			// Increment sprite Index
			spriteIndex++;
		}
	}
}