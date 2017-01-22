// *********************************************************
// ********* IMPLEMENTATION OF THE SPELLCARD CLASS *********
// *********************************************************

#include "SpellCard.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include "Collision.h"
#include "Physics.h"

// CONSTRUCTOR
// Default Constructor
SpellCard::SpellCard()
{
	// Default initialization
	category = magicPower = castingTime = cooldownTime
		= costMP = 0;
}

// Custom Constructor
SpellCard::SpellCard(int cardID)
{
	// General attributes initialization
	load(cardID);

	// Loads the Spell's Texture
	imageTexture.loadFromFile("BlackCandle/Cards/SpellCards/" + std::to_string(cardID) + ".png");
	image.setTexture(imageTexture);
	image.setPosition(0, -999999);

	// Cooldown Timer initialization
	cooldown.start();

	// We open the respective EffectCard ".bin" accordingly 
	// with its ID
	std::ifstream file("BlackCandle/Cards/SpellCards/" + std::to_string(cardID) + ".bin", std::ios::in | std::ios::binary);

	// We create two strings: one for getting the line (all the ".bin" content) and another
	// to separate the attributes
	std::string line, value;

	// We import the ".bin" to "line"
	std::getline(file, line);

	// And so, we create a Stringstream to read the attributes
	std::stringstream stream(line);

	// We read the category
	std::getline(stream, value, ';');
	category = atoi(value.c_str());

	// We read the magic power
	std::getline(stream, value, ';');
	magicPower = atoi(value.c_str());

	// We read the casting time
	std::getline(stream, value, ';');
	castingTime = atoi(value.c_str());

	// We read the cooldown time
	std::getline(stream, value, ';');
	cooldownTime = atoi(value.c_str());

	// We read the MP cost
	std::getline(stream, value, ';');
	costMP = atoi(value.c_str());
}

// GETTERS
int SpellCard::getCategory() {
	return category;
}

int SpellCard::getCastingTime() {
	return castingTime;
}

int SpellCard::getCooldownTime() {
	return cooldownTime;
}

bool SpellCard::isCharged() {
	return (cooldown.getTimeElapsed() >= cooldownTime);
}

int SpellCard::getCost() {
	return costMP;
}

// This method is triggered when the Player presses the command button
// long enough to the Spell be active. It works diferently for each category:
// 1 (Projectile) = Adds a Projectile position, angle and velocity.
// 2 (Beam) = Adds a Beam position and angle and set the Spell as active
// 3 (Area) = Adds a Area position and set the Spell as active
void SpellCard::use(sf::Vector2f position, float rotation, float angle)
{
	if (category == 1)
	{
		positions.push_back(position);
		angles.push_back(rotation);
		cooldown.stop();
		cooldown.start();
		sf::Vector2f p;
	}
	else if (category == 2)
	{
		image.setPosition(position.x + (sin(rotation) * image.getLocalBounds().height / 2),
			position.y - (cos(rotation) * image.getLocalBounds().height / 2));
		image.setRotation(angle);
		cooldown.start();
	}
	else if (category == 3)
	{
		cooldown.stop();
		cooldown.start();
	}
}

// These is the main method, it makes the Spell's happen while
// the User is still doing other things
// Player's Method
void SpellCard::execute(Stage* currentStage, CombatEntity* user, sf::RenderWindow* gameWindow)
{
	// -------------------------- Projectiles -----------------------------------
	if (category == 1)
	{
		// Movimentação e Colisão dos Projéteis
		int size = positions.size(), erases = 0;
		for (int i = 0; i < size; i++)
		{
			positions[i - erases].x += cos(angles[i - erases]) * 3;
			positions[i - erases].y += sin(angles[i - erases]) * 3;

			image.setPosition(positions[i - erases]);

			bool collide = false;
			for (int j = 0; j < currentStage->getMonsterList().size(); j++)
			{
				if (Collision::boundingBox(&image, &currentStage->getMonsterList().at(j)->getSprite()))
				{
					collide = true;

					switch (user->magicChance(currentStage->getMonsterList().at(j)))
					{
					case 1:
						currentStage->getMonsterList().at(j)->receiveHit(user->magicalDamage(magicPower) * 2, true);
						std::cout << "Dano(Critical): " << user->magicalDamage(magicPower) * 2 << std::endl;
						break;
					case 2:
						currentStage->getMonsterList().at(j)->receiveHit(user->magicalDamage(magicPower), true);
						std::cout << "Dano: " << user->magicalDamage(magicPower) << std::endl;
						break;
					case 3:
						std::cout << "MISS" << std::endl;
						break;
					}
				}
			}

			if (collide) {
				positions.erase(positions.begin() + (i - erases));
				angles.erase(angles.begin() + (i - erases));

				erases++;
			}
			else if (Physics::appMechanic(&image, currentStage)) {
				positions.erase(positions.begin() + (i - erases));
				angles.erase(angles.begin() + (i - erases));

				erases++;
			}

			gameWindow->draw(image);
		}
	}
	// -------------------------------------------------------------------------
	// ------------------------------- Beam ------------------------------------
	else if (category == 2)
	{
		if (user->isCasting())
		{
			if (cooldown.getTimeElapsed() >= 500)
			{
				for (int i = 0; i < currentStage->getMonsterList().size(); i++) {
					if (Collision::SATBoundingBox(image, currentStage->getMonsterList().at(i)->getSprite()))
					{
						switch (user->magicChance(currentStage->getMonsterList().at(i)))
						{
						case 1:
							currentStage->getMonsterList().at(i)->receiveHit(user->magicalDamage(magicPower) * 2, true);
							std::cout << "Dano: " << user->magicalDamage(magicPower) * 2 << std::endl;
							break;
						case 2:
							currentStage->getMonsterList().at(i)->receiveHit(user->magicalDamage(magicPower), true);
							std::cout << "Dano: " << user->magicalDamage(magicPower) << std::endl;
							break;
						case 3:
							std::cout << "MISS" << std::endl;
							break;
						}
					}
				}

				cooldown.stop();
				cooldown.start();
			}

			gameWindow->draw(image);
			image.setPosition(0, -9999);
		}
		else if (isCharged())
			cooldown.start();
	}
	// -------------------------------------------------------------------------
	// ------------------------------- Area ------------------------------------
	else if (category == 3)
	{
		if (!isCharged())
		{
			image.setPosition(user->getCenter().x - image.getLocalBounds().width / 2.0, user->getCenter().y - image.getLocalBounds().height / 2.0);

			if (cooldown.getTimeElapsed() % 500 >= 0 && cooldown.getTimeElapsed() % 500 <= 50)
			{
				for (int i = 0; i < currentStage->getMonsterList().size(); i++) {
					if (Collision::boundingBox(&image, &currentStage->getMonsterList().at(i)->getSprite()))
					{
						switch (user->magicChance(currentStage->getMonsterList().at(i)))
						{
						case 1:
							currentStage->getMonsterList().at(i)->receiveHit(user->magicalDamage(magicPower) * 2, true);
							std::cout << "Dano: " << user->magicalDamage(magicPower) * 2 << std::endl;
							break;
						case 2:
							currentStage->getMonsterList().at(i)->receiveHit(user->magicalDamage(magicPower), true);
							std::cout << "Dano: " << user->magicalDamage(magicPower) << std::endl;
							break;
						case 3:
							std::cout << "MISS" << std::endl;
							break;
						}
					}
				}
			}

			gameWindow->draw(image);
		}
	}
	// -------------------------------------------------------------------------
}

// Other Entities
void SpellCard::execute(Stage* currentStage, CombatEntity* user, CombatEntity* target, sf::RenderWindow* gameWindow)
{
	// -------------------------- Projectiles -----------------------------------
	if (category == 1)
	{
		// Movimentação e Colisão dos Projéteis
		int size = positions.size(), erases = 0;
		for (int i = 0; i < size; i++)
		{
			positions[i - erases].x += cos(angles[i - erases]) * 3;
			positions[i - erases].y += sin(angles[i - erases]) * 3;

			image.setPosition(positions[i - erases]);

			bool collide = false;

			if (Collision::boundingBox(&image, &target->getSprite()))
			{
				collide = true;

				switch (user->magicChance(target))
				{
				case 1:
					target->receiveHit(user->magicalDamage(magicPower) * 2, true);
					std::cout << "Dano(Critical): " << user->magicalDamage(magicPower) * 2 << std::endl;
					break;
				case 2:
					target->receiveHit(user->magicalDamage(magicPower), true);
					std::cout << "Dano: " << user->magicalDamage(magicPower) << std::endl;
					break;
				case 3:
					std::cout << "MISS" << std::endl;
					break;
				}
			}

			if (collide) {
				positions.erase(positions.begin() + (i - erases));
				angles.erase(angles.begin() + (i - erases));

				erases++;
			}
			else if (Physics::appMechanic(&image, currentStage)) {
				positions.erase(positions.begin() + (i - erases));
				angles.erase(angles.begin() + (i - erases));

				erases++;
			}

			gameWindow->draw(image);
		}
	}
	// -------------------------------------------------------------------------
	// ------------------------------- Beam ------------------------------------
	else if (category == 2)
	{
		if (user->isCasting())
		{
			if (cooldown.getTimeElapsed() >= 500)
			{
				if (Collision::SATBoundingBox(image, target->getSprite()))
				{
					switch (user->magicChance(target))
					{
					case 1:
						target->receiveHit(user->magicalDamage(magicPower) * 2, true);
						std::cout << "Dano: " << user->magicalDamage(magicPower) * 2 << std::endl;
						break;
					case 2:
						target->receiveHit(user->magicalDamage(magicPower), true);
						std::cout << "Dano: " << user->magicalDamage(magicPower) << std::endl;
						break;
					case 3:
						std::cout << "MISS" << std::endl;
						break;
					}
				}

				cooldown.stop();
				cooldown.start();
			}

			gameWindow->draw(image);
			image.setPosition(0, -9999);
		}
		else if (isCharged())
			cooldown.start();
	}
	// -------------------------------------------------------------------------
	// ------------------------------- Area ------------------------------------
	else if (category == 3)
	{
		if (!isCharged())
		{
			image.setPosition(user->getCenter().x - image.getLocalBounds().width / 2.0, user->getCenter().y - image.getLocalBounds().height / 2.0);

			if (cooldown.getTimeElapsed() % 500 >= 0 && cooldown.getTimeElapsed() % 500 <= 50)
			{
				if (Collision::boundingBox(&image, &target->getSprite()))
				{
					switch (user->magicChance(target))
					{
					case 1:
						target->receiveHit(user->magicalDamage(magicPower) * 2, true);
						std::cout << "Dano: " << user->magicalDamage(magicPower) * 2 << std::endl;
						break;
					case 2:
						target->receiveHit(user->magicalDamage(magicPower), true);
						std::cout << "Dano: " << user->magicalDamage(magicPower) << std::endl;
						break;
					case 3:
						std::cout << "MISS" << std::endl;
						break;
					}
				}
			}

			gameWindow->draw(image);
		}
	}
	// -------------------------------------------------------------------------
}