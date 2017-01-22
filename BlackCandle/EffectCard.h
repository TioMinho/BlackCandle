#ifndef _EFFECTCARD_H_
#define _EFFECTCARD_H_

#include "Card.h"
#include <iostream>
#include <string>

class EffectCard : public Card
{
// -------- Attributes ---------- 
private:
	int category;			// Defines how the Card works
	int level;				// Card's level (indicates how many lines it needs)
	int factor;				// Used for calculate the intensity of the Card's effects

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTOR
	// Standart Constuctor
	EffectCard();

	// Custom Constructor
	EffectCard(int cardID);

	// GETTERS
	int getCategory();
	int getLevel();
	int getFactor();

	// SETTERS
	void setCategory(int category);
	void setLevel(int level);
	void setFactor(int factor);

	// Main method to calculate the modifier of the Effect Card
	// based on its category
	int applyEffect(int atribute);

	// This method simply indicates in which attribute
	// will this Card has effect
	// This is the chart:
	// 1 - Strength      | 2 - Defense            | 3 - Agility              | 4 - Dexterity
	// 5 - Intelligence  | 6 - Resistance         | 7 - Luck                 | 8 - HP
	// 9 - MP            | 10 - Damage (Received) | 11 - Damage (Given)
	// 12 - Attack Speed | 13 - Casting Speed     | 14 - Experience Received
	int getAttribute();

// ------------------------------
};

#endif