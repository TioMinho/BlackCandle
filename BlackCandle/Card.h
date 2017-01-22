#ifndef _CARD_H_
#define _CARD_H_

#include <iostream>
#include <string>

// Card - Base Class for all the classes
// of Cards in the Game
class Card
{
// -------- Attributes ---------- 
protected:
	int cardID;						// Card's identification by number
	std::string name;				// Card's name
	std::string description;		// Descriptions of the Card's effects
	int tradeValue;					// Sell/Buy value of the Card
	bool equipped;					// Indicates if the card is equipped

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Standart Constructor
	Card();

	// Custom Constructor #01
	Card(int cardID);

	// Custom Constructor #02
	Card(int cardID, const char* cardName, const char* description, int tradeValue);

	// Main Method to Load the Card's Information from a ".bin" file
	void load(int cardID);

	// GETTERS
	int getID();
	std::string getName();
	std::string getDescription();
	int getValue();
	bool isEquipped();

	// SETTERS
	void setID(int cardID);
	void setName(const char* name);
	void setDescription(const char* description);
	void setValue(int tradeValue);
	void equip();
	void unequip();
		
// ------------------------------
};

#endif