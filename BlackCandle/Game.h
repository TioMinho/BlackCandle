#ifndef _GAME_H_
#define _GAME_H_

#include <SFML\Graphics.hpp>
#include "Keyboard.h"
#include "Menu.h"
#include "Stage.h"
#include "CombatEntity.h"
#include "Physics.h"

// Game - Main Class, responsable for running the game
// entirely. All methods except "run()" are privates.
class Game
{
// -------- Attributes ---------- 
private:
	sf::RenderWindow mainWindow;		// Game's Main Window
	bool isGame;						// Indicates if the game is still running
	sf::View camera;					// The Game's Main Camera
	Stage* currentStage;				// A pointer to the Game's current stage in play
	Keyboard keyboard;					// The Game's Keyboard Input class
	Menu menu;							// The Player's in-game Menu

	// **************** TESTE
	CombatEntity teste;

// -----------------------------

// --------- Methods -----------
private:
	// Manage the User's Input
	void userInput();

	// Center's the Camera in the Main Character
	void centerCamera(Character* target);

public:
	// Standart Constructor
	Game();
	
	// Main Method -> Runs the game entirely
	void run();

// -----------------------------
};

#endif