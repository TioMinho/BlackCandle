#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <SFML\Graphics.hpp>
#include "SATCollision.h"
#include "Tile.h"

class Collision {
// -------- Methods ----------
public:
	// Bounding Box Collision Test - General
	static bool boundingBox(sf::Sprite* agent, sf::Shape* receptor);			// For a "sf::Shape"
	static bool boundingBox(sf::Sprite* agent, sf::Sprite* receptor);			// For a "sf::Sprite"
	static bool boundingBox(sf::Sprite* agent, Tile* receptor);					// For a "Tile"
	static bool boundingBox(sf::FloatRect* agent, sf::FloatRect* receptor) {		// For any two rectangles
		return !(agent->left + agent->width < receptor->left
			||
			agent->top + agent->height < receptor->top
			||
			agent->top > receptor->top + receptor->height
			||
			agent->left > receptor->left + receptor->width);
	}
	static bool SATBoundingBox(const sf::Sprite& agent, const sf::Sprite& receptor)
	{
		return SATCollision::BoundingBoxTest(agent, receptor);
	}

	// Bounding Box Collision Tests -> Direcional Collisions
	// For a "sf::Shape"
	static bool upCollision(sf::Sprite* upAgent, sf::Shape* downReceptor);
	static bool leftCollision(sf::Sprite* leftAgent, sf::Shape* rightReceptor);
	static bool rightCollision(sf::Sprite* rightAgent, sf::Shape* leftReceptor);
	static bool downCollision(sf::Sprite* downAgent, sf::Shape* upReceptor);

	// For a "Tile"
	static bool upCollision(sf::Sprite* upAgent, Tile* downReceptor);
	static bool leftCollision(sf::Sprite* leftAgent, Tile* rightReceptor);
	static bool rightCollision(sf::Sprite* rightAgent, Tile* leftReceptor);
	static bool downCollision(sf::Sprite* downAgent, Tile* upReceptor);

// ---------------------------
};

#endif

