// *********************************************************
// *********** IMPLEMENTATION OF THE MENU CLASS ************
// *********************************************************

#include "Menu.h"

using namespace std;

// CONSTRUCTORS
// Standart Constructor
Menu::Menu()
{
	// General Initialization ______________________________
	// Menu Size initialization
	width = 800;
	height = 600;

	// Box Texture initialization
	menuTexture.loadFromFile("BlackCandle/Menu/menu.png");
	box.setTexture(&menuTexture);

	// Font and Text initialization
	font.loadFromFile("BlackCandle/Menu/font.ttf");
	text.setFont(font);
	text.setColor(sf::Color::White);

	// General Logic Initialization
	active = false;
	majorOption = 0;
	selectionIndex = 1;
	timeControl.stop();

	// Equipment Menu ______________________________________
	// Rendering Offsets
	offset = sf::Vector2i(0, 0);
	cardOffset = 0;

	// CardViewer Texture
	cardTexture.loadFromFile("BlackCandle/Cards/icons/icons.png");
	cardViewer.setTexture(cardTexture);
}

// Standart Constructor
Menu::Menu(int width, int height)
{
	// General Initialization ______________________________
	// Menu Size initialization
	this->width = width;
	this->height = height;

	// Box Texture initialization
	menuTexture.loadFromFile("BlackCandle/Menu/menu.png");
	box.setTexture(&menuTexture);

	// Font and Text initialization
	font.loadFromFile("BlackCandle/Menu/font.ttf");
	text.setFont(font);
	text.setColor(sf::Color::White);

	// General Logic Initialization
	active = false;
	majorOption = 0;
	selectionIndex = 1;
	timeControl.stop();

	// Equipment Menu ______________________________________
	// Rendering Offsets
	offset = sf::Vector2i(0, 0);
	cardOffset = 0;

	// CardViewer Texture
	cardTexture.loadFromFile("BlackCandle/Cards/icons/icons.png");
	cardViewer.setTexture(cardTexture);
}

// Indicates if the Menu is open
bool Menu::isOpen() {
	return active;
}

// Open the Menu
void Menu::open() {
	active = true;
}

// Close the Menu
void Menu::close() {
	active = false;
}

// Set the Menu's width and heigth
void Menu::setSize(sf::Vector2u size) {
	width = size.x;
	height = size.y;
}

// The Menu's Very Own Loop
void Menu::menuLoop(sf::RenderWindow* gameWindow, Keyboard* keyboard, Player* player)
{
	input(player, keyboard);

	render(gameWindow, player);
	gameWindow->display();
	gameWindow->clear(sf::Color::Black);
}

// Handles the User's Input
void Menu::input(Player* player, Keyboard* keyboard)
{
	// This condition handles the input when no option has yet been selected
	// in the Menu's first Selection (COMPLETE)
	// -----------------------------------------------------------------------------------
	if (majorOption == 0)
	{
		// Cursos movement and selection change
		if (keyboard->clicked(sf::Keyboard::Left))
			selectionIndex--;
		else if (keyboard->clicked(sf::Keyboard::Right))
			selectionIndex++;

		// SelectionIndex boundaries
		if (selectionIndex < 1)
			selectionIndex = 1;
		else if (selectionIndex > 4)
			selectionIndex = 4;

		// Selection
		if (keyboard->clicked(sf::Keyboard::Z)) {
			majorOption = selectionIndex;
			selectionIndex = 1;
			minorOption = 0;
		}
		// De-selection
		else if (keyboard->clicked(sf::Keyboard::X))
			close();
	}
	// -----------------------------------------------------------------------------------

	// This condition handles the input when the Player has selected the "Status" option
	// in the Menu's Start (INCOMPLETE)
	// -----------------------------------------------------------------------------------
	else if (majorOption == 1)
	{
		std::cout << "Status" << std::endl;

		majorOption = 0;
	}
	// -----------------------------------------------------------------------------------

	// This condition handles all the input and options when the Player selectes the
	// "Equip" option in the first Menu Selection (COMPLETED)
	// -----------------------------------------------------------------------------------
	else if (majorOption == 2)
	{
		// This condition handles the input when the Player has not yet selected anything
		// from the "Equip" menu
		if (minorOption == 0)
		{
			// Cursos movement and selection change
			if (keyboard->clicked(sf::Keyboard::Up))
				selectionIndex--;
			else if (keyboard->clicked(sf::Keyboard::Down))
				selectionIndex++;

			// Selection boundaries
			if (selectionIndex < 1)
				selectionIndex = 1;
			else if (selectionIndex > 4)
				selectionIndex = 4;

			// Selection
			if (keyboard->clicked(sf::Keyboard::Z))
			{
				minorOption = selectionIndex;

				// View Synapses
				if (minorOption == 1)
				{
					basePointer = player->getInventory()->getBaseCard();
					if (basePointer != NULL) nodePointer = basePointer->getCenter();
				}
				// Equip Effect Card
				else if (minorOption == 2)
				{
					effectPointer = NULL;
					basePointer = player->getInventory()->getBaseCard();
					if (basePointer != NULL) nodePointer = basePointer->getCenter();
				}
				// Equip Spell Card
				else if (minorOption == 3)
				{
					basePointer = player->getInventory()->getBaseCard();
					if (basePointer != NULL) spellPointer = player->getInventory()->getActiveSpells().getSpellCard(0);
				}
				// Equip Base Card
				else if (minorOption == 4)
				{
					basePointer = NULL;
				}

				selectionIndex = 1;
			}
			// De-selection
			else if (keyboard->clicked(sf::Keyboard::X)) {
				selectionIndex = majorOption;
				majorOption = 0;
				minorOption = -1;
			}

		}
		// This condition handles the input when the Player has selected
		// the "View Synapses" option
		else if (minorOption == 1)
		{
			if (basePointer != NULL)		// If there's a BaseCard equipped
			{
				// Synapses movement control
				timeControl.start();
				if (timeControl.getTimeElapsed() >= 500)
				{
					if (moveSynapses())
						timeControl.stop();
				}

				// De-selection
				if (keyboard->clicked(sf::Keyboard::X))
				{
					offset.x = 0;
					offset.y = 0;

					selectionIndex = 1;

					minorOption = 0;
				}
			}
			else {		// If there's not a BaseCard equipped
				std::cout << "No BaseCard Equipped" << std::endl;

				minorOption = 0;
				selectionIndex = 0;
			}
		}
		// This condition handles the Input when the Player's selectes the 
		// "Equip Effect Card"
		else if (minorOption == 2)
		{
			if (basePointer != NULL)		// If there's a BaseCard equipped
			{
				// Synapses movement control
				timeControl.start();
				if (timeControl.getTimeElapsed() > 500)
				{
					if (moveSynapses())
						timeControl.stop();
				}

				// Selection
				if (keyboard->clicked(sf::Keyboard::Z)) {
					minorOption = 5;
					cardOffset = 0;
				}
				// De-selection
				else if (keyboard->clicked(sf::Keyboard::X)) {
					offset.x = 0;
					offset.y = 0;

					selectionIndex = 2;

					minorOption = 0;
				}
			}
			else {		// If there's not a BaseCard equipped
				std::cout << "No BaseCard Equipped" << std::endl;

				minorOption = 0;
				selectionIndex = 2;
			}
		}
		// This condition handles the input when the Player selectes the
		// "Equip SpellCard" option
		else if (minorOption == 3)
		{
			if (basePointer != NULL)		// If there's a BaseCard equipped
			{
				// Cursor movement and index change
				if (keyboard->clicked(sf::Keyboard::Left))
					selectionIndex++;
				else if (keyboard->clicked(sf::Keyboard::Right))
					selectionIndex--;

				// SelectionIndex boundaries
				if (selectionIndex < 1)
					selectionIndex = 1;
				else if (selectionIndex > player->getInventory()->getBaseCard()->getSpellSlots())
					selectionIndex = player->getInventory()->getBaseCard()->getSpellSlots();

				// spellIndex atualization
				spellIndex = selectionIndex;

				// Selection
				if (keyboard->clicked(sf::Keyboard::Z)) {
					minorOption = 6;
					cardOffset = 0;
				}
				// De-Selection
				else if (keyboard->clicked(sf::Keyboard::X))
				{
					minorOption = 0;

					selectionIndex = 3;
				}
			}
			else {		// If there's not a BaseCard equipped
				std::cout << "No BaseCard Equipped" << std::endl;

				minorOption = 0;
				selectionIndex = 3;
			}
		}
		// This condition handles the input when the Player selectes the
		// "Equip BaseCard" option
		else if (minorOption == 4)
		{
			// Cursor movement, cardOffset calculation and index change
			if (keyboard->clicked(sf::Keyboard::Up)) {
				selectionIndex--;
				if (cardOffset != 0)
					cardOffset--;
			}
			else if (keyboard->clicked(sf::Keyboard::Down)) {
				selectionIndex++;
				if (selectionIndex > 20)
					cardOffset++;
			}

			// SelectionIndex boundaries
			if (selectionIndex < 0)
				selectionIndex = 0;
			else if (selectionIndex > player->getInventory()->getBaseList().getSize())
				selectionIndex = player->getInventory()->getBaseList().getSize();

			// CardOffset boundaries
			if (20 + cardOffset > player->getInventory()->getBaseList().getSize())
				cardOffset = player->getInventory()->getBaseList().getSize() - 19;
			if (cardOffset < 0)
				cardOffset = 0;

			// Pointer atualization
			if (selectionIndex > 0)
				basePointer = player->getInventory()->getBaseList().getBaseCard(selectionIndex - 1);
			else
				basePointer = NULL;

			// Selection
			if (keyboard->clicked(sf::Keyboard::Z))
			{
				// Equipping the Card
				if (basePointer != NULL) {
					if (!basePointer->isEquipped()) {
						if (player->getInventory()->getBaseCard() != NULL)
							player->getInventory()->getBaseCard()->unequip();

						player->getInventory()->setBaseCard(basePointer);
						basePointer->equip();
					}
					else
						std::cout << "Carta ja equipada" << std::endl;
				}
				else {
					if (player->getInventory()->getBaseCard() != NULL)
						player->getInventory()->getBaseCard()->unequip();

					player->getInventory()->setBaseCard(NULL);
				}

				cardOffset = 0;
				selectionIndex = 1;
			}
			// De-Selection
			else if (keyboard->clicked(sf::Keyboard::X)){
				cardOffset = 0;
				minorOption = 0;
				selectionIndex = 4;
			}
		}
		// This is the condition that handles the Input when the Player's selecting
		// a card to equip in the "Equip Effect Card" Menu
		else if (minorOption == 5)
		{
			// Cursor movement, cardOffset calculation and index change
			if (keyboard->clicked(sf::Keyboard::Up)) {
				selectionIndex--;
				if (cardOffset != 0)
					cardOffset--;
			}
			else if (keyboard->clicked(sf::Keyboard::Down)) {
				selectionIndex++;
				if (selectionIndex > 20)
					cardOffset++;
			}

			// SelectionIndex boundaries
			if (selectionIndex < 0)
				selectionIndex = 0;
			else if (selectionIndex > player->getInventory()->getEffectList().getSize())
				selectionIndex = player->getInventory()->getEffectList().getSize();

			// CardOffset boundaries
			if (20 + cardOffset > player->getInventory()->getEffectList().getSize())
				cardOffset = player->getInventory()->getEffectList().getSize() - 19;
			if (cardOffset < 0)
				cardOffset = 0;

			// Pointer atualization
			if (selectionIndex > 0)
				effectPointer = player->getInventory()->getEffectList().getEffectCard(selectionIndex - 1);
			else
				effectPointer = NULL;

			// Selection
			if (keyboard->clicked(sf::Keyboard::Z))
			{
				// Equipping the Card
				if (effectPointer != NULL) {
					if (!effectPointer->isEquipped()) {
						if (nodePointer->getCard() != NULL)
							nodePointer->getCard()->unequip();

						nodePointer->setCard(effectPointer);
						effectPointer->equip();
					}
					else
						std::cout << "Carta ja equipada" << std::endl;
				}
				else {
					if (nodePointer->getCard() != NULL) nodePointer->getCard()->unequip();
					nodePointer->setCard(NULL);
				}

				cardOffset = 0;
				minorOption = 2;
				selectionIndex = 1;
			}
			// De-selection
			else if (keyboard->clicked(sf::Keyboard::X)){
				cardOffset = 0;
				minorOption = 2;
				selectionIndex = 1;
			}
		}
		// This is the condition that handles the Input when the Player's selecting
		// a card to equip in the "Equip Spell Card" Menu
		else if (minorOption == 6)
		{
			// Cursor movement, cardOffset calculation and index change
			if (keyboard->clicked(sf::Keyboard::Up)) {
				selectionIndex--;
				if (cardOffset != 0)
					cardOffset--;
			}
			else if (keyboard->clicked(sf::Keyboard::Down)) {
				selectionIndex++;
				if (selectionIndex > 20)
					cardOffset++;
			}

			// SelectionIndex boundaries
			if (selectionIndex < 0)
				selectionIndex = 0;
			else if (selectionIndex > player->getInventory()->getSpellList().getSize())
				selectionIndex = player->getInventory()->getSpellList().getSize();

			// CardOffset boundaries
			if (20 + cardOffset > player->getInventory()->getSpellList().getSize())
				cardOffset = player->getInventory()->getSpellList().getSize() - 19;
			if (cardOffset < 0)
				cardOffset = 0;

			// Pointer atualization
			if (selectionIndex > 0)
				spellPointer = player->getInventory()->getSpellList().getSpellCard(selectionIndex - 1);
			else
				spellPointer = NULL;

			// Selection
			if (keyboard->clicked(sf::Keyboard::Z))
			{
				// Equipping the Card
				if (spellPointer != NULL) {
					if (!spellPointer->isEquipped()) {
						if(player->getInventory()->getActiveSpells().getSpellCard(spellIndex - 1) != NULL)
							player->getInventory()->getActiveSpells().getSpellCard(spellIndex - 1)->unequip();

						player->getInventory()->setActiveSpell(spellIndex - 1, spellPointer);
						spellPointer->equip();
					}
					else
						std::cout << "Carta ja equipada" << std::endl;
				}
				else {
					if (player->getInventory()->getActiveSpells().getSpellCard(spellIndex - 1) != NULL)
						player->getInventory()->getActiveSpells().getSpellCard(spellIndex - 1)->unequip();

					player->getInventory()->setActiveSpell(spellIndex - 1, NULL);
				}

				minorOption = 3;
				cardOffset = 0;
				selectionIndex = spellIndex;
			}
			// De-Selection
			else if (keyboard->clicked(sf::Keyboard::X)){
				minorOption = 3;
				cardOffset = 0;
				selectionIndex = spellIndex;
			}
		}
	}
	// -----------------------------------------------------------------------------------

	// This condition handles all the input and options when the Player selectes the
	// "CARDS" option in the first Menu Selection (INCOMPLETE)
	// -----------------------------------------------------------------------------------
	else if (majorOption == 3)
	{
		std::cout << "Lista de Cartas" << std::endl;

		majorOption = 0;
	}
	// -----------------------------------------------------------------------------------

	// This condition handles all the input and options when the Player selectes the
	// "SYSTEM" option in the first Menu Selection (INCOMPLETE)
	// -----------------------------------------------------------------------------------
	else if (majorOption == 4)
	{
		std::cout << "System" << std::endl;

		majorOption = 0;
	}
	// -----------------------------------------------------------------------------------
}

// Renders the entire Menu
void Menu::render(sf::RenderWindow* gameWindow, Player* player)
{
	// ---------------------------------------------------------------
	// --------------------- GENERAL RENDERING -----------------------
	// ---------------------------------------------------------------
	// General Background
	renderBackground(0, 0, width, height, gameWindow);

	// Main Block - Menu's Options
	renderBlock(0, 0, width, 60, gameWindow);

	// Major Options' Text renderization
	text.setCharacterSize(40);

	text.setString("Status    Equip    Cards    System");
	text.setPosition((width / 2) - (text.getLocalBounds().width / 2), 13 - (text.getLocalBounds().height / 2));

	gameWindow->draw(text);

	// ---------------------------------------------------------------
	// --------------------- OPTIONS RENDERING -----------------------
	// ---------------------------------------------------------------

	// STATUS SUBMENU ________________________________________________
	if (majorOption == 1 || (majorOption == 0 && selectionIndex == 1))
	{
	}
	// _______________________________________________________________
	// EQUIPMENT SUBMENU __________________________________________________
	else if (majorOption == 2 || (majorOption == 0 && selectionIndex == 2))
	{
		// STRUCTURES AND BLOCKS _____________________________________________________________________________
		// The BaseCard's Structure
		if (player->getInventory()->getBaseCard() != NULL)
			player->getInventory()->getBaseCard()->render(gameWindow, 180 + ((width - 410) / 2) - 9 + offset.x,
			90 + ((height - 120) / 2) - 11 + offset.y);

		// Submain Block - Equipment Block
		renderBlock(0, 60, width, height - 60, gameWindow);

		// Equipment Options Block
		renderBlock(15, 90, 150, 200, gameWindow);

		// Card's List Block
		renderBlock(15, 320, 150, height - 350, gameWindow);

		// BaseCard's Block
		renderBlock(180, 90, width - 410, height - 120, gameWindow);

		// Card's Description Block
		renderBlock(width - 215, 90, 200, height - 120, gameWindow);

		// TEXTS _____________________________________________________________________________________________
		// Titles
		text.setCharacterSize(12);

		text.setString("Choose an option");
		text.setPosition(15 + 8, 75);

		gameWindow->draw(text);

		text.setString("Cards");
		text.setPosition(15 + 8, 305);

		gameWindow->draw(text);

		text.setString("BaseCard Synapses");
		text.setPosition(180 + 8, 75);

		gameWindow->draw(text);

		text.setString("Description");
		text.setPosition(width - 215 + 8, 75);

		gameWindow->draw(text);

		// Equipment Menu's Options
		text.setCharacterSize(16);

		text.setString("View\nSynapses\n\nEquip\nEffect Card\n\nEquip\nSpell Card\n\nEquip\nBase Card");
		text.setPosition(15 + (75 - text.getLocalBounds().width / 2) + 8, 90 + (200 / 9) - 10);

		gameWindow->draw(text);

		// Card's List and Descriptions
		if (minorOption == 2 || minorOption == 5)	// Effect Cards
		{
			if (basePointer != NULL)
			{
				drawList(&player->getInventory()->getEffectList(), 2, gameWindow);

				if (minorOption == 2) {
					if (nodePointer->getCard() == NULL)
						text.setString("Empty Slot\nLevel: " + to_string(nodePointer->getLevel()) + ".");
					else
						text.setString(nodePointer->getCard()->getDescription());
				}
				else {
					if (effectPointer == NULL)
						text.setString("Unequip the\nselected\nEffect Card.");
					else
						text.setString(effectPointer->getDescription());
				}

				text.setPosition(width - 215 + 15, 100);
				gameWindow->draw(text);
			}
		}
		else if (minorOption == 3 || minorOption == 6)		// Spell Cards
		{
			if (basePointer != NULL)
			{
				drawList(&player->getInventory()->getSpellList(), 1, gameWindow);

				if (minorOption == 3)
				{
					if (player->getInventory()->getActiveSpells().getSpellCard(selectionIndex - 1) == NULL)
						text.setString("Empty Slot");
					else
						text.setString(player->getInventory()->getActiveSpells().getSpellCard(selectionIndex - 1)->getDescription());
				}
				else
				{
					if (spellPointer == NULL)
						text.setString("Unequip the\nselected\Spell Card.");
					else
						text.setString(spellPointer->getDescription());
				}

				text.setPosition(width - 215 + 15, 100);
				gameWindow->draw(text);
			}
		}
		else if (minorOption == 4)		// BaseCards
		{
			drawList(&player->getInventory()->getBaseList(), 0, gameWindow);

			if (basePointer == NULL)
				text.setString("Unequip the\nselected\nBase Card.");
			else
				text.setString(basePointer->getDescription());

			text.setPosition(width - 215 + 15, 100);
			gameWindow->draw(text);
		}
	}
	// ____________________________________________________________________
	// CARDS SUBMENU ______________________________________________________
	else if (majorOption == 3)
	{
	}
	// ____________________________________________________________________
	// SYSTEM SUBMENU _____________________________________________________
	else if (majorOption == 4)
	{
	}
	// ____________________________________________________________________

	// ---------------------------------------------------------------
	// ----------------------- INPUT RENDERING -----------------------
	// ---------------------------------------------------------------

	// Cursor Texture and Size
	box.setTextureRect(sf::IntRect(0, 24, 8, 8));
	box.setSize(sf::Vector2f(8, 8));

	// MAIN MENU __________________________________________________________
	if (majorOption == 0)
	{
		switch (selectionIndex)
		{
		case 1:
			box.setPosition((width / 2 - 400) + 35, 30 - 4);
			break;
		case 2:
			box.setPosition((width / 2 - 400) + 231, 30 - 4);
			break;
		case 3:
			box.setPosition((width / 2 - 400) + 405, 30 - 4);
			break;
		case 4:
			box.setPosition((width / 2 - 400) + 581, 30 - 4);
			break;
		}

		gameWindow->draw(box);
	}
	// ____________________________________________________________________
	// EQUIPMENT SUBMENU __________________________________________________
	if (majorOption == 2 || (majorOption == 0 && selectionIndex == 2))
	{
		if (player->getInventory()->getBaseCard() != NULL)
		{
			// BaseCard's Name and Sprite
			cardViewer.setTextureRect(sf::IntRect(18 * 1, 22 * 0, 18, 22));
			cardViewer.setPosition(180 + 18, 90 + 30);

			text.setCharacterSize(12);
			text.setPosition(180 + 18, 90 + 15);
			text.setString(player->getInventory()->getBaseCard()->getName());

			gameWindow->draw(cardViewer);
			gameWindow->draw(text);

			// SpellCards' Names and Sprites
			for (int i = player->getInventory()->getBaseCard()->getSpellSlots(); i > 0; i--)
			{
				if (player->getInventory()->getActiveSpells().getSpellCard(i - 1) != NULL)
					cardViewer.setTextureRect(sf::IntRect(18 * 2, 22 * 0, 18, 22));
				else
					cardViewer.setTextureRect(sf::IntRect(18 * 0, 22 * 0, 18, 22));

				cardViewer.setPosition(width - 230 - (15 + 28 * i), 90 + 30);

				text.setPosition(width - 230 - (15 + 28 * i) + 9, 90 + 15);
				text.setString(to_string(i));

				gameWindow->draw(cardViewer);
				gameWindow->draw(text);
			}
		}
		else {
			// NO BASECAR EQUIPPED
			cardViewer.setTextureRect(sf::IntRect(18 * 0, 22 * 0, 18, 22));
			cardViewer.setPosition(180 + 18, 90 + 30);

			text.setCharacterSize(12);
			text.setPosition(180 + 18, 90 + 15);
			text.setString("Empty");

			gameWindow->draw(cardViewer);
			gameWindow->draw(text);
		}

		// EQUIPMENT MENU OPTIONS CURSOR
		if (minorOption == 0) {
			switch (selectionIndex)
			{
			case 1:
				box.setPosition(30, 118);
				break;
			case 2:
				box.setPosition(30, 162);
				break;
			case 3:
				box.setPosition(30, 207);
				break;
			case 4:
				box.setPosition(30, 253);
				break;
			}

			gameWindow->draw(box);
		}
		// MOVE SYNAPSES CARD SPRITE AND CURSOR
		else if (minorOption == 1) {
			box.setPosition(30, 118);

			cardViewer.setTextureRect(sf::IntRect(18 * 0, 22 * 1, 18, 22));
			cardViewer.setPosition(180 + ((width - 410) / 2) - 9,
				90 + ((height - 120) / 2) - 11);

			if (player->getInventory()->getBaseCard() != NULL)
			{
				text.setPosition(width - 215 + 15, 100);

				if (nodePointer->getCard() == NULL)
					text.setString("Empty Slot\nLevel: " + to_string(nodePointer->getLevel()) + ".");
				else
					text.setString(nodePointer->getCard()->getDescription());
			}

			gameWindow->draw(box);
			if (player->getInventory()->getBaseCard() != NULL) {
				gameWindow->draw(cardViewer);
				gameWindow->draw(text);
			}

		}
		// EQUIP EFFECT CARD SPRITES AND CURSOR
		else if (minorOption == 2 || minorOption == 5) {
			box.setPosition(30, 162);

			cardViewer.setTextureRect(sf::IntRect(18 * 0, 22 * 1, 18, 22));
			cardViewer.setPosition(180 + ((width - 410) / 2) - 9,
				90 + ((height - 120) / 2) - 11);

			gameWindow->draw(box);
			if (player->getInventory()->getBaseCard() != NULL)
				gameWindow->draw(cardViewer);
		}
		// EQUIP SPELLCARD SPRITES AND CURSOR
		else if (minorOption == 3 || minorOption == 6) {
			box.setPosition(30, 207);

			cardViewer.setTextureRect(sf::IntRect(18 * 0, 22 * 1, 18, 22));
			cardViewer.setPosition(width - 230 - (15 + 28 * spellIndex), 90 + 30);

			gameWindow->draw(box);
			if (player->getInventory()->getBaseCard() != NULL)
				gameWindow->draw(cardViewer);
		}
		// EQUIP BASECARD CURSOR
		else if (minorOption == 4) {
			box.setPosition(30, 253);

			gameWindow->draw(box);
		}

		if (minorOption == 4 || minorOption == 5 || minorOption == 6) {

			if (selectionIndex < 20)
				box.setPosition(25, 320 + 15 + (selectionIndex * 11));
			else
				box.setPosition(25, 320 + 15 + (19 * 11));

			gameWindow->draw(box);
		}
	}
	// ____________________________________________________________________
}

// This method creates an String based in one of the Player's Cards List
// and return the entire list in form of this string
void Menu::drawList(CardList* cardList, int cardType, sf::RenderWindow* gameWindow)
{
	text.setCharacterSize(12);

	std::string list("");

	if (minorOption > 1 && minorOption <= 6) {
		if (cardOffset == 0)
			list += "< Unequip >";
		else
			list += "[...]";
	}

	for (int i = cardOffset; i < cardList->getSize() && i < cardOffset + 20 - 1; i++)
	{
		list += "\n";

		Card* pointer;
		if (cardType == 0)
			pointer = cardList->getBaseCard(i);
		else if (cardType == 1)
			pointer = cardList->getSpellCard(i);
		else if (cardType == 2)
			pointer = cardList->getEffectCard(i);

		int compensation = 0;
		if (pointer->isEquipped()) {
			list += "[E] ";
			compensation = 4;
		}

		list += "#" + to_string(pointer->getID()) + "-";

		if (pointer->getName().length() + compensation > 10)
			list += pointer->getName().substr(0, 10) + "...";
		else
			list += pointer->getName();

		if (cardOffset + 19 < cardList->getSize())
			list += "\n[...]";
	}

	text.setString(list);
	text.setPosition(15 + 15 + 8, 320 + 10);

	gameWindow->draw(text);
}

// Method responsable for move tha pointer trough the Synapses
bool Menu::moveSynapses()
{
	// Upper-Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (nodePointer->getNode(1) != NULL){
			nodePointer = nodePointer->getNode(1);
			offset.x -= 28;
			offset.y += 32;
			return true;
		}
	}
	// Bottom-Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (nodePointer->getNode(3) != NULL){
			nodePointer = nodePointer->getNode(3);
			offset.x -= 28;
			offset.y -= 32;
			return true;
		}
	}
	// Upper-Left
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (nodePointer->getNode(7) != NULL){
			nodePointer = nodePointer->getNode(7);
			offset.x += 28;
			offset.y += 32;
			return true;
		}
	}
	// Bottom-Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (nodePointer->getNode(5) != NULL){
			nodePointer = nodePointer->getNode(5);
			offset.x += 28;
			offset.y -= 32;
			return true;
		}
	}
	// Up
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (nodePointer->getNode(0) != NULL){
			nodePointer = nodePointer->getNode(0);
			offset.y += 32;
			return true;
		}
	}
	// Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (nodePointer->getNode(2) != NULL){
			nodePointer = nodePointer->getNode(2);
			offset.x -= 28;
			return true;
		}
	}
	// Down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (nodePointer->getNode(4) != NULL){
			nodePointer = nodePointer->getNode(4);
			offset.y -= 32;
			return true;
		}
	}
	// Left
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (nodePointer->getNode(6) != NULL){
			nodePointer = nodePointer->getNode(6);
			offset.x += 28;
			return true;
		}
	}

	return false;
}

// Uses a pattern to fill the menu's background
void Menu::renderBackground(float positionX, float positionY, int sizeX, int sizeY, sf::RenderWindow* gameWindow)
{
	// Set the Background's Texture
	box.setTextureRect(sf::IntRect(24, 0, 32, 32));
	box.setSize(sf::Vector2f(32, 32));

	// Draw the background
	for (int i = 0; i * 32 < sizeY; i++)
	{
		for (int j = 0; j * 32 < sizeX; j++)
		{
			box.setPosition(positionX + j * 32, positionY + i * 32);
			gameWindow->draw(box);
		}
	}
}

// Creates a Box using the Texture to make a proper border
void Menu::renderBlock(float positionX, float positionY, int sizeX, int sizeY, sf::RenderWindow* gameWindow)
{
	// Upper-Left Border
	box.setTextureRect(sf::IntRect(0, 0, 8, 8));

	box.setPosition(positionX, positionY);
	box.setSize(sf::Vector2f(8, 8));

	gameWindow->draw(box);

	// Upper Border
	box.setTextureRect(sf::IntRect(8, 0, 8, 8));

	box.setPosition(positionX + 8, positionY);
	box.setSize(sf::Vector2f(sizeX - 16, 8));

	gameWindow->draw(box);

	// Upper-Right Border
	box.setTextureRect(sf::IntRect(16, 0, 8, 8));

	box.setPosition(positionX + (sizeX - 8), positionY);
	box.setSize(sf::Vector2f(8, 8));

	gameWindow->draw(box);

	// Right Border
	box.setTextureRect(sf::IntRect(16, 8, 8, 8));

	box.setPosition(positionX + (sizeX - 8), positionY + 8);
	box.setSize(sf::Vector2f(8, sizeY - 16));

	gameWindow->draw(box);

	// Bottom-Right Border
	box.setTextureRect(sf::IntRect(16, 16, 8, 8));

	box.setPosition(positionX + (sizeX - 8), positionY + (sizeY - 8));
	box.setSize(sf::Vector2f(8, 8));

	gameWindow->draw(box);

	// Bottom Border
	box.setTextureRect(sf::IntRect(8, 16, 8, 8));

	box.setPosition(positionX + 8, positionY + (sizeY - 8));
	box.setSize(sf::Vector2f(sizeX - 16, 8));

	gameWindow->draw(box);

	// Bottom-Left Border
	box.setTextureRect(sf::IntRect(0, 16, 8, 8));

	box.setPosition(positionX, positionY + (sizeY - 8));
	box.setSize(sf::Vector2f(8, 8));

	gameWindow->draw(box);

	// Left Border
	box.setTextureRect(sf::IntRect(0, 8, 8, 8));

	box.setPosition(positionX, positionY + 8);
	box.setSize(sf::Vector2f(8, sizeY - 16));

	gameWindow->draw(box);
}