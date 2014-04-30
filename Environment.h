#pragma once
#include "template.h"
#include <string>
#include "track.h"
#include "Vehicle.h"
#include "Globals.h"
#include "AI.h"

/***********************/
/* AI LINKED LIST      */
/***********************/
typedef struct AINode* ptr;

struct AINode{
	AI *sprite;
	ptr next;
};

class Environment
{
private:
	// Track object currently assigned to environment
	Track map;

	// The position of the environment with respect to the
	// user viewport
	float positionX;
	float positionY;

	// Final index in the assets list
	int g_assetsEndIndex;

	// Tile and object rows currently loaded in to the environment
	int tileRows;
	int tileCols;
	int objectRows;
	int objectCols;

	// Pointers for the AI list
	ptr AIHead;
	ptr AITailItem;
	int AIListSize;

	void loadTiles();
	void createSprites();
	void manageAI();
	void addAI();
	void updateAI();

public:
	Environment();
	~Environment(void);

	// Mutators
	void processTrack();
	void updateEnvironment(float x, float y, float);
	void setPositionX(float posX);
	void setPositionY(float posY);
	void draw();
	void setTrack(Track t);

	// Accessors
	int getAIAmount();
	float getPositionX();
	float getPositionY();
	float getAIStartX();
	float getAIStartY();
	int getTimeRemaining();
};
