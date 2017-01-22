// *****************************************************
// ********* IMPLEMENTATION OF THE GAME CLASS **********
// *****************************************************

#include "Game.h"
#include "Collision.h"
#include <iostream>

using namespace std;

// Standart Constructor
Game::Game()
{
	// Initializing the boolean that keeps the game running
	isGame = true;

	// Initializing the Main Window of the Game
	mainWindow.create(sf::VideoMode(1280, 720), "Black Candle", sf::Style::Default);
	
	// Initialization of the Game's Camera
	camera.reset(sf::FloatRect(0, 0, mainWindow.getSize().x, mainWindow.getSize().y));
	mainWindow.setView(camera);

	// Initializating the Stage with the "null" stage
	currentStage = new Stage();

	// Menu Initialization
	menu.setSize(mainWindow.getSize());
}

void Game::userInput()
{

}

void Game::centerCamera(Character* target)
{
	// Generic centralization of the Camera
	camera.setCenter(target->getPosition().x + (target->getSize().x / 2.0),
					 target->getPosition().y + (target->getSize().y / 2.0));

	// Limiting the view to the Stage's boundaries
	// In the X Axis
	if (camera.getCenter().x - (mainWindow.getSize().x / 2.0) < 0)
		camera.setCenter((mainWindow.getSize().x / 2.0), camera.getCenter().y);
	else if (camera.getCenter().x + (mainWindow.getSize().x / 2.0) > currentStage->getSize().x)
		camera.setCenter(currentStage->getSize().x - (mainWindow.getSize().x / 2.0), camera.getCenter().y);

	// In the Y Axis
	if (camera.getCenter().y + (mainWindow.getSize().y / 2.0) > currentStage->getSize().y)
		camera.setCenter(camera.getCenter().x, mainWindow.getSize().y / 2.0);
}

#include "Menu.h"
#include "Inventory.h"
#include "BaseCard.h"

void Game::run()
{
	Player tste;
	tste.setPosition(10, 200);
	BaseCard carta1(1);
	BaseCard carta5(5);
	EffectCard carta2(2);
	EffectCard carta3(3);
	SpellCard carta4(4);
	SpellCard carta6(6);
	SpellCard carta7(7);

	tste.addToInventory(carta1);
	tste.addToInventory(carta1);
	tste.addToInventory(carta1);
	tste.addToInventory(carta1);
	tste.addToInventory(carta6);
	tste.addToInventory(carta7);
	tste.addToInventory(carta5);
	tste.addToInventory(carta2);
	tste.addToInventory(carta3);
	tste.addToInventory(carta4);

	Inventory testeT;
	BaseNode teste5;
	Card teste2(1);

	cout << sizeof(menu) << endl;
	cout << sizeof(carta1) << endl;
	cout << sizeof(tste) << endl;
	cout << sizeof(teste5) << endl;
	cout << sizeof(testeT) << endl;
	cout << sizeof(teste2) << endl;
	
	mainWindow.setFramerateLimit(200);
	// Game Loop
	while (isGame)
	{
		// ------ Tratamento de Eventos -------
		sf::Event e;

		while (mainWindow.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				mainWindow.close();
				isGame = false;
			}
			if (e.type == sf::Event::KeyPressed) {
				if (e.key.code == sf::Keyboard::Escape)
					mainWindow.close();
			}
		}
		// ------------------------------------
		tste.update(&mainWindow, &keyboard, currentStage);

		centerCamera(&tste);

		if (keyboard.isKeyPressed(keyboard.H, 500))
			tste.receiveHit(20, 0);

		Physics::appPhysics(&tste, currentStage);
		Physics::appPhysics(currentStage->getMonsterList()[0], currentStage);

		currentStage->renderMap(&mainWindow);

		tste.render(&mainWindow);

		mainWindow.setView(camera);
		mainWindow.display();
		mainWindow.clear(sf::Color::Black);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
 			std::cout << "POW" << std::endl;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			menu.open();

		while (menu.isOpen())
			menu.menuLoop(&mainWindow, &keyboard, &tste);
	}
}