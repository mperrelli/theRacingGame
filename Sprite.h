#ifndef SPRITE_H
#define SPRITE_H
#include <iostream>

using namespace std;

class Sprite{

private:
	int spriteIndex;
	int imageIndex;

public:
	Sprite();
	Sprite(int index, int image);
	void createSprite(int index, int image);
	void setImage(int index);
	void setX(float posX);
	void setY(float posY);
	int getSpriteIndex();
	int getImageFile();
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	float getCenterX();
	float getCenterY();
};

#endif