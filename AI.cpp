#include <cstdlib>
#include "template.h"
#include "AI.h"
#include "Log.h"

AI::AI() : Sprite()
{
	setSpeed();
	direction = EAST;
	lastTrackPiece = -1;
	offset = agk::Random(5, 10);
}

AI::AI(int sIndex, string image, float x, float y) : Sprite(sIndex, image)
{
	setSpeed();
	direction = EAST;
	lastTrackPiece = -1;
	offset = agk::Random(5, 10);
}

void AI::setSpeed()
{
	speed = rand() % 9 + 6;
}

float AI::getEnvPosY()
{
	return posY;
}

float AI::getEnvPosX()
{
	return posX;
}

void AI::advancePosition(float x, float y, int timer)
{
	// Get surface
	int sIndex = agk::GetSpriteHitGroup(SPRITE_GROUP_TRACK , getCenterX(), getCenterY());

	int surface = agk::GetSpriteImageID(sIndex);

	float deltaX = 0, deltaY = 0;

	// Respond to surface
	if(timer % offset == 0)
	{
		if(surface == TRACK_H && direction == EAST)
		{
			deltaX += speed;
			lastTrackPiece = TRACK_H;
		}
		else if(surface == TRACK_H && direction == WEST)
		{
			deltaX -= speed;
			lastTrackPiece = TRACK_H;
		}
		else if(surface == TRACK_V && direction == NORTH)
		{
			deltaY -= speed;
			lastTrackPiece = TRACK_V;
		}
		else if(surface == TRACK_V && direction == SOUTH)
		{
			deltaY += speed;
			lastTrackPiece = TRACK_V;
		}
		else if(surface == TRACK_TURN_WS && direction == EAST)
		{
			deltaY += speed;
			direction = SOUTH;
			lastTrackPiece = TRACK_TURN_WS;
			turnCarTowards(SOUTH);
		}
		else if(surface == TRACK_TURN_WS && direction == NORTH)
		{
			deltaX -= speed;
			direction = WEST;
			lastTrackPiece = TRACK_TURN_WS;
			turnCarTowards(WEST);
		}
		else if(surface == TRACK_TURN_WN && direction == EAST)
		{
			deltaY -= speed;
			direction = NORTH;
			lastTrackPiece = TRACK_TURN_WN;
			turnCarTowards(NORTH);
		}
		else if(surface == TRACK_TURN_WN && direction == SOUTH)
		{
			deltaX += speed;
			direction = WEST;
			lastTrackPiece = TRACK_TURN_WN;
			turnCarTowards(WEST);
		}
		else if(surface == TRACK_TURN_ES && direction == WEST)
		{
			deltaY += speed;
			direction = SOUTH;
			lastTrackPiece = TRACK_TURN_ES;
			turnCarTowards(SOUTH);
		}
		else if(surface == TRACK_TURN_ES && direction == NORTH)
		{
			deltaX += speed;
			direction = EAST;
			lastTrackPiece = TRACK_TURN_ES;
			turnCarTowards(EAST);
		}
		else if(surface == TRACK_TURN_EN && direction == WEST)
		{
			deltaY -= speed;
			direction = NORTH;
			lastTrackPiece = TRACK_TURN_EN;
			turnCarTowards(NORTH);
		}
		else if(surface == TRACK_TURN_EN && direction == SOUTH)
		{
			deltaX += speed;
			direction = EAST;
			lastTrackPiece = TRACK_TURN_EN;
			turnCarTowards(EAST);
		}
	}

	if(deltaX == 0 && deltaY == 0)
	{
		switch(direction)
		{
		case SOUTH:
			
			deltaY += speed;

			break;
		case NORTH:

			deltaY -= speed;

			break;
		case EAST:

			deltaX += speed;

			break;
		case WEST:

			deltaX -= speed;

			break;
		}
	}

	posX += deltaX;
	posY += deltaY;

	setPosition(x + posX, y + posY);
}

void AI::turnCarTowards(int dir)
{
	switch(dir)
	{
	case EAST:
		agk::SetSpriteAngle(getSpriteIndex(), 0);
		break;
	case SOUTH:
		agk::SetSpriteAngle(getSpriteIndex(), 90);
		break;
	case WEST:
		agk::SetSpriteAngle(getSpriteIndex(), 180);
		break;
	case NORTH:
		agk::SetSpriteAngle(getSpriteIndex(), 270);
		break;
	}
}