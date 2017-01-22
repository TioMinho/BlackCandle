#ifndef _TIME_H_
#define _TIME_H_

#include <SFML\System\Clock.hpp>

class Timer
{
// -------- Attributes ----------
private:
	sf::Clock clock;
	bool paused;
	sf::Int32 timePaused;

// ------------------------------
// ---------- Methods -----------
public:
	Timer()
	{
		clock.restart();
		paused = true;
		timePaused = 0;
	}

	void start()
	{
		if (paused)
		{
			clock.restart();
			paused = false;
		}
	}

	void pause()
	{
		if (!paused) {
			timePaused += clock.getElapsedTime().asMilliseconds();
			paused = true;
		}
	}

	void stop()
	{
		timePaused = 0;
		paused = true;
	}

	sf::Int32 getTimeElapsed()
	{
		return (paused) ? timePaused : timePaused + clock.getElapsedTime().asMilliseconds();
	}

// ------------------------------
};

#endif;