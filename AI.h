#pragma once
#include "vehicle.h"

class AI : public Sprite{

public:
	int direction;
	int lastTrackPiece;
	int speed;
	int offset;
	int active;
	float posX, posY;
	void setSpeed();
	void advancePosition(float x, float y);
	void turnCarTowards(int dir);
	
public:
	AI();
	AI(int sIndex, string image, float x, float y);

	float getEnvPosY();
	float getEnvPosX();

	bool isActive();

	~AI();
};
