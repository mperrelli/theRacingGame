#ifndef SPRITE_H
#define SPRITE_H
#include <iostream>

using namespace std;

class Sprite{

protected:
	int spriteIndex;
	int imageIndex;

public:
	Sprite();
	void createSprite();
	void deleteSprite();
	int getSpriteIndex();
	int getImageIndex();
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	float getCenterX();
	float getCenterY();
	void setVisible(bool value);
	void setImage(int index);
	void setX(float posX);
	void setY(float posY);
	void setValues(int spriteIndex, int imageIndex);
};

#endif