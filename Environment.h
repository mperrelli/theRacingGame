#pragma once

class Environment
{
private:
	int difficulty, type;
	float positionX, positionY;

public:
	Environment(int difficulty, int type);
	~Environment(void);

	void generateTrack(int type);
	void addObstacles(int difficulty);
	void updateEnvironment();
	void setPositionX(float posX);
	void setPositionY(float posY);
	
	float getPositionX();
	float getPositionY();
};
