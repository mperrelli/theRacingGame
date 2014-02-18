#include "Sprite.h"
#include <iostream>

using namespace std;

Sprite::Sprite(int index, string image){
	spriteIndex = index;
	imageFile = image;
}

void Sprite::createSprite(int index, string image){

}

void Sprite::setImage(int index){

}

void Sprite::setX(float posX){
	SetSpriteX(spriteIndex, posX);
}

void Sprite::setY(float posY){
	SetSpriteY(spriteIndex, posY);
}

int Sprite::getSpriteIndex(){
	return this->spriteIndex;
}

string Sprite::getImageFile(){
	return this->imageFile;
}

float Sprite::getX(){
	return GetSpriteX(spriteIndex);
}

float Sprite::getY(){
	return GetSpriteY(spriteIndex);
}

float Sprite::getWidth(){

}

float Sprite::getHeight(){

}

float Sprite::getCenterX(){
	getWidth() / 2;
}

float Sprite::getCenterY(){
	getHeight() / 2;
}
