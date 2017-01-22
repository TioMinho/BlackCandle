#ifndef _LOGQUEUE_H_
#define _LOGQUEUE_H_

#include <iostream>
#include "BattleLogNode.h"

class LogQueue
{
// -------- Attributes ---------- 
private:
	LogNode* header;
	int size, maxSize;

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Default Constructor
	LogQueue() {
		header = NULL;
		size = maxSize = 0;
	}

	// GETTERS
	LogNode* getHeader() {
		return header;
	}

	int getSize() {
		return size;
	}

	int getMaxSize() {
		return maxSize;
	}

	// SETTERS
	void setMaxSize(int maxSize) {
		this->maxSize = maxSize;
	}

	// Method to indicate if the Queue is empty
	bool isEmpty() {
		return (header == NULL);
	}

	sf::Vector2f getPosition(int index)
	{
		int limit = (index > size) ? size : index;
		LogNode* aux = header;

		int i;
		for (i = 0; i < limit; i++)
			aux = aux->getNext();

		return sf::Vector2f(aux->getPosition().x, aux->getPosition().y - 15 * (i + 1));

	}

	// Method to return a specific log from the Queue
	std::string getLog(int index) 
	{
		int limit = (index > size) ? size : index;
		LogNode* aux = header;

		for (int i = 0; i < limit; i++)
			aux = aux->getNext();

		return aux->getElement();
	}

	// Method to include a new Log to the Queue
	void enqueue(std::string element)
	{
		LogNode* newNode = new LogNode(element);

		if (isEmpty()) {
			header = newNode;
			size++;
		}
		else
		{
			LogNode* aux = header;

			while (aux->getNext() != NULL)
				aux = aux->getNext();

			aux->setNext(newNode);
			size++;

			if (maxSize != 0 && size > maxSize)
				dequeue();
		}
	}

	void enqueue(std::string element, sf::Vector2f position) 
	{
		BattleLogNode* newNode = new BattleLogNode(element, position);
		short index = 0;

		if (isEmpty()) {
			header = newNode;
			size++;
		}
		else
		{
			LogNode* aux = header;

			while (aux->getNext() != NULL) {
				aux = aux->getNext();
				index++;
			}

			aux->setNext(newNode);
			size++;

			if (maxSize != 0 && size > maxSize)
				dequeue();
		}
	}

	// Method to exclude a log from the Queue
	void dequeue()
	{
		if (!isEmpty())
		{
			LogNode* aux = header;

			header = header->getNext();

			delete(aux);
			size--;
		}
	}

	// Method to exclude all the logs from the Queue
	void clear()
	{
		for (int i = 0; i < size; i++)
			dequeue();
	}

// ------------------------------
};

#endif