#include "Sprite.h"
#include "template.h"
#include <iostream>

using namespace std;
using namespace AGK;

Sprite::Sprite(int index, string image){
	spriteIndex = index;
	imageFile = image;
}

void Sprite::createSprite(int index, string image){
	agk::CreateSprite(index, image);
}

void Sprite::setImage(int index){

}

void Sprite::setX(float posX){
	agk::SetSpriteX(spriteIndex, posX);
}

void Sprite::setY(float posY){
	agk::SetSpriteY(spriteIndex, posY);
}

int Sprite::getSpriteIndex(){
	return this->spriteIndex;
}

string Sprite::getImageFile(){
	return this->imageFile;
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
