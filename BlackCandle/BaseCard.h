#ifndef _BASECARD_H_
#define _BASECARD_H_

#include <SFML\Graphics.hpp>
#include "Card.h"
#include "BaseNode.h"

// BaseCard - Class that represents the Cards
// responsable for designing the Structure where
// the Player can equip his cards
class BaseCard : public Card
{
// -------- Attributes ---------- 	
private:
	// BaseCard's Stats Growth Rate
	int strength;
	int defense;
	int agility;
	int dexterity;
	int intelligence;
	int resistance;
	int luck;

	// BaseCard's Structure
	int spellSlots;			// Represents the quantity of Spell slots available
	BaseNode* center;		// The center Node of the entire structure

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Standart Constructor
	BaseCard();

	// Custom Constructor
	BaseCard(int cardID);

	// GETTERS
	int getGrowthRate(int statusCode);
	int getSpellSlots();
	BaseNode* getCenter();

	// Method used to Load the Structure of the Basecard
	// This method will only be used when a Basecard is being equipped
	void loadStructure();

	// This recursive method will destroy all the BaseCard's Data Structure
	// from preventing memory leaks
	void clearStructure();		// This is the interface
	void clearStructure(BaseNode* aux, BaseNode* previous, bool start, std::vector<BaseNode*> *trashcan);

	// Main recursive method to apply modifiers in any attribute
	// based on its code.
	int modify(int attribute, int attributeNumber);		// This is the interface
	int modify(int attribute, int attributeNumber, BaseNode* aux);

	// This method can, recursively, provides position and
	// texture to a Sprite so the Structure can have a graphic
	// representation based on it's organization
	void render(sf::RenderWindow* mainWindow, float posX, float posY);	// This is the interface
	void render(sf::RenderWindow* gameWindow, float posX, float posY, BaseNode* aux, BaseNode* previous,
		sf::Sprite* cardSprite, sf::RectangleShape* line, bool start);

// ------------------------------
};

#endif