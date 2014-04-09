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

void Sprite::setValues(int sIndex, int	iIndex)
{
	spriteIndex = sIndex;
	imageIndex = iIndex;
}

void Sprite::createSprite()
{
	agk::CreateSprite(spriteIndex, imageIndex);
}

void Sprite::setVisible(bool value)
{
	if(value)
		agk::SetSpriteVisible(spriteIndex, 1);
	else
		agk::SetSpriteVisible(spriteIndex, 0);
}

void Sprite::deleteSprite()
{
	agk::DeleteSprite(spriteIndex);
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
	return tspriteIndex;
}

int Sprite::getImageIndex()
{
	return imageIndex;
}

float Sprite::getX()
{
	return agk::GetSpriteX(spriteIndex);
}

float Sprite::getY()
{
	return agk::GetSpriteY(spriteIndex);
}

float Sprite::getWidth()
{
	return agk::GetSpriteWidth(spriteIndex);
}

float Sprite::getHeight()
{
	return agk::GetSpriteHeight(spriteIndex);
}

float Sprite::getCenterX()
{
	return getWidth() / 2;
}

float Sprite::getCenterY()
{
	return getHeight() / 2;
}
