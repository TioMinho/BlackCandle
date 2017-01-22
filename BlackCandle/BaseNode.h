#ifndef _BASENODE_H_
#define _BASENODE_H_

#include <iostream>
#include "EffectCard.h"

// BaseNode - This class contains the attributes
// necessary for creating the Data Structure of the
// BaseCards
class BaseNode
{
// -------- Attributes ---------- 
private:
	EffectCard* card;
	BaseNode* bounds[8];

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Standart Constructor
	BaseNode();

	// GETTERS
	EffectCard* getCard();
	int getLevel();
	BaseNode* getNode(int index);

	// SETTERS
	void setCard(EffectCard* effectCard);
	void setBound(BaseNode* node, int index);

// ------------------------------
};

#endif