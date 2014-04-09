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

void Sprite::setImage(int index)
{

}

void Sprite::deleteSprite()
{
	agk::DeleteSprite(spriteIndex);
}

void Sprite::setColor(char color)
{
	// 'R' for RED
	// 'G' for GREEN
	// 'B' FOR BLUE
	switch(color)
	{
		case 'R': 
			agk::SetSpriteColor(spriteIndex, 255, 0, 0, 255);
			break;
		case 'G':
			agk::SetSpriteColor(spriteIndex, 50, 205, 50, 255);
			break;
		default:
			agk::SetSpriteColor(spriteIndex, 0, 199, 255, 255);
	}
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
	return agk::GetSpriteWidth(spriteIndex);
}

float Sprite::getHeight(){
	return agk::GetSpriteHeight(spriteIndex);
}

float Sprite::getCenterX(){
	return getWidth() / 2;
}

float Sprite::getCenterY(){
	return getHeight() / 2;
}
