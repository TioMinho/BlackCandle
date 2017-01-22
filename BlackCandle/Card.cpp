// ****************************************************
// ********* IMPLEMENTATION OF THE CARD CLASS *********
// ****************************************************

#include "Card.h"
#include <fstream>
#include <sstream>

using namespace std;

// CONSTRUCTORS
// Standart Constructor
Card::Card()
{
	cardID = 0;
	name = "Empty";
	description = "Empty card";
	tradeValue = 0;
	equipped = false;
}

// Custom Constructor #01
Card::Card(int cardID)
{
	load(cardID);
}

// Custom Constructor #02
Card::Card(int cardID, const char* cardName, const char* description, int tradeValue)
{
	this->cardID = cardID;
	this->name = cardName;
	this->description = description;
	this->tradeValue = tradeValue;
}

// Main Method to Load the Card's Information from a ".bin" file
void Card::load(int cardID)
{
	// The Stream object to read the "index.bin" file
	ifstream file("BlackCandle/Cards/index.bin", ios::in | ios::binary);

	// The string to receive a line and a auxiliar string to receive its parts
	string line, value;

	// We read a quantity of lines equals to the Card's ID
	for (int i = 0; i < cardID; i++)
		getline(file, line);

	// The Stringstream used to separate the data
	stringstream stream(line);

	// The Card's very ID
	getline(stream, value, ';');
	this->cardID = atoi(value.c_str());

	// The Card's Name
	getline(stream, value, ';');
	name = value;

	// The Card's Description
	getline(stream, value, ';');
	description = value;

	// The Card's Trade Value
	getline(stream, value, ';');
	tradeValue = atoi(value.c_str());

	// And, in the end, we close the file
	file.close();
}

// GETTERS
int Card::getID() {
	return cardID;
}

string Card::getName() {
	return name;
}

string Card::getDescription() {
	return description;
}

int Card::getValue() {
	return tradeValue;
}

bool Card::isEquipped() {
	return equipped;
}

// SETTERS
void Card::setID(int cardID) {
	this->cardID = cardID;
}

void Card::setName(const char* name) {
	this->name = name;
}

void Card::setDescription(const char* description) {
	this->description = description;
}

void Card::setValue(int tradeValue) {
	this->tradeValue = tradeValue;
}

void Card::equip() {
	equipped = true;
}

void Card::unequip() {
	equipped = false;
}