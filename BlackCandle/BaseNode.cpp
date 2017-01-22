// ********************************************************
// ********* IMPLEMENTATION OF THE BASENODE CLASS *********
// ********************************************************

#include "BaseNode.h"

// CONSTRUCTORS
// Standart Constructor
BaseNode::BaseNode()
{
	// Card Reference Initialization
	card = NULL;

	// Bounds Reference Initialization
	for (int i = 0; i < 8; i++) {
		bounds[i] = NULL;
	}
}

// GETTERS
EffectCard* BaseNode::getCard() {
	return card;
}

int BaseNode::getLevel() {
	int counter = 0;

	for (int i = 0; i < 8; i++)
		if (bounds[i] != NULL)
			counter++;

	return counter;
}

BaseNode* BaseNode::getNode(int index) {
	return bounds[index];
}

// SETTERS
void BaseNode::setCard(EffectCard* effectCard) {
	card = effectCard;
}

void BaseNode::setBound(BaseNode* node, int index) {
	bounds[index] = node;
}