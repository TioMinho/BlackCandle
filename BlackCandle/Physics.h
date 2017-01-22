#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "Character.h"
#include "Stage.h"

class Physics
{
// --------- Methods -----------
public:
	// Standart Constructor
	Physics();

	// Method responsable for applying gravity to Characters entities
	static void appGravity(Character* character, int groundHeight);						

	// Method responsable for recognizing and dealing with Mechanics Collisions
	static void appMechanic(Character* character, sf::RectangleShape* plataform);
	static void appMechanic(Character* character, Tile* tile);
	static bool appMechanic(sf::Sprite* sprite, Stage* stage);

	// General method to apply Physics to Characters entities
	static void appPhysics(Character* character, sf::RectangleShape* plataform, int groundHeight);
	static void appPhysics(Character* character, Stage* stage);

// -----------------------------
};

#endif