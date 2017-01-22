#ifndef _LOGNODE_H_
#define _LOGNODE_H_

#include <iostream>
#include <string>

// LogNode - owenaoskdinoalskignaoksd
class LogNode
{
// -------- Attributes ---------- 
protected:
	std::string element;
	LogNode* next;

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Default Constructor
	LogNode() 
	{
		element = "";
		next = NULL;
	}

	// Custom Constructor
	LogNode(std::string content)
	{
		element = content;
		next = NULL;
	}

	// GETTERS
	std::string getElement() {
		return element;
	}

	LogNode* getNext() {
		return next;
	}

	virtual sf::Vector2f getPosition(){ 
		std::cout << "ERRO" << std::endl;
		return sf::Vector2f(0, 0);
	}
	
	// SETTERS
	void setElement(std::string content) {
		element = content;
	}

	void setNext(LogNode* next) {
		this->next = next;
	}

// ------------------------------
};

#endif