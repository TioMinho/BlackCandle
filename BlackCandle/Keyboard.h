#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <SFML/Window/Keyboard.hpp>
#include "Timer.h"

// Keyboard - This class is an extension of the 
// sf::Keyboard class. This one can handle single
// presses in any button.
class Keyboard : public sf::Keyboard
{
// -------- Attributes ---------- 
private:
	bool triggered[sf::Keyboard::KeyCount];
	Timer timer;

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Default Constructor
	Keyboard(){
		for (int i = 0; i < sf::Keyboard::KeyCount; i++)
			triggered[i] = false;

		timer.stop();
		timer.start();
	}

	bool clicked(sf::Keyboard::Key key) {
		if (isKeyPressed(key)) {
			if (!triggered[key]) {
				triggered[key] = true;
				return true;
			}
		}
		else
			triggered[key] = false;
		
		return false;
	}
	
	bool isKeyPressed(sf::Keyboard::Key key) {
		return sf::Keyboard::isKeyPressed(key);
	}

	bool isKeyPressed(sf::Keyboard::Key key, int delay) 
	{
		if (isKeyPressed(key) && timer.getTimeElapsed() >= delay)
		{
			timer.stop();
			timer.start();

			return true;
		}
		else
			return false;
	}
// ------------------------------
};

#endif