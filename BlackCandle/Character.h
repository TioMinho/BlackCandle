#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <SFML/Graphics.hpp>

// Character - Base Class for most of the Game's
// representative Characters and the Protagonist
// itself
class Character
{
// -------- Attributes ---------- 
protected:
	// The Basic for Rendering
	// Sprite and Texture
	sf::Sprite sprite;
	sf::Texture spriteText;

	// Size Control - For Animation
	sf::Vector2i size;
	sf::Vector2i frame;

	// The Basics of Cinematics
	sf::Vector2f movement;
	sf::Vector2f speed;
	sf::Clock jumpTrigger;
	int jumpLimit;

// ------------------------------
// --------- Methods ------------
public:
	// CONSTRUCTORS
	// Standart
	Character();
	// Custom
	Character(std::string spriteName, int width, int height, int moveSpeed, int jumpSpeed, int jumpLimit);

	// GETTERS
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getCenter();
	sf::Vector2i getSize();
	sf::Vector2i getFrame();
	sf::Vector2f getMovement();
	sf::Vector2f getSpeed();
	int getJumpLimit();

	// SETTERS
	void setSprite(std::string spriteName);
	void setSize(int width, int height);
	void setFrame(int frameX, int frameY);
	void setMoveSpeed(int moveSpeed);
	void setJumpSpeed(int jumpSpeed);
	void setJumpLimit(int milliSeconds);
	void setPosition(float x, float y);

	// ****************************** TESTES DE CINEMATICS

	void doJump();
	void doFall(float rate);
	void onGround();
	void walkLeft();
	void walkRight();
	void stand();
	void execMovement();

	// ***************************************************

// ------------------------------
};

#endif