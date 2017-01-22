#ifndef _SPELLCARD_H_
#define _SPELLCARD_H_

#include "SFML\Graphics.hpp"
#include <vector>
#include "Card.h"
#include "Stage.h"
#include "CombatEntity.h"

// SpellCard - this class represents the Cards
// with magical power, that enables the Player
// to cast Spells. The Spells processing and graphical elements
// are also in this class.
class SpellCard : public Card
{
// -------- Attributes ---------- 
private:
	// General Attributes
	int category;				// Defines how the Spell works
	int magicPower;				// The Spell's magic power to calculate damage
	int castingTime;			// The time needed for the Spell to be casted (in milliseconds)
	int cooldownTime;			// The recharging time of the Spell (in milliseconds)
	int costMP;					// The MP Cost of the Spell

	// Rendering Attributes
	// Graphics
	sf::Sprite image;
	sf::Texture imageTexture;

	// Logics
	std::vector<sf::Vector2f> positions;
	std::vector<float> angles;
	Timer cooldown;

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTOR
	// Default Constructor
	SpellCard();

	// Custom Constructor
	SpellCard(int cardID);

	// GETTERS
	int getCategory();
	int getCastingTime();
	int getCooldownTime();
	float getCooldownPercentage() {
		return ((cooldown.getTimeElapsed() * 1.0 / cooldownTime) > 1) ? 1 : (cooldown.getTimeElapsed() * 1.0 / cooldownTime);
	}
	bool isCharged();
	int getCost();

	// This method is triggered when the Player presses the command button
	// long enough to the Spell be active. It works diferently for each category:
	// 1 (Projectile) = Adds a Projectile position, angle and velocity.
	// 2 (Beam) = Adds a Beam position and angle and set the Spell as active
	// 3 (Area) = Adds a Area position and set the Spell as active
	void use(sf::Vector2f position, float rotation, float angle);

	// These is the main method, it makes the Spell's happen while
	// the User is still doing other things
	// Player's Method
	void execute(Stage* currentStage, CombatEntity* user, sf::RenderWindow* gameWindow);

	// Other Entities
	void execute(Stage* currentStage, CombatEntity* user, CombatEntity* target, sf::RenderWindow* gameWindow);

// ------------------------------
};

#endif