#pragma once
#include "vehicle.h"

class AI : public Sprite{

public:

	static const int NORTH = 1;
	static const int WEST = 2;
	static const int SOUTH = 3;
	static const int EAST = 4;

	int direction;
	int lastTrackPiece;
	int speed;
	int offset;
	float posX, posY;
	void setSpeed();
	void advancePosition(float x, float y, int timer);
	void turnCarTowards(int dir);
	
public:
	AI();
	AI(int sIndex, string image, float x, float y);

	float getEnvPosY();
	float getEnvPosX();

	~AI();
};
