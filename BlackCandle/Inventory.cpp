// *********************************************************
// ********* IMPLEMENTATION OF THE INVENTORY CLASS *********
// *********************************************************

#include "Inventory.h"

// CONSTRUCTORS
// Standart Constructor
Inventory::Inventory()
{
	// General initialization
	cardCredits = 0;

	activeSpells.clear();
	baseList.clear();
	spellList.clear();
	effectList.clear();

	baseCard = NULL;
}

// GETTERS
int Inventory::getCardCredits() {
	return cardCredits;
}

CardList &Inventory::getActiveSpells() {
	return activeSpells;
}

CardList &Inventory::getBaseList() {
	return baseList;
}

CardList &Inventory::getSpellList() {
	return spellList;
}

CardList &Inventory::getEffectList() {
	return effectList;
}

BaseCard* Inventory::getBaseCard() {
	return baseCard;
}

// SETTERS
// (Some of them don't work as regular Setters methods)
void Inventory::setActiveSpell(int index, SpellCard* card) {
	activeSpells.getNode(index)->setCard(card);
}

void Inventory::setCardCredits(int quantity) {
	cardCredits = quantity;
}

void Inventory::increaseCC(int quantity) {
	cardCredits += quantity;
}

void Inventory::dereaseCC(int quantity) {
	cardCredits - +quantity;
}

void Inventory::setBaseCard(BaseCard* card) 
{
	if (card == NULL)
	{
		if (baseCard != NULL)
			baseCard->clearStructure();

		activeSpells.clear();
		baseCard = NULL;
		return;
	}

	if (baseCard != NULL)
		baseCard->clearStructure();

	activeSpells.clear();
	for (int j = 0; j < card->getSpellSlots(); j++)
		activeSpells.addStart(NULL);

	baseCard = card;
	baseCard->loadStructure();
}

void Inventory::addToList(BaseCard card) {
	baseList.addStart(new BaseCard(card));
}

void Inventory::addToList(SpellCard card) {
	spellList.addStart(new SpellCard(card));
}

void Inventory::addToList(EffectCard card) {
	effectList.addStart(new EffectCard(card));
}

void Inventory::removeCard(int cardID) {
	int i;

	for (i = 0; i < baseList.getSize(); i++) {
		if (baseList.getBaseCard(i)->getID() == cardID) {
			baseList.removePosition(i);
			return;
		}
	}

	for (i = 0; i < spellList.getSize(); i++) {
		if (spellList.getSpellCard(i)->getID() == cardID) {
			spellList.removePosition(i);
			return;
		}
	}

	for (i = 0; i < effectList.getSize(); i++) {
		if (effectList.getEffectCard(i)->getID() == cardID) {
			effectList.removePosition(i);
			return;
		}
	}
}