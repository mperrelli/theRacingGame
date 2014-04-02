#include "Sprite.h"
#include "template.h"
#include <iostream>

using namespace std;
using namespace AGK;


Sprite::Sprite()
{
	spriteIndex = NULL;
	imageIndex = NULL;
}

Sprite::Sprite(int index, int image)
{
	spriteIndex = index;
	imageIndex = image;
}

void Sprite::createSprite(int index, int image)
{
	agk::CreateSprite(index, image);
}

void Sprite::setImage(int index)
{

}

void Sprite::setX(float posX)
{
	agk::SetSpriteX(spriteIndex, posX);
}

void Sprite::setY(float posY)
{
	agk::SetSpriteY(spriteIndex, posY);
}

int Sprite::getSpriteIndex()
{
	return this->spriteIndex;
}

int Sprite::getImageFile(){
	return this->imageIndex;
}

float Sprite::getX(){
	return agk::GetSpriteX(spriteIndex);
}

float Sprite::getY(){
	return agk::GetSpriteY(spriteIndex);
}

float Sprite::getWidth(){

}

float Sprite::getHeight(){

}

float Sprite::getCenterX(){
	//getWidth() / 2;
}

float Sprite::getCenterY(){
	//getHeight() / 2;
}
