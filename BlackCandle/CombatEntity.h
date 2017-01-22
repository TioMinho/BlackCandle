#ifndef _COMBATENTITY_H_
#define _COMBATENTITY_H_

#include "Character.h"
#include "Timer.h"

// CombatEntity - this class represents any entity
// in the Game that can fight or be fighted against
// It includes the Player itself.
class CombatEntity : public Character
{
// -------- Attributes ---------- 
protected:
	// ---------- RPG's Statuses ----------
	int level;				// The Entity's level
	int HP;					// The Entity's Health Points
	int MP;					// The Entity's Magic Points
	int strength;			// Strength determines the Physical Attack power of the Entity
	int defense;			// Defense minimizes the damage from Physical Attacks and increases the HP
	int agility;			// Agility determines the Physical Attack speed and avoid damage rate
	int dexterity;			// Dextery minimizes the chance of "miss" and reduce casting and cooldown time
	int intelligence;		// intelligence determines the Magical Attack power of the Entity and increases the MP
	int resistance;			// Resistance minimizes the damage from Magical Attacks and avoid damage rate
	int luck;				// Luck increases the chance for Critical Hits
	int experience;			// Experience determines the Level Progress of the Player
	// ------------------------------------

	// Combat Variables
	Timer attackTimer;						// The Physical Attack delay
	Timer castingTimer;						// The Magical Attack delay
	bool casting;							// Indicates that the Entity is casting a Spell

// ------------------------------
	
public:
	// Constructors
	// Standart Constructor
	CombatEntity();

	// Indicates if the CombatEntity is, or not, casting
	// a SpellCard
	bool isCasting() {
		return casting;
	}

	int getLevel() {
		return level;
	}

	// Determines the Max HP of the Entity, based on its defense.
	int maxHP();

	int getHP() {
		return HP;
	}

	// Determines the Max MP of the Entity, based on its intelligence.
	int maxMP();

	int getMP() {
		return MP;
	}

	// Returns the castingTimer
	Timer* getCastingTimer() {
		return &castingTimer;
	}

	// Execute a physical attack in a specific enemy
	// This does not identify the Enemies' position
	virtual void attackF(CombatEntity* enemy);

	// Execute a physical attack in a specific enemy
	// This does not identify the Enemies' position
	virtual void attackM(int magicIndex);

	// Stop and Pause the Timers, and set variables
	// to indicate that the Entity isn't attacking, or
	// his action was interrupted.
	void stance();

	// Modify the current HP, accordingly to a damage value
	// from a attack decreased by the defense status or resistance.
	// . "bool magic" -> indicates either or not the attack was magical.
	void receiveHit(int damage, bool magic);


	// ---------------- FORMULAS ------------------

	// Calculates the Damage from a Magical Attack (No Modifiers Applied)
	// The max damage an magic can cause values 9999
	int magicalDamage(int magicPower);

	// Calculates the chance of a Magical Attacks to hit
	// 1 = Critical Hit | 2 = Normal Hit | 3 = Miss
	int magicChance(CombatEntity* enemy);

protected:
	// Calculates the Damage from a Physical Attack (No Modifiers Applied)
	// The max damage an attack can cause values 9999.
	int physicalDamage();

	// Calculates the chance of a Physical Attacks to hit
	// 1 = Critical Hit | 2 = Normal Hit | 3 = Miss
	int attackChance(CombatEntity* enemy);

	// Decrease the damage received from a Physical Attack (Modifier)
	// "defense"-based
	int defend(int damage);

	// Decrease the damage received from a Magical Attack (Modifier)
	// "resistance"-based
	int resist(int damage);

	// Calculates the Attack Speed Rate, as the delay between attacks
	// The value is in milliseconds
	int attackSpeed();

	// Calculates the time needed to cast determinated spell.
	// The value is in milliseconds and is based in the spell's castingTime.
	int magicSpeed(int castingTime);

	// Calculates the experience needed to get to the next Level
	// This is the interface of the recursive method
	int nextLevelXP();

	// Recursion method
	int nextLevelXP(int level);

	// --------------------------------------------

// ------------------------------
};

#endif