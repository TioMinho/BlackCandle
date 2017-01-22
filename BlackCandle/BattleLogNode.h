#ifndef _BATTLELOGNODE_H_
#define _BATTLELOGNODE_H_

#include <SFML\Graphics.hpp>
#include "LogNode.h"

// BattleLogNode - 0923j0ieofiameofae
class BattleLogNode : public LogNode
{
// -------- Attributes ---------- 
private:
	sf::Vector2f position;

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Default Constructor
	BattleLogNode() {
		element = "";
		next = NULL;
	}

	// Custom Constructor
	BattleLogNode(std::string text, sf::Vector2f position) {
		element = text;
		this->position = position;
		next = NULL;
	}

	// GETTERS
	sf::Vector2f getPosition() {
		return this->position;
	}

	// SETTERS
	void setPosition(sf::Vector2f position) {
		this->position = position;
	}

// ------------------------------
};

#endif