#include "template.h"
#include <string>
#include "Environment.h"
#include "Track.h"
#include "log.h"
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
	objectRows = tileRows * 4;
	objectCols = tileCols * 4;

	positionX = SCREEN_CENTER_X - map.getStartPosX();
	positionY = SCREEN_CENTER_Y - map.getStartPosY();
}

/*
*	We are attaching a map to the environment here. Then calling
*	all the subsequent actions that need to take place to load that map.
*/
void Environment::setTrack(Track t)
{
	map = t;

	processTrack();

	loadTiles();

	createSprites();

	draw();
}

/*
*	The controller functions on the template will call this function
*	directly to update the environment and everything that comprises the
*	environment based on keyboard and mouse clicks
*/
void Environment::updateEnvironment()
{
	
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

/*
*	Draws the current state of the environment. This will simply 
*	move the track atlas around according to current environment
*	position.
*/
void Environment::draw()
{
	// Variables for the tile coordinates
	float x = getPositionX(), y = getPositionY();

	// Variable to temporarily hold a sprite index
	int spriteIndex = TRACK_ATLAST_START_INDEX;

	// Update all the tiles specified in the map.
	for (int r = 0; r < tileRows; r++)
	{
		// Set x to default X position.
		x = getPositionX();

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

	x = getPositionX();
	y = getPositionY();

	// Update all the objects specified in the map.
	for (int r = 0; r < objectRows; r++)
	{
		// Set x to default X position.
		x = getPositionX();

		// Display all the tiles in this row.
		for (int c = 0; c < objectCols; c++)
		{
			if(map.objectAtlas[r][c] != 0)
			{
				// Set the tile's position.
				agk::SetSpritePosition(spriteIndex, x, y);

				// Increment sprite Index
				spriteIndex++;
			}

			// Update the X coordinate for the next tile.
			x += OBJECT_TILE_SIZE;
		}

		// Increase y for the next row.
		y += OBJECT_TILE_SIZE;
	}
}

/*
*	Loads all the images from the map into the environment as
*	AGK images. This is done so that we can use these images 
*	to make sprites later.
*/
void Environment::loadTiles()
{  
	string temp;

	for(int i = 0; i < map.MAX_ASSETS; i++)
	{
		temp = map.getPathToAsset(i);
		agk::LoadImage(ASSETS_START_INDEX + i, temp.c_str());
	}
}

/*
*	Creates all the sprites from the maps trackAtlas.
*	This should only need to be done once per map load.
*/
void Environment::createSprites()
{
	int spriteIndex = TRACK_ATLAST_START_INDEX;

	// Create sprites for all track pieces
	for (int r = 0; r < tileRows; r++)
	{
		// Display all the tiles in this row.
		for (int c = 0; c < tileCols; c++)
		{
			// Create a sprite for this tile.
			agk::CreateSprite(spriteIndex, map.trackAtlas[r][c]);
			agk::SetSpriteDepth(spriteIndex, 1);

			// Increment sprite Index
			spriteIndex++;
		}
	}

	// Create sprites for all objects
	for (int r = 0; r < objectRows; r++)
	{
		// Display all the tiles in this row.
		for (int c = 0; c < objectCols; c++)
		{
			// Create a sprite for this tile.
			if(map.objectAtlas[r][c] > 0)
			{
				agk::CreateSprite(spriteIndex, map.objectAtlas[r][c]);
				agk::SetSpriteDepth(spriteIndex, 0);

				// Increment sprite Index
				spriteIndex++;
			}
		}
	}
}