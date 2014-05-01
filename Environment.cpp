#include "template.h"
#include "Environment.h"
#include "Track.h"
#include "Globals.h"
#include "AI.h"
#include "Timer.h"
using namespace AGK;
using namespace std;

Environment::Environment()
{
	positionX = 0;
	positionY = 0;
	tileRows = 0;
	tileCols = 0;

	AIHead = NULL;
	AITailItem = NULL;
	AIListSize = 0;
}

Environment::~Environment(void)
{
	int spriteIndex = TRACK_ATLAS_START_INDEX;

	// Sequentially delete all track pieces
	for (int r = 0; r < tileRows; r++)
	{
		for (int c = 0; c < tileCols; c++)
		{
			agk::DeleteSprite(spriteIndex);

			// Increment sprite Index
			spriteIndex++;
		}
	}

	// Sequentially delete all objects
	for (int r = 0; r < objectRows; r++)
	{
		for (int c = 0; c < objectCols; c++)
		{
			if(map.objectAtlas[r][c] > (ASSETS_START_INDEX - ASSET_OFFSET))
			{
				agk::DeleteSprite(spriteIndex);

				// Increment sprite Index
				spriteIndex++;
			}
		}
	}

	// Sequentially delete all assets
	for (int r = 0; r < objectRows; r++)
	{
		for (int c = 0; c < objectCols; c++)
		{
			if(map.objectAtlas[r][c] > (ASSETS_START_INDEX - ASSET_OFFSET))
			{
				agk::DeleteSprite(spriteIndex);

				// Increment sprite Index
				spriteIndex++;
			}
		}
	}

	// Delete all AI cars
	for(int i = AI_SPRITE_START_INDEX; i < AIListSize + AI_SPRITE_START_INDEX; i++)
		agk::DeleteSprite(i);
}

void Environment::processTrack()
{
	tileRows = map.getRows();
	tileCols = map.getCols();
	objectRows = tileRows * OBJECTS_PER_TILEROW;
	objectCols = tileCols * OBJECTS_PER_TILEROW;

	positionX = float(SCREEN_CENTER_X - map.getStartPosX());
	positionY = float(SCREEN_CENTER_Y - map.getStartPosY());
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
void Environment::updateEnvironment(float x, float y, float speed)
{
	positionX -= x * speed;
	positionY -= y * speed;

	manageAI();

	draw();
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
	int spriteIndex = TRACK_ATLAS_START_INDEX;

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
			if(map.objectAtlas[r][c] > (ASSETS_START_INDEX - ASSET_OFFSET))
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

	for(int i = 0; i < MAX_ASSETS; i++)
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
	int spriteIndex = TRACK_ATLAS_START_INDEX;

	// Create sprites for all track pieces
	for (int r = 0; r < tileRows; r++)
	{
		// Display all the tiles in this row.
		for (int c = 0; c < tileCols; c++)
		{
			// Create a sprite for this tile.
			agk::CreateSprite(spriteIndex, map.trackAtlas[r][c]);
			agk::SetSpriteDepth(spriteIndex, 1);
			agk::SetSpriteGroup(spriteIndex, SPRITE_GROUP_TRACK);

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
			if(map.objectAtlas[r][c] > (ASSETS_START_INDEX - ASSET_OFFSET))
			{
				agk::CreateSprite(spriteIndex, map.objectAtlas[r][c]);
				agk::SetSpriteDepth(spriteIndex, 0);
				agk::SetSpriteGroup(spriteIndex, SPRITE_GROUP_TRACK);

				// Increment sprite Index
				spriteIndex++;
			}
		}
	}

	g_assetsEndIndex = spriteIndex;
}

void Environment::manageAI()
{
	// Check interval and add a new AI if necessary
	if(Timer::Instance()->getElapsedTime() % ADD_AI_INTERVAL == 0)
	{
		addAI();
	}

	// Update all AI positions
	updateAI();
}

void Environment::addAI()
{
	// Position
	float posY = getAIStartY();
	float posX = getAIStartX();

	// A new sprite is dynamically created
	AI *a = new AI;
	a -> createSprite(AI_SPRITE_START_INDEX + AIListSize, "Resources/carMoving.png");
	a -> setPosition(posX, posY);

	// AGK functions
	agk::SetSpriteDepth(AI_SPRITE_START_INDEX + AIListSize, SPRITE_AI_DEPTH);
	agk::SetSpriteAnimation(AI_SPRITE_START_INDEX + AIListSize, VEHICLE_FRAME_WIDTH, 
		                    VEHICLE_FRAME_HEIGHT, VEHICLE_FRAMES);
	agk::PlaySprite(AI_SPRITE_START_INDEX + AIListSize);

	AIListSize++;
	
	// A new node is created in the linked list
	ptr newptr;
	newptr = new AINode;
	newptr -> sprite = a;
	newptr -> next = NULL;

	if(AIHead == NULL)
	{
		AIHead = newptr;
	}
	else
	{
		AITailItem -> next = newptr;
	}

	AITailItem = newptr;
}

// Update AI positions based on environment position
// and their speed.
void Environment::updateAI()
{
	ptr cur = AIHead;

	float x = getAIStartX(), y = getAIStartY();

	while(cur != NULL)
	{
		if(cur->sprite->isActive() == true)
		{
			cur->sprite->advancePosition(x, y);
		}

		cur = cur -> next;
	}
}

int Environment::getAIAmount()
{
	return AIListSize;
}

int Environment::getTimeRemaining()
{
	// gets the total map time - the current elapsed inplay time
	return map.getTime() - Timer::Instance()->getElapsedTimeSec();
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

float Environment::getAIStartX()
{
	return positionX + map.getAIStartPosX();
}

float Environment::getAIStartY()
{
	return positionY + map.getAIStartPosY();
}