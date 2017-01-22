#ifndef _HUD_H_
#define _HUD_H_

#include <SFML/Graphics.hpp>
#include "LogQueue.h"
#include "CombatEntity.h"
#include "CardList.h"
#include "Timer.h"
#include <math.h>

// HUD - OAISnFOKANFLAKSNFLAKSF
class HUD
{
// -------- Attributes ---------- 
private:
	// Graphics 
	sf::Texture spriteSheet;			// The HUD's spritesheet
	sf::Sprite element;					// The HUD's elements (Principal, Bars, Logs, Cursor, etc)
	sf::RectangleShape bar;				// The bar to compose some of the HUD's elements
	sf::Sprite aim;						// The Aim Sprite of the Spell casting

	// Texts
	LogQueue logs;						// The Logs elements and organization
	LogQueue battleLog[2];				// The battle damages indicator logs (Damage received and damage given)
	sf::Font hudFont;					// The font to compose the sf::Text "logText" and "hudText"
	sf::Text logText;					// The graphic element of the Logs
	sf::Text hudText;					// The graphic element of the HUD

	// Logics
	Timer logTimer[2];					// The Timers to control the battleLogs queue
	float barFactor[5];					// The percentual size of the every HUD's Bar
	float aimRotation;					// The AIM Sprite rotation value

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Default Constructor
	HUD() 
	{
		// The Spritesheet initialization
		spriteSheet.loadFromFile("BlackCandle/Characters/hud.png");

		// The elements will be formed by the spriteSheet
		element.setTexture(spriteSheet);

		// The aim has a static image
		aim.setTexture(spriteSheet);
		aim.setTextureRect(sf::IntRect(0, 269, 10, 8));

		// The Logs will start with a initial message and a fixed maxSize
		logs.setMaxSize(5);
		logs.enqueue("* Player's Log");

		// Font and Text initialization
		hudFont.loadFromFile("BlackCandle/Characters/hudFont.ttf");

		logText.setFont(hudFont);
		logText.setColor(sf::Color::White);
		logText.setCharacterSize(10);

		hudText.setFont(hudFont);
		logText.setColor(sf::Color::White);

		// Initialize all Bar's Factor as 100% (1)
		for (int i = 0; i < 5; i++)
			barFactor[i] = 0;

		// Initializing the Battle Logs
		for (int i = 0; i < 2; i++) {
			battleLog[i].setMaxSize(10);
			logTimer[i].start();
		}

		// Initializing the AIM's rotation variables
		aimRotation = 339.25;
	}

	// Ups the AIM cursor
	void upAim(int frameY, sf::Vector2f center) {
		if (frameY == 0) {
			aimRotation -= 0.01;

			if (getAimAngle() < -90 || getAimAngle() > 90)
				aimRotation += 0.01;
		}
		else {
			aimRotation += 0.01;

			if (getAimAngle() < 90 || getAimAngle() > 270)
				aimRotation -= 0.01;
		}
	}

	void downAim(int frameY, sf::Vector2f center) {
		if (frameY == 0) {
			aimRotation += 0.01;

			if (getAimAngle() < -90 || getAimAngle() > 90)
				aimRotation -= 0.01;
		}
		else {
			aimRotation -= 0.01;

			if (getAimAngle() < 90 || getAimAngle() > 270)
				aimRotation += 0.01;
		}
	}

	void leftAim() {
		aimRotation = 179.08;
	}
	
	void rightAim() {
		aimRotation = 339.25;
	}

	sf::Vector2f getAimPosition() {
		return aim.getPosition();
	}

	float getAimRotation() {
		return aimRotation;
	}

	float getAimAngle() {
		if (cos(aimRotation) > 0)
			return asin(sin(aimRotation)) * (180 / 3.14159265);
		else
			return 180 - asin(sin(aimRotation)) * (180 / 3.14159265);
	}

	// Update one of the HUD's Bar
	// 1 - HP | 2 - MP | 3 - ATK | 4 - MAG | - 5 EXP
	void updateBar(int index, float factor) {
		this->barFactor[index - 1] = (factor > 1) ? 1 : factor;
	}

	void addLog(std::string text) {
		logs.enqueue(text);
	}

	void addBattleLog(std::string text, sf::Vector2f topCenter, bool inflicting) {
		battleLog[inflicting].enqueue(text, topCenter);
		logTimer[inflicting].stop();
		logTimer[inflicting].start();
	}

	// Render's the HUD
	void render(sf::RenderWindow* gameWindow, CombatEntity* player, CardList* activeSpells)
	{
		// HP's, MP's, ATK's, MAG's and NextLevel's Bars render
		// HP
		bar.setFillColor(sf::Color(216, 0, 33));
		bar.setSize(sf::Vector2f(barFactor[0] * 190, 16));
		bar.setPosition(15 + 46, 15 + 14);

		gameWindow->draw(bar);

		// MP
		bar.setFillColor(sf::Color(35, 153, 72));
		bar.setSize(sf::Vector2f(barFactor[1] * 190, 16));
		bar.setPosition(15 + 63, 15 + 47);

		gameWindow->draw(bar);

		// ATK
		bar.setFillColor(sf::Color(0, 125, 196));
		bar.setSize(sf::Vector2f(11, barFactor[2] * 95));
		bar.setPosition(15 + 16, 15 + 75);

		gameWindow->draw(bar);

		// MAG
		bar.setFillColor(sf::Color(0, 125, 196));
		bar.setSize(sf::Vector2f(11, barFactor[3] * 95));
		bar.setPosition(15 + 51, 15 + 75);

		gameWindow->draw(bar);

		// EXP
		bar.setFillColor(sf::Color(178, 0, 255));
		bar.setSize(sf::Vector2f(barFactor[4] * 200, 11));
		bar.setPosition(gameWindow->getSize().x - 15 - 211 + 5, gameWindow->getSize().y - 15 - 34 + 17);

		gameWindow->draw(bar);

		// The HUD Graphicals Elements Renderization
		// Principal
		element.setTextureRect(sf::IntRect(0, 0, 295, 187));
		element.setPosition(15, 15);

		gameWindow->draw(element);

		// Player's Level
		hudText.setCharacterSize(22);
		hudText.setString(std::to_string(player->getLevel()));
		hudText.setPosition(15 + 38 - (hudText.getLocalBounds().width / 2),
			15 + 46 - (hudText.getLocalBounds().height));

		gameWindow->draw(hudText);

		// Player's HP
		hudText.setCharacterSize(16);
		hudText.setString(std::to_string(player->getHP()) + "/" + std::to_string(player->maxHP()));
		hudText.setPosition(15 + 46 + 95 - (hudText.getLocalBounds().width / 2), 15 + 10);

		gameWindow->draw(hudText);

		// Player's MP
		hudText.setCharacterSize(16);
		hudText.setString(std::to_string(player->getMP()) + "/" + std::to_string(player->maxMP()));
		hudText.setPosition(15 + 63 + 95 - (hudText.getLocalBounds().width / 2), 15 + 43);

		gameWindow->draw(hudText);

		// Logs
		element.setTextureRect(sf::IntRect(34, 187, 211, 84));
		element.setPosition(15, gameWindow->getSize().y - 15 - 84);

		std::string logContent = "";
		for (int i = 0; i < logs.getSize(); i++)
			logContent += logs.getLog(i) + "\n";

		logText.setString(logContent);
		logText.setPosition(15 + 10, gameWindow->getSize().y - 15 - 84 + 23);

		gameWindow->draw(element);
		gameWindow->draw(logText);

		// Battle Logs
		for (int j = 0; j < 2; j++)
		{
			if (logTimer[j].getTimeElapsed() > 2000)
				battleLog[j].clear();

			for (int i = 0; i < battleLog[j].getSize(); i++)
			{
				hudText.setCharacterSize(20);
				hudText.setString(battleLog[j].getLog(i));
				hudText.setPosition(battleLog[j].getPosition(i));

				float alpha = (logTimer[j].getTimeElapsed() > 1500) ? 255 * ((logTimer[j].getTimeElapsed() % 1000) * 1.0 / 500) : 0;
				alpha = (alpha > 254) ? 254 : alpha;
				hudText.setColor(sf::Color(255, 255, 255, 255 - alpha));

				std::cout << "Transparency: " << std::to_string(hudText.getColor().a) << std::endl;

				gameWindow->draw(hudText);
			}
		}

		// NextLevel Bar
		element.setTextureRect(sf::IntRect(34, 271, 211, 34));
		element.setPosition(gameWindow->getSize().x - 15 - 211, gameWindow->getSize().y - 15 - 34);

		gameWindow->draw(element);

		// NextLevel Percentage
		hudText.setColor(sf::Color::White);
		hudText.setCharacterSize(16);
		std::string percentage = std::to_string(barFactor[4]);
		percentage = percentage.substr(0, 5); percentage += "%";
		hudText.setString(percentage);
		hudText.setPosition(gameWindow->getSize().x - 15 - 211 + 5 + (100 - hudText.getLocalBounds().width / 2),
							gameWindow->getSize().y - 15 - 34 + 10);

		gameWindow->draw(hudText);

		// SpellSlots
		for (int i = 0; i < activeSpells->getSize(); i++)
		{
			element.setPosition(15 + 295 + 30 + (15 + 34) * i, 30);

			if (activeSpells->getSpellCard(i) != NULL)
				element.setTextureRect(sf::IntRect(0, 187, 34, 41));
			else
				element.setTextureRect(sf::IntRect(0, 228, 34, 41));
			
			gameWindow->draw(element);
			
			// Spell Index
			hudText.setCharacterSize(14);
			hudText.setString(std::to_string(i + 1));
			hudText.setPosition(15 + 295 + 30 + (15 + 34) * i + (17 - hudText.getLocalBounds().width / 2), 
								30 + 25 - hudText.getLocalBounds().height);

			gameWindow->draw(hudText);

			// Cooldown Bar
			if (activeSpells->getSpellCard(i) != NULL) {
				bar.setFillColor(sf::Color(0, 0, 0, 200));
				bar.setPosition((15 + 295 + 30 + (15 + 34) * i + 5), 30 + 5);
				bar.setSize(sf::Vector2f(24 * (1 - activeSpells->getSpellCard(i)->getCooldownPercentage()), 31));

				gameWindow->draw(bar);
			}
		}

		// Cursor Update and Render
		aim.setPosition(sf::Vector2f(player->getCenter().x + cos(aimRotation) * 50, player->getCenter().y + sin(aimRotation) * 50));
		aim.setRotation(getAimAngle());

		if (player->isCasting())
			gameWindow->draw(aim);
	}

// ------------------------------
};

#endif