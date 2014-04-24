#pragma once
#include "template.h"
#include <string>
#include "track.h"
#include "Vehicle.h"
#include "Globals.h"
using namespace std;

class Environment
{
private:
	Track map;

	float positionX;
	float positionY;

	int g_assetsEndIndex;

	int tileRows;
	int tileCols;
	int objectRows;
	int objectCols;

	void loadTiles();
	void createSprites();

public:
	Environment();
	~Environment(void);

	void processTrack();
	void updateEnvironment(float x, float y, float);
	void setPositionX(float posX);
	void setPositionY(float posY);
	void draw();
	void setTrack(Track t);

	float getPositionX();
	float getPositionY();
};
