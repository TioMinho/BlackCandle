// *****************************************************
// ******* IMPLEMENTATION OF THE CHARACTER CLASS *******
// *****************************************************

#include "Character.h"
#include <iostream>

// Standart Constructor
Character::Character()
{
	// *********************************** TEST *****************************************
	// Sprite initialization
	spriteText.loadFromFile("BlackCandle/Characters/main.png");
	sprite.setTexture(spriteText);

	// Size and Frame initialization
	size = sf::Vector2i(69, 57);
	frame = sf::Vector2i(0, 0);

	// Cinematics initialization
	movement = sf::Vector2f(0, 0);
	speed = sf::Vector2f(0.5, 3);
	this->jumpLimit = 100;
	jumpTrigger.restart();
	// *************************************************************************************
}

// Custom Constructor
Character::Character(std::string spriteName, int width, int height, int moveSpeed, int jumpSpeed, int jumpLimit)
{
	// Sprite initialization
	spriteText.loadFromFile("BlackCandle/Characters/" + spriteName + ".png");
	sprite.setTexture(spriteText);

	// Size and Frame initialization
	size = sf::Vector2i(width, height);
	frame = sf::Vector2i(0, 0);

	// Cinematics initialization
	movement = sf::Vector2f(0, 0);
	speed = sf::Vector2f(moveSpeed, jumpSpeed);
	this->jumpLimit = jumpLimit;
	jumpTrigger.restart();
}

// GETTERS
sf::Sprite Character::getSprite(){
	return sprite;
}

sf::Vector2f Character::getPosition() {
	return sprite.getPosition();
}

sf::Vector2f Character::getCenter() {
	return sf::Vector2f(sprite.getPosition().x + size.x / 2.0, sprite.getPosition().y + size.y / 2.0);
}

sf::Vector2i Character::getSize(){
	return size;
}

sf::Vector2i Character::getFrame(){
	return frame;
}

sf::Vector2f Character::getMovement(){
	return movement;
}

sf::Vector2f Character::getSpeed(){
	return speed;
}

int Character::getJumpLimit(){
	return jumpLimit;
}

// SETTERS
void Character::setSprite(std::string spriteName)
{
	spriteText.loadFromFile("BlackCandle/" + spriteName + ".png");
	sprite.setTexture(spriteText);
}

void Character::setSize(int width, int height){
	size = sf::Vector2i(width, height);
}

void Character::setFrame(int frameX, int frameY) {
	frame = sf::Vector2i(frameX, frameY);

	sprite.setTextureRect(sf::IntRect(frame.x * size.x, frame.y * size.y, size.x, size.y));
}

void Character::setMoveSpeed(int moveSpeed) {
	speed.x = moveSpeed;
}

void Character::setJumpSpeed(int jumpSpeed) {
	speed.y = jumpSpeed;
}

void Character::setJumpLimit(int milliSeconds) {
	jumpLimit = milliSeconds;
}

void Character::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

// ****************************** TESTES DE CINEMATICS

void Character::doJump() {
	if (jumpTrigger.getElapsedTime().asMilliseconds() <= jumpLimit)
		movement.y = -speed.y;
}

void Character::doFall(float rate) {
	if (movement.y < 5)
		movement.y += rate;
}

void Character::onGround() {
	movement.y = 0;
	jumpTrigger.restart();
}

void Character::walkLeft() {
	movement.x = -speed.x;
}

void Character::walkRight() {
	movement.x = speed.x;
}

void Character::stand() {
	movement.x = 0;
}

void Character::execMovement() {
	sprite.move(movement);
}

// ***************************************************