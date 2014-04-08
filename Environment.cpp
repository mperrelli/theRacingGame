#include "template.h"
#include <string>
#include "Environment.h"
#include "Track.h"
using namespace AGK;
using namespace std;

Environment::Environment()
{
	positionX = 0;
	positionY = 0;
	tileRows = 0;
	tileCols = 0;
}

Environment::~Environment(void)
{
}

void Environment::processTrack()
{
	tileRows = map.getRows();
	tileCols = map.getCols();
}

void Environment::setTrack(Track t)
{
	/*
	* Once we know the difficulty and track type we can then call the next
	* two functions to construct what makes up the environment
	*/

	map = t;

	processTrack();

	loadTiles();

	createSprites();

	draw();
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
			agk::CreateSprite(spriteIndex, map.trackAtlas[r][c]);

			// Increment sprite Index
			spriteIndex++;
		}
	}
}