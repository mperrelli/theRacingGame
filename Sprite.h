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
	void createSprite();
	void deleteSprite();
	void setVisible(bool value);
	void setColor(char color);
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