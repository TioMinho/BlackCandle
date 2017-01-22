// *****************************************************
// ******** IMPLEMENTATION OF THE PHYSICS CLASS ********
// *****************************************************

#include "Physics.h"
#include "Collision.h"

// Standart Constructor
Physics::Physics() { }

// Method responsable for applying gravity to Characters entities
void Physics::appGravity(Character* character, int groundHeight)
{
	if (character->getPosition().y + character->getSize().y >= groundHeight)
	{
		character->onGround();
		character->setPosition(character->getPosition().x, groundHeight - character->getSize().y);
	}
	else
		character->doFall(0.05);
}

// Method responsable for recognizing and dealing with Mechanics Collisions
void Physics::appMechanic(Character* character, sf::RectangleShape* plataform)
{
	if (Collision::upCollision(&character->getSprite(), plataform))
	{
		character->onGround();
		character->setPosition(character->getPosition().x, plataform->getPosition().y - character->getSize().y);
	}
	else if (Collision::downCollision(&character->getSprite(), plataform))
	{
		character->setPosition(character->getPosition().x, plataform->getPosition().y + plataform->getLocalBounds().height);
	}
	else
	{
		if (Collision::leftCollision(&character->getSprite(), plataform))
			character->setPosition(plataform->getPosition().x - character->getSize().x, character->getPosition().y);

		if (Collision::rightCollision(&character->getSprite(), plataform))
			character->setPosition(plataform->getPosition().x + plataform->getLocalBounds().width, character->getPosition().y);
	}
}

void Physics::appMechanic(Character* character, Tile* tile)
{
	if (Collision::upCollision(&character->getSprite(), tile))
	{
		character->onGround();
		character->setPosition(character->getPosition().x, tile->top() - character->getSize().y);
	}
	else if (Collision::downCollision(&character->getSprite(), tile))
	{
		character->setPosition(character->getPosition().x, tile->bottom());
	}
	else
	{
		if (Collision::leftCollision(&character->getSprite(), tile))
			character->setPosition(tile->left() - character->getSize().x, character->getPosition().y);

		if (Collision::rightCollision(&character->getSprite(), tile))
			character->setPosition(tile->right(), character->getPosition().y);
	}
}

bool Physics::appMechanic(sf::Sprite* sprite, Stage* stage)
{
	// Collision Check with all the Stage's Tiles
	for (int i = 0; i < stage->getCollisionMap().size(); i++)
		if (Collision::boundingBox(sprite, &stage->getCollisionMap()[i]))
			return true;

	// Stopping a Character to tresspass the Stage's boundaries
	if (sprite->getPosition().x < 0)
		return true;
	else if (sprite->getPosition().x + sprite->getLocalBounds().width > stage->getSize().x)
		return true;

	return false;
}

// General method to apply Physics to Characters entities
void Physics::appPhysics(Character* character, sf::RectangleShape* plataform, int groundHeight)
{
	appGravity(character, groundHeight);
	appMechanic(character, plataform);
}

void Physics::appPhysics(Character* character, Stage* stage)
{
	// Gravity (Collision in the Y Axis)
	appGravity(character, stage->getSize().y);

	// Collision Check with all the Stage's Tiles
	for (int i = 0; i < stage->getCollisionMap().size(); i++)
		appMechanic(character, &stage->getCollisionMap()[i]);

	// Stopping a Character to tresspass the Stage's boundaries
	if (character->getPosition().x < 0)
		character->setPosition(0, character->getPosition().y);
	else if (character->getPosition().x + character->getSize().x > stage->getSize().x)
		character->setPosition(stage->getSize().x - character->getSize().x, character->getPosition().y);

}