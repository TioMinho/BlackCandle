// *****************************************************
// ******* IMPLEMENTATION OF THE COLLISION CLASS *******
// *****************************************************

#include "Collision.h"

// -------------------------------------
// Bounding Box Collision Test - General
// -------------------------------------
// For a "sf::Shape"
bool Collision::boundingBox(sf::Sprite* agent, sf::Shape* receptor)
{
	return !(agent->getPosition().x + agent->getGlobalBounds().width < receptor->getPosition().x
		||
		agent->getPosition().y + agent->getGlobalBounds().height < receptor->getPosition().y
		||
		agent->getPosition().y > receptor->getPosition().y + receptor->getGlobalBounds().height
		||
		agent->getPosition().x > receptor->getPosition().x + receptor->getGlobalBounds().width);
}

// For a "sf::Sprite"
bool Collision::boundingBox(sf::Sprite* agent, sf::Sprite* receptor) {
	return !(agent->getPosition().x + agent->getGlobalBounds().width < receptor->getPosition().x
		||
		agent->getPosition().y + agent->getGlobalBounds().height < receptor->getPosition().y
		||
		agent->getPosition().y > receptor->getPosition().y + receptor->getGlobalBounds().height
		||
		agent->getPosition().x > receptor->getPosition().x + receptor->getGlobalBounds().width);
}

// For a "Tile"
bool Collision::boundingBox(sf::Sprite* agent, Tile* receptor)
{
	return !(agent->getPosition().x + agent->getGlobalBounds().width < receptor->left()
		||
		agent->getPosition().y + agent->getGlobalBounds().height < receptor->top()
		||
		agent->getPosition().y > receptor->bottom()
		||
		agent->getPosition().x > receptor->right());
}
// ----------------------------------------
// Bounding Box Collision Test - Direcional
// ----------------------------------------

// For a "sf::Shape"
// Bounding Box Collision Test - Up->Down
bool Collision::upCollision(sf::Sprite* upAgent, sf::Shape* downReceptor)
{
	return (boundingBox(upAgent, downReceptor) &&
		upAgent->getPosition().y < downReceptor->getPosition().y &&
		upAgent->getPosition().y < downReceptor->getPosition().y + downReceptor->getGlobalBounds().height &&
		upAgent->getPosition().y + upAgent->getGlobalBounds().height <= downReceptor->getPosition().y + 5 &&
		upAgent->getPosition().y + upAgent->getGlobalBounds().height < downReceptor->getPosition().y + downReceptor->getGlobalBounds().height &&
		upAgent->getPosition().x + upAgent->getGlobalBounds().width > downReceptor->getPosition().x + 1 &&
		upAgent->getPosition().x < downReceptor->getPosition().x + downReceptor->getGlobalBounds().width - 1);
}

// Bounding Box Collision Test - Left->Right
bool Collision::leftCollision(sf::Sprite* leftAgent, sf::Shape* rightReceptor)
{
	return (boundingBox(leftAgent, rightReceptor) &&
		leftAgent->getPosition().x < rightReceptor->getPosition().x &&
		leftAgent->getPosition().x < rightReceptor->getPosition().x + rightReceptor->getGlobalBounds().width &&
		leftAgent->getPosition().x + leftAgent->getGlobalBounds().width <= rightReceptor->getPosition().x + 2 &&
		leftAgent->getPosition().x + leftAgent->getGlobalBounds().width < rightReceptor->getPosition().x + rightReceptor->getGlobalBounds().width);
}

// Bounding Box Collision Test - Right->Left
bool Collision::rightCollision(sf::Sprite* rightAgent, sf::Shape* leftReceptor)
{
	return (boundingBox(rightAgent, leftReceptor) &&
		rightAgent->getPosition().x >= leftReceptor->getPosition().x + leftReceptor->getGlobalBounds().width - 2 &&
		rightAgent->getPosition().x > leftReceptor->getPosition().x &&
		rightAgent->getPosition().x + rightAgent->getGlobalBounds().width > leftReceptor->getPosition().x &&
		rightAgent->getPosition().x + rightAgent->getGlobalBounds().width > leftReceptor->getPosition().x + leftReceptor->getGlobalBounds().width);
}

// Bounding Box Collision Test - Down->Up
bool Collision::downCollision(sf::Sprite* downAgent, sf::Shape* upReceptor)
{
	return (boundingBox(downAgent, upReceptor) &&
		downAgent->getPosition().y >= upReceptor->getPosition().y + upReceptor->getGlobalBounds().height - 2 &&
		downAgent->getPosition().y > upReceptor->getPosition().y &&
		downAgent->getPosition().y + downAgent->getGlobalBounds().height > upReceptor->getPosition().y &&
		downAgent->getPosition().y + downAgent->getGlobalBounds().height > upReceptor->getPosition().y + upReceptor->getGlobalBounds().height);
}

// For a "Tile"
// Bounding Box Collision Test - Up->Down
bool Collision::upCollision(sf::Sprite* upAgent, Tile* downReceptor)
{
	return (boundingBox(upAgent, downReceptor) &&
		upAgent->getPosition().y < downReceptor->top() &&
		upAgent->getPosition().y < downReceptor->bottom() &&
		upAgent->getPosition().y + upAgent->getGlobalBounds().height <= downReceptor->top() + 5 &&
		upAgent->getPosition().y + upAgent->getGlobalBounds().height < downReceptor->bottom() &&
		upAgent->getPosition().x + upAgent->getGlobalBounds().width > downReceptor->left() + 1 &&
		upAgent->getPosition().x < downReceptor->right() - 1);
}

// Bounding Box Collision Test - Left->Right
bool Collision::leftCollision(sf::Sprite* leftAgent, Tile* rightReceptor)
{
	return (boundingBox(leftAgent, rightReceptor) &&
		leftAgent->getPosition().x < rightReceptor->left() &&
		leftAgent->getPosition().x < rightReceptor->right() &&
		leftAgent->getPosition().x + leftAgent->getGlobalBounds().width <= rightReceptor->left() + 2 &&
		leftAgent->getPosition().x + leftAgent->getGlobalBounds().width < rightReceptor->right() &&
		leftAgent->getPosition().y + leftAgent->getGlobalBounds().height > rightReceptor->top() + 1);
}

// Bounding Box Collision Test - Right->Left
bool Collision::rightCollision(sf::Sprite* rightAgent, Tile* leftReceptor)
{
	return (boundingBox(rightAgent, leftReceptor) &&
		rightAgent->getPosition().x >= leftReceptor->right() - 2 &&
		rightAgent->getPosition().x > leftReceptor->left() &&
		rightAgent->getPosition().x + rightAgent->getGlobalBounds().width > leftReceptor->left() &&
		rightAgent->getPosition().x + rightAgent->getGlobalBounds().width > leftReceptor->right() &&
		rightAgent->getPosition().y + rightAgent->getGlobalBounds().height > leftReceptor->top() + 1);
}

// Bounding Box Collision Test - Down->Up
bool Collision::downCollision(sf::Sprite* downAgent, Tile* upReceptor)
{
	return (boundingBox(downAgent, upReceptor) &&
		downAgent->getPosition().y >= upReceptor->bottom() - 2 &&
		downAgent->getPosition().y > upReceptor->top() &&
		downAgent->getPosition().y + downAgent->getGlobalBounds().height > upReceptor->top() &&
		downAgent->getPosition().y + downAgent->getGlobalBounds().height > upReceptor->bottom());
}