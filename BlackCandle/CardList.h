#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include "ListNode.h"

// CardList - %!*(#%*(%
class CardList
{
// -------- Attributes ---------- 
private:
	ListNode* header;
	int size;

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Default Constructor
	CardList() 
	{
		// Header initialization
		header = NULL;

		// Size initialization (size can be read as "last position", too)
		size = 0;
	}

	// GETTERS
	ListNode* getHeader() {
		return header;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return (header == NULL);
	}

	ListNode* getNode(int position)
	{
		int limit = (position >= size) ? size : position;
		ListNode* aux = header;

		for (int i = 0; i < limit; i++)
			aux = aux->getNext();

		return aux;
	}

	BaseCard* getBaseCard(int position) {
		return getNode(position)->getBaseCard();
	}

	EffectCard* getEffectCard(int position) {
		return getNode(position)->getEffectCard();
	}

	SpellCard* getSpellCard(int position) {
		return getNode(position)->getSpellCard();
	}
	
	// ADDITION METHODS
	// Adds an card in the beggining of the List
	void addStart(int)
	{
		addStart(new ListNode());
		size++;
	}

	void addStart(BaseCard* card)
	{
		addStart(new ListNode(card));
		size++;
	}
	
	void addStart(EffectCard* card)
	{
		addStart(new ListNode(card));
		size++;
	}
	
	void addStart(SpellCard* card)
	{
		addStart(new ListNode(card));
		size++;
	}

	void addStart(ListNode* node)
	{
		if (isEmpty())
			header = node;
		else
		{
			node->setNext(header);
			header = node;
		}
	}

	// Adds an card in a specific position of the List
	// Obs.: [0] is the header.
	void addPosition(BaseCard* card, int position)
	{
		addPosition(new ListNode(card), position);
		size++;
	}

	void addPosition(EffectCard* card, int position)
	{
		addPosition(new ListNode(card), position);
		size++;
	}

	void addPosition(SpellCard* card, int position)
	{
		addPosition(new ListNode(card), position);
		size++;
	}

	void addPosition(ListNode* node, int position)
	{
		if (isEmpty())
			header = node;
		else
		{
			ListNode* aux = header;
			ListNode* previous = aux;

			for (int i = 0; i < position; i++) {
				previous = aux;
				aux = aux->getNext();
			}

			previous->setNext(node);
			node->setNext(aux);
		}
	}

	// Adds an card in the last position of the List
	// Obs.: this position correspond to the "size" value.
	void addEnd(BaseCard* card)
	{
		addEnd(new ListNode(card));
		size++;
	}

	void addEnd(EffectCard* card)
	{
		addEnd(new ListNode(card));
		size++;
	}

	void addEnd(SpellCard* card)
	{
		addEnd(new ListNode(card));
		size++;
	}

	void addEnd(ListNode* node)
	{
		if (isEmpty())
			header = node;
		else
		{
			ListNode* aux = header;

			for (int i = 0; i < size; i++)
				aux = aux->getNext();

			aux->setNext(node);
		}
	}

	// REMOVING METHODS
	// Remove a card from the start of the List
	void removeFirst() 
	{
		if (!isEmpty()) 
		{
			ListNode* deleted = header;

			header = header->getNext();

			delete(deleted);
			size--;
		}
	}

	// Remove a card from a specific position
	void removePosition(int position)
	{
		if (!isEmpty())
		{
			if (position == 0)
				removeFirst();
			else {
				ListNode* deleted = header;
				ListNode* previous = deleted;

				int limit = (position >= size) ? size : position;
				for (int i = 0; i < limit; i++) {
					previous = deleted;
					header = header->getNext();
				}

				previous->setNext(deleted->getNext());

				delete(deleted);
				size--;
			}
		}
	}

	// Remove a card from the last position
	void removeEnd()
	{
		if (!isEmpty())
		{
			ListNode* deleted = header;
			ListNode* previous = deleted;

			for (int i = 0; i < size; i++) {
				previous = deleted;
				header = header->getNext();
			}

			previous->setNext(deleted->getNext());

			delete(deleted);
			size--;
		}
	}

	// Remove all the cards
	void clear()
	{
		while (!isEmpty())
			removeFirst();
	}

// ------------------------------
};

#endif