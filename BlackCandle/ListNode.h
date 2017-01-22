#ifndef _LISTNODE_H_
#define _LISTNODE_H_

#include "iostream"
#include "BaseCard.h"
#include "EffectCard.h"
#include "SpellCard.h"

// ListNode - this class represents a Node used
// to create the "ListNode"s linked list.
class ListNode
{
// -------- Attributes ---------- 
private:
	// Cards' Pointers
	BaseCard* base;
	EffectCard* effect;
	SpellCard* spell;

	// Node Pointer
	ListNode* next;

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Default Constructor
	ListNode() 
	{
		// All the attributes are initialized as NULL
		base = NULL;
		effect = NULL;
		spell = NULL;

		next = NULL;
	}

	// Custom Constructor
	ListNode(BaseCard* base)
	{
		// All the attributes are initialized as NULL, minus the BaseCard pointer
		this->base = base;
		effect = NULL;
		spell = NULL;

		next = NULL;
	}

	// Custom Constructor
	ListNode(EffectCard* effect)
	{
		// All the attributes are initialized as NULL, minus the BaseCard pointer
		base = NULL;
		this->effect = effect;
		spell = NULL;

		next = NULL;
	}

	// Custom Constructor
	ListNode(SpellCard* spell)
	{
		// All the attributes are initialized as NULL, minus the BaseCard pointer
		base = NULL;
		effect = NULL;
		this->spell = spell;

		next = NULL;
	}

	// GETTERS
	BaseCard* getBaseCard() {
		return base;
	}

	EffectCard* getEffectCard() {  
		return effect;
	}

	SpellCard* getSpellCard() {
		return spell;
	}

	ListNode* getNext() {
		return next;
	}

	// SETTERS
	void setCard(BaseCard* card) {
		this->base = card;
	}

	void setCard(EffectCard* card) {
		this->effect = card;
	}

	void setCard(SpellCard* card) {
		this->spell = card;
	}

	void setNext(ListNode* next) {
		this->next = next;
	}

// ------------------------------
};

#endif