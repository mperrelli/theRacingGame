#pragma once
#include "template.h"
#include <string>
#include "track.h"
#include "Vehicle.h"
#include "Globals.h"
#include "AI.h"
using namespace std;

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
	Track map;

	float positionX;
	float positionY;

	float AIPosX;
	float AIPosY;

	int g_assetsEndIndex;

	int tileRows;
	int tileCols;
	int objectRows;
	int objectCols;

	ptr AIHead;
	ptr AITailItem;
	int AIListSize;

	int timer;
	int addAIInterval;

	void loadTiles();
	void createSprites();
	void manageAI();
	void addAI();
	void updateAI();

public:
	Environment();
	~Environment(void);

	void processTrack();
	void updateEnvironment(float x, float y, float);
	void setPositionX(float posX);
	void setPositionY(float posY);
	void draw();
	void setTrack(Track t);
	int getTime();
	int getAIAmount();

	float getPositionX();
	float getPositionY();
	float getAIStartX();
	float getAIStartY();
};
