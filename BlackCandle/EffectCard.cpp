// **********************************************************
// ********* IMPLEMENTATION OF THE EFFECTCARD CLASS *********
// **********************************************************

#include "EffectCard.h"
#include <fstream>
#include <sstream>

using namespace std;

// CONSTRUCTOR
// Standart Constuctor
EffectCard::EffectCard()
{
	// Standart initialization
	category = factor = 0;
}

// Custom Constructor
EffectCard::EffectCard(int cardID)
{
	// Initializing the general attributes
	load(cardID);

	// We open the respective EffectCard ".bin" accordingly 
	// with its ID
	ifstream file("BlackCandle/Cards/EffectCards/" + to_string(cardID) + ".bin", ios::in | ios::binary);

	// We create two strings: one for getting the line (all the ".bin" content) and another
	// to separate the attributes
	string line, value;

	// We import the ".bin" to "line"
	getline(file, line);

	// And so, we create a Stringstream to read the attributes
	stringstream stream(line);

	// We read the category
	getline(stream, value, ';');
	category = atoi(value.c_str());

	// We read the level
	getline(stream, value, ';');
	level = atoi(value.c_str());

	// We read the factor
	getline(stream, value, ';');
	factor = atoi(value.c_str());

	// And we close the file
	file.close();
}

// GETTERS
int EffectCard::getCategory() {
	return category;
}

int EffectCard::getLevel() {
	return level;
}

int EffectCard::getFactor() {
	return factor;
}

// SETTERS
void EffectCard::setCategory(int category) {
	this->category = category;
}

void EffectCard::setLevel(int level) {
	this->level = level;
}

void EffectCard::setFactor(int factor) {
	this->factor = factor;
}

// Main method to calculate the modifier of the Effect Card
// based on its category
int EffectCard::applyEffect(int atribute)
{
	int thirdDigit = category / 100;

	if (thirdDigit == 0)
		return atribute + factor;
	else if (thirdDigit == 1)
		return atribute - factor;
	else if (thirdDigit == 2)
		return atribute * (1 + factor * 0.1);
	else if (thirdDigit == 3)
		return atribute * (1 - factor * 0.1);
	else
		return atribute;
}

// This method simply indicates in which attribute
// will this Card has effect
// This is the chart:
// 1 - Strength      | 2 - Defense            | 3 - Agility              | 4 - Dexterity
// 5 - Intelligence  | 6 - Resistance         | 7 - Luck                 | 8 - HP
// 9 - MP            | 10 - Damage (Received) | 11 - Damage (Given)
// 12 - Attack Speed | 13 - Casting Speed     | 14 - Experience Received
int EffectCard::getAttribute() {
	return category % 100;
}