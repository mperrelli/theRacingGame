#pragma once

class Environment
{
private:
	static const int LINEAR = 1;
	static const int CYCLICAL = 2;

	static const int TRACK_TILE_SIZE = 128;
	static const int OBSTACLE_TILE_SIZE = 32;

	static const int LINEAR_ROWS = 5;
	static const int LINEAR_COLS = 10;

	static const int TRACK_ATLAST_START_INDEX = 50;

	// Constants for the image indecies
	static const int GRASS         = 10;
	static const int TRACK         = 11;
	static const int TRACK_TURN    = 12;
	static const int BARRIER       = 13;
	static const int BARRIER_TURN  = 14;

	int difficulty;
	int type;

	float positionX;
	float positionY;

	int * trackAtlas;

	int tileRows;
	int tileCols;

	void loadTiles();
	void createSprites();

public:
	Environment(int difficulty, int type);
	~Environment(void);

	void generateTrack(int type);
	void updateEnvironment();
	void setPositionX(float posX);
	void setPositionY(float posY);
	void draw();

	float getPositionX();
	float getPositionY();
};
