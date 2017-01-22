#ifndef _MENU_H_
#define _MENU_H_

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include "Keyboard.h"
#include "BaseCard.h"
#include "Timer.h"
#include "Player.h"

// Menu - this class contains all the elements
// needed to represent the Player's ingame Menu
// where he can see his stats and Cards
class Menu
{
// -------- Attributes ---------- 
private:
	// General Graphics
	int width, height;						// The Menu's geometric size
	sf::RectangleShape box;					// The Menu's box rectangle, both block and background
	sf::Texture menuTexture;				// The Menu's Texture
	sf::Text text;							// The Text used to describe the blocks
	sf::Font font;							// The Text's Font

	// General Logics
	bool active;							// Indicates either or not the Menu is open
	int majorOption, minorOption;			// Respectively, the Menu's Option and the Active Block's Option
	int selectionIndex;						// This variable is used to represent a index in some list from the Menu
	Timer timeControl;

	// BaseCard's Menu
	sf::Sprite cardViewer;					// Shows the active card during the selection
	sf::Texture cardTexture;				// The cardViewer's Texture
	sf::Vector2i offset;					// The BaseCard's Structure viewer offset
	int cardOffset;							// The Card's List viewer offset
	int spellIndex;							// The selected SpellCard index
	BaseNode* nodePointer;					// This pointer will be used to move across the Basecard Synapses
	EffectCard* effectPointer;				// This pointer will be used to select a Card from the inventory to the Synapses
	SpellCard* spellPointer;				// This pointer will be used to select a Card from the inventory to the Synapses
	BaseCard* basePointer;					// This pointer will be used to select a Card from the inventory to the Synapses

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Standart Constructor
	Menu();

	// Custom Constructor
	Menu(int width, int height);
	
	// Indicates if the Menu is open
	bool isOpen();

	// Open the Menu
	void open();

	// Close the Menu
	void close();

	// Set the Menu's width and heigth
	void setSize(sf::Vector2u size);

	// The Menu's Very Own Loop
	void menuLoop(sf::RenderWindow* gameWindow, Keyboard* keyboard, Player* player);

private:
	// Handles the User's Input
	void input(Player* player, Keyboard* keyboard);

	// Renders the entire Menu
	void render(sf::RenderWindow* gameWindow, Player* player);

	// This method creates an String based in one of the Player's Cards List
	// and return the entire list in form of this string
	void drawList(CardList* cardList, int cardType, sf::RenderWindow* gameWindow);

	// Method responsable for move tha pointer trough the Synapses
	bool moveSynapses();

	// Uses a pattern to fill the menu's background
	void renderBackground(float positionX, float positionY, int sizeX, int sizeY, sf::RenderWindow* gameWindow);

	// Creates a Box using the Texture to make a proper border
	void renderBlock(float positionX, float positionY, int sizeX, int sizeY, sf::RenderWindow* gameWindow);

// ------------------------------
};

#endif