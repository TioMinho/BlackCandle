// ********************************************************
// ********* IMPLEMENTATION OF THE BASECARD CLASS *********
// ********************************************************

#include "BaseCard.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// CONSTRUCTORS
// Standart Constructor
BaseCard::BaseCard() {
	// Spell Slots initialization
	spellSlots = 0;

	// Center card initialization
	center = NULL;
}

// Custom Constructor
BaseCard::BaseCard(int cardID)
{
	// Initializing the general attributes
	load(cardID);

	// Create the Base Structure
	// First, open the ".bin" file correspondent of the Card
	ifstream file("BlackCandle/Cards/BaseCards/" + to_string(cardID) + ".bin", ios::in | ios::binary);

	// Declaration of two strings: one for the line and another to hold the commands
	string line, value;

	// The line gets, first, all the BaseCards attributes
	getline(file, line);

	// We create a stringstream to separate this data
	stringstream stream(line);

	// First, we read the number of Spell Slots
	getline(stream, value, ';');
	spellSlots = atoi(value.c_str());

	// Then, all the Stats Growth Rate
	getline(stream, value, ';');
	strength = atoi(value.c_str());

	getline(stream, value, ';');
	defense = atoi(value.c_str());

	getline(stream, value, ';');
	agility = atoi(value.c_str());

	getline(stream, value, ';');
	dexterity = atoi(value.c_str());

	getline(stream, value, ';');
	intelligence = atoi(value.c_str());

	getline(stream, value, ';');
	resistance = atoi(value.c_str());

	getline(stream, value, ';');
	luck = atoi(value.c_str());

	// After all, we close the file
	file.close();
}

// GETTERS
int BaseCard::getGrowthRate(int statusCode) {
	if (statusCode == 1)
		return strength;
	else if (statusCode == 2)
		return defense;
	else if (statusCode == 3)
		return agility;
	else if (statusCode == 4)
		return dexterity;
	else if (statusCode == 5)
		return intelligence;
	else if (statusCode == 6)
		return resistance;
	else if (statusCode == 7)
		return luck;
	else
		return 0;
}

int BaseCard::getSpellSlots() {
	return spellSlots;
}

BaseNode* BaseCard::getCenter() {
	return center;
}

// Methos used to Load the Structure of the Basecard
// This method will only be used when a Basecard is being equipped
void BaseCard::loadStructure()
{
	// Create the Base Structure
	// First, open the ".bin" file correspondent of the Card
	ifstream file("BlackCandle/Cards/BaseCards/" + to_string(cardID) + ".bin", ios::in | ios::binary);

	// Declaration of two strings: one for the line and another to hold the commands
	string line, command;

	// The line gets, first, the general attributes
	getline(file, line);

	// So, we read the next line, that contains all the steps to build the Structure
	getline(file, line);

	// We create a stringstream to separate this data
	stringstream stream(line);

	// And the commands are taken. Those are the possible commands:
	// setNew -> this command creates a new slot. The bound number is expected with anoter getline
	// set -> this command close an existing bound. The bound number is expected with another getline
	// setCenter -> this command close an existing bound with the center reference. The bound number is expected with another getline.
	// back -> actual = previous.
	// foward -> previous = actual.
	// move -> moves the "actual" to a existing slot. The bound number is expected with another getline

	// The start:
	center = new BaseNode();
	BaseNode* actual = center, *previous = actual;

	while (getline(stream, command, ';'))
	{
		// We check the command and do the requested
		if (command == "setNew")
		{
			getline(stream, command, ';');

			actual->setBound(new BaseNode(), atoi(command.c_str()));
		}
		else if (command == "set")
		{
			getline(stream, command, ';');

			actual->setBound(previous, atoi(command.c_str()));
		}
		else if (command == "setCenter")
		{
			getline(stream, command, ';');

			actual->setBound(center, atoi(command.c_str()));
		}
		else if (command == "back")
		{
			actual = previous;
		}
		else if (command == "foward")
		{
			previous = actual;
		}
		else if (command == "move")
		{
			getline(stream, command, ';');

			actual = actual->getNode(atoi(command.c_str()));
		}
	}

	// After all, we close the file
	file.close();
}

// This methos will destroy all the BaseCard's Data Structure
// from preventing memory leaks
// This is the recursive method
void BaseCard::clearStructure(BaseNode* aux, BaseNode* previous, bool start, std::vector<BaseNode*> *trashcan)
{
	if (start && aux == center)
		return;

	// We go until reach any end
	for (int i = 0; i < 8; i++)
	{
		if (aux->getNode(i) != NULL && aux->getNode(i) != previous)
		{
			BaseNode* deleted = aux->getNode(i);
			clearStructure(deleted, aux, true, trashcan);

			bool isInsert = true;
			for (int j = 0; j < trashcan->size(); j++)
				if (trashcan->at(j) == deleted)
					isInsert = false;

			if (isInsert)
				trashcan->push_back(deleted);
		}
	}

	return;
}

// This is the interface
void BaseCard::clearStructure()
{
	std::vector<BaseNode*> trashcan;

	clearStructure(center, NULL, false, &trashcan);

	for (int i = 0; i < trashcan.size(); i++)
		delete(trashcan.at(i));
}

// Main method to apply modifiers in any attribute
// based on its code.
// This is the recursive method
int BaseCard::modify(int attribute, int attributeNumber, BaseNode* aux)
{
	// If the current card acts in this kind of attribute, we
	// modify it based on the EffectCard
	if (aux->getCard()->getAttribute() == attributeNumber)
		attribute = aux->getCard()->applyEffect(attribute);

	// And recursively check all the other Nodes
	for (int i = 0; i < 8; i++)
		if (aux->getNode(i) != NULL)
			attribute = modify(attribute, attributeNumber, aux->getNode(i));

	// And return the final result
	return attribute;
}

// This is the interface to the method above
int BaseCard::modify(int attribute, int attributeNumber)
{
	return modify(attribute, attributeNumber, center);
}

// This method can, recursively, provides position and
// texture to a Sprite so the Structure can have a graphic
// representation based on it's organization
// This is the recursive method
void BaseCard::render(sf::RenderWindow* gameWindow, float posX, float posY, BaseNode* aux, BaseNode* previous,
	sf::Sprite* cardSprite, sf::RectangleShape* line, bool start)
{
	// We verify if the structure is repeating itself
	if (aux == center && start)
		return;

	// We draw the cardSprite in the specific position
	cardSprite->setPosition(posX, posY);

	if (aux->getCard() != NULL) {
		cardSprite->setTextureRect(sf::IntRect(18 * 3, 0, 18, 22));
		gameWindow->draw(*cardSprite);
	}
	else {
		cardSprite->setTextureRect(sf::IntRect(0, 0, 18, 22));
		gameWindow->draw(*cardSprite);
	}

	// And check the recursion for all the others Nodes
	for (int i = 0; i < 8; i++)
	{
		if (aux->getNode(i) != NULL)
		{
			if (i == 0) {
				line->setPosition(posX + 9, posY);
				line->setRotation(0);

				gameWindow->draw(*line);

				if (aux->getNode(i) != previous)
					render(gameWindow, posX, posY - 32, aux->getNode(0), aux, cardSprite, line, true);
			}
			else if (i == 1) {
				line->setPosition(posX + 18, posY);
				line->setRotation(45);

				gameWindow->draw(*line);

				if (aux->getNode(i) != previous)
					render(gameWindow, posX + 28, posY - 32, aux->getNode(1), aux, cardSprite, line, true);
			}
			else if (i == 2) {
				line->setPosition(posX + 18, posY + 11);
				line->setRotation(90);

				gameWindow->draw(*line);

				if (aux->getNode(i) != previous)
					render(gameWindow, posX + 28, posY, aux->getNode(2), aux, cardSprite, line, true);
			}
			else if (i == 3) {
				line->setPosition(posX + 18, posY + 22);
				line->setRotation(135);

				gameWindow->draw(*line);

				if (aux->getNode(i) != previous)
					render(gameWindow, posX + 28, posY + 32, aux->getNode(3), aux, cardSprite, line, true);
			}
			else if (i == 4) {
				line->setPosition(posX + 9, posY + 22 + 10);
				line->setRotation(0);

				gameWindow->draw(*line);

				if (aux->getNode(i) != previous)
					render(gameWindow, posX, posY + 32, aux->getNode(4), aux, cardSprite, line, true);
			}
			else if (i == 5) {
				line->setPosition(posX - 10, posY + 22 + 10);
				line->setRotation(45);

				gameWindow->draw(*line);

				if (aux->getNode(i) != previous)
					render(gameWindow, posX - 28, posY + 32, aux->getNode(5), aux, cardSprite, line, true);
			}
			else if (i == 6) {
				line->setPosition(posX - 10, posY + 11);
				line->setRotation(90);

				gameWindow->draw(*line);

				if (aux->getNode(i) != previous)
					render(gameWindow, posX - 28, posY, aux->getNode(6), aux, cardSprite, line, true);
			}
			else if (i == 7) {
				line->setPosition(posX - 10, posY - 10);
				line->setRotation(135);

				gameWindow->draw(*line);

				if (aux->getNode(i) != previous)
					render(gameWindow, posX - 28, posY + 32, aux->getNode(7), aux, cardSprite, line, true);
			}
		}
	}

	return;
}

// This is the interface
void BaseCard::render(sf::RenderWindow* mainWindow, float posX, float posY)
{
	// We create the graphic objects that will be used in the Method
	sf::Sprite cardSprite;
	sf::Texture cardTexture;

	sf::RectangleShape lines(sf::Vector2f(2, -10));
	lines.setFillColor(sf::Color::White);

	bool start = false;

	// We load the card's texture and put it on the cardSprite
	cardTexture.loadFromFile("BlackCandle/Cards/icons/icons.png");
	cardSprite.setTexture(cardTexture);

	// And, so, we call the main method
	render(mainWindow, posX, posY, center, NULL, &cardSprite, &lines, start);
}
