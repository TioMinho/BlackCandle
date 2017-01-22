// *****************************************************
// ***** IMPLEMENTATION OF THE COMBATENTITY CLASS ******
// *****************************************************

#include "CombatEntity.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include <random>

// Constructors
// Standart Constructor
CombatEntity::CombatEntity()
{
	// RPG's Stats initialization
	level = 1;
	strength = defense = agility = dexterity = intelligence
		= resistance = luck = 10;
	HP = maxHP();
	MP = maxMP();
	experience = 0;

	// Combat variables initialization
	stance();
}

// Execute a physical attack in a specific enemy
// This does not identify the Enemies' position
void CombatEntity::attackF(CombatEntity* enemy){
}

// Execute a physical attack in a specific enemy
// This does not identify the Enemies' position
void CombatEntity::attackM(int magicIndex) {
}

// Stop and Pause the Timers, and set variables
// to indicate that the Entity isn't attacking, or
// his action was interrupted.
void CombatEntity::stance()
{
	attackTimer.pause();
	castingTimer.stop();
	casting = false;
}

// Modify the current HP, accordingly to a damage value
// from a attack decreased by the defense status or resistance.
// . "bool magic" -> indicates either or not the attack was magical.
void CombatEntity::receiveHit(int damage, bool magic) {
	HP -= (magic) ? resist(damage) : defend(damage);
	std::cout << "HP: " << HP << std::endl;
}

// --------------------------------------------
// ---------------- FORMULAS ------------------
// --------------------------------------------

// Calculates the Damage from a Magical Attack (No Modifiers Applied)
// The max damage an magic can cause values 9999
int CombatEntity::magicalDamage(int magicPower) {
	return (magicPower * 4 + (level * intelligence * magicPower / 32) > 9999) ?
		9999 : magicPower * 4 + (level * intelligence * magicPower / 32);
}

	// Calculates the Damage from a Physical Attack (No Modifiers Applied)
	// The max damage an attack can cause values 9999.
int CombatEntity::physicalDamage() {
	return (strength + ((pow(level, 2) * strength / 256) * 3 / 2) > 9999) ?
		9999 : strength + ((pow(level, 2) * strength / 256) * 3 / 2);
}

// Calculates the chance of a Physical Attacks to hit
// 1 = Critical Hit | 2 = Normal Hit | 3 = Miss
int CombatEntity::attackChance(CombatEntity* enemy)
{
	// -------------- Random Value Generation
	std::random_device generator;
	std::mt19937 rng(generator());
	std::uniform_int_distribution<int> distribution(0, 255);

	auto hitPoint = distribution(rng);
	// -------------------------------------

	// Verify the hit
	if (hitPoint <= luck)
		return 1;	// Critical Hit
	else if (hitPoint <= (168 + this->dexterity - enemy->agility))
		return 2;	// Normal Hit
	else
		return 3;	// Miss
}

// Calculates the chance of a Magical Attacks to hit
// 1 = Critical Hit | 2 = Normal Hit | 3 = Miss
int CombatEntity::magicChance(CombatEntity* enemy)
{
	// -------------- Random Value Generation
	std::random_device generator;
	std::mt19937 rng(generator());
	std::uniform_int_distribution<int> distribution(0, 255);

	auto hitPoint = distribution(rng);
	// -------------------------------------

	// Verify the hit
	if (hitPoint <= luck)
		return 1;	// Critical Hit
	else if (hitPoint <= (168 + this->dexterity - enemy->resistance))
		return 2;	// Normal Hit
	else
		return 3;	// Miss
}

// Decrease the damage received from a Physical Attack (Modifier)
// "defense"-based
int CombatEntity::defend(int damage) {
	return (damage * (255 - defense) / 256) + 1;
}

// Decrease the damage received from a Magical Attack (Modifier)
// "resistance"-based
int CombatEntity::resist(int damage) {
	return (damage * (255 - resistance) / 256) + 1;
}

// Calculates the Attack Speed Rate, as the delay between attacks
// The value is in milliseconds
int CombatEntity::attackSpeed() {
	return (1500 * (255 - agility) / 256) + 1;
}

// Calculates the time needed to cast determinated spell.
// The value is in milliseconds and is based in the spell's castingTime.
int CombatEntity::magicSpeed(int castingTime) {
	return (castingTime * (255 - dexterity) / 256) + 1;
}

// Determines the Max HP of the Entity, based on its defense.
int CombatEntity::maxHP() {
	return (50 * defense > 9999) ? 9999 : 50 * defense;
}

// Determines the Max MP of the Entity, based on its intelligence.
int CombatEntity::maxMP() {
	return (25 * intelligence > 5000) ? 5000 : 25 * intelligence;
}

// Calculates the experience needed to get to the next Level
// This is the interface of the recursive method
int CombatEntity::nextLevelXP() {
	return nextLevelXP(level + 1);
}

// Recursion method
int CombatEntity::nextLevelXP(int level)
{
	if (level == 1)
		return 0;
	else
		return (level - 1) * 50 + nextLevelXP(level - 1);
}