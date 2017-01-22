#ifndef _TILE_H_
#define _TILE_H_

#include <SFML\Graphics.hpp>

// Tile - class responsable for designing the
// areas of a Stage where Collisions can happen,
// as much as for indicates the Mechanics proprieties.
class Tile
{
// -------- Attributes ---------- 
private:
	int tileClass;
	sf::Vector2i size;
	sf::Vector2f position;

// ------------------------------
// --------- Methods ------------
public:
	// Constructors
	//Standart
	Tile()
	{
		// Tile Class-Collision initialization
		tileClass = 0;

		// Collision Tile size and position initialization
		size = sf::Vector2i(32, 32);
		position = sf::Vector2f(0, 0);
	}

	Tile(int tileClass, int size, sf::Vector2f position)
	{
		// Tile Class-Collision initialization
		this->tileClass = tileClass;

		// Collision Tile size and position initialization
		this->size = sf::Vector2i(size, size);
		this->position = position;
	}

	// GETTERS
	int getClass() {
		return tileClass;
	}

	sf::Vector2i getSize() {
		return size;
	}

	// SETTERS
	void setClass(int tileClass) {
		this->tileClass = tileClass;
	}

	void setSize(int width, int height) {
		this->size = sf::Vector2i(width, height);
	}

	void setPosition(float x, float y) {
		this->position = sf::Vector2f(x, y);
	}

	// Special Collision Getters
	float top() {
		return position.y;
	}

	float bottom() {
		return position.y + size.y;
	}

	float left() {
		return position.x;
	}

	float right() {
		return position.x + size.x;
	}

// ------------------------------
};

#endif