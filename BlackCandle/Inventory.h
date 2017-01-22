#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <iostream>
#include <vector>
#include "CardList.h"
#include "SpellCard.h"
#include "EffectCard.h"
#include "BaseCard.h"

// Inventory - class responsable for holding
// all the necessary systems for the Player
// to use the Game's Cards
class Inventory
{
// -------- Attributes ---------- 
private:
	int cardCredits;							// The current used for trading Cards in the Game
	BaseCard* baseCard;							// The Inventory's active BaseCard
	CardList activeSpells;						// The list of active spells in the Inventory
	CardList activeEffects;						// The list of equipped effect cards in the Inventory

	CardList baseList;							// The list os BaseCards in the Inventory
	CardList spellList;							// The list os SpellCards in the Inventory
	CardList effectList;						// The list os EffectCards in the Inventory

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Standart Constructor
	Inventory();

	// GETTERS
	int getCardCredits();
	CardList &getActiveSpells();
	CardList &getBaseList();
	CardList &getSpellList();
	CardList &getEffectList();
	BaseCard* getBaseCard();

	// SETTERS
	// (Some of them don't work as regular Setters methods)
	void setActiveSpell(int index, SpellCard* card);
	void setCardCredits(int quantity);
	void increaseCC(int quantity);
	void dereaseCC(int quantity);
	void setBaseCard(BaseCard* card);
	void addToList(BaseCard card);
	void addToList(SpellCard card);
	void addToList(EffectCard card);
	void removeCard(int cardID);

// ------------------------------
};

#endif