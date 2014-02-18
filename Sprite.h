#ifndef SPRITE_H
#define SPRITE_H
#include <iostream>

using namespace std;

class Sprite{

private:
	int spriteIndex;
	string imageFile;

	Sprite(){} // Private default constructor

public:
	Sprite(int index, string image);
	void createSprite(int index, string image);
	void setImage(int index);
	void setX(float posX);
	void setY(float posY);
	int getSpriteIndex();
	string getImageFile();
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	float getCenterX();
	float getCenterY();
};

#endif