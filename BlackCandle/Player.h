#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include "Keyboard.h"
#include "CombatEntity.h"
#include "Inventory.h"
#include "Collision.h"
#include "HUD.h"
#include <math.h>

// Player - this class represents the user's interface
// with the Game and all the elements that he can control.
// This class holds the all Input, the Graphical Elements and
// Processing that refers to the Player's character and controls.
class Player : public CombatEntity
{
// -------- Attributes ---------- 
private:
	HUD hud;
	Inventory inventory;

	// *******TESTE
	short spellNumber;

// ------------------------------
// ---------- Methods -----------
public:
	// CONSTRUCTORS
	// Default Constructor
	Player() { 
		frame.y = 0; 
	}

	// GETTERS
	Inventory* getInventory() {
		return &inventory;
	}

	// This is the method that update all the Player's states, considering the Input
	// and Stage's conditions.
	void update(sf::RenderWindow* gameWindow, Keyboard* keyboard, Stage* currentStage) {
		input(keyboard, &currentStage->getMonsterList());

		execMovement();

		for (int i = 0; i < inventory.getActiveSpells().getSize(); i++)
			if (inventory.getActiveSpells().getSpellCard(i) != NULL)
				inventory.getActiveSpells().getSpellCard(i)->execute(currentStage, this, gameWindow);

		attackTimer.start();

		hud.updateBar(1, (HP * 1.0 / maxHP()));
		hud.updateBar(2, (MP * 1.0 / maxMP()));
		hud.updateBar(3, (attackTimer.getTimeElapsed() * 1.0 / attackSpeed()));
		hud.updateBar(5, (experience * 1.0 / nextLevelXP()));
	}

	// Handle the Player's in-game input
	void input(Keyboard* keyboard, std::vector<CombatEntity*> *enemyList)
	{
		// Walking mode
		if (!casting)
		{
			if (keyboard->isKeyPressed(Keyboard::Left)) {
				walkLeft();
				frame.y = 1;
				hud.leftAim();
			}
			else if (keyboard->isKeyPressed(Keyboard::Right)) {
				walkRight();
				frame.y = 0;
				hud.rightAim();
			}
			else
				stand();

			if (keyboard->isKeyPressed(Keyboard::Up))
				doJump();

			if (keyboard->isKeyPressed(Keyboard::Z) && attackTimer.getTimeElapsed() >= attackSpeed())
			{
				// We deal the damage to all the Enemy's from the List who are in the attack range
				if (enemyList != NULL)
				{
					for (int i = 0; i < enemyList->size(); i++)
						if (inRange(enemyList->at(i)))
							attackF(enemyList->at(i));
				}

				attackTimer.stop();	// The timer is reset for the next attack
			}
		}
		// Casting Mode
		else
		{
			// Can't move
			stand();

			// ************************ AIM
			if (keyboard->isKeyPressed(keyboard->Up))
				hud.upAim(frame.y, getCenter());
			else if (keyboard->isKeyPressed(keyboard->Down))
				hud.downAim(frame.y, getCenter());
		
			// *******************************
		}

		// Casting input
		// Spell chosen == Key Number - 27
		if (keyboard->isKeyPressed(keyboard->Num1))
			attackM(keyboard->Num1 - 27);
		else if (keyboard->isKeyPressed(keyboard->Num2))
			attackM(keyboard->Num2 - 27);
		else if (keyboard->isKeyPressed(keyboard->Num3))
			attackM(keyboard->Num3 - 27);
		else if (keyboard->isKeyPressed(keyboard->Num4))
			attackM(keyboard->Num4 - 27);
		else if (keyboard->isKeyPressed(keyboard->Num5))
			attackM(keyboard->Num5 - 27);
		else if (keyboard->isKeyPressed(keyboard->Num6))
			attackM(keyboard->Num6 - 27);
		else if (keyboard->isKeyPressed(keyboard->Num7))
			attackM(keyboard->Num7 - 27);
		else if (keyboard->isKeyPressed(keyboard->Num8))
			attackM(keyboard->Num8 - 27);
		else if (keyboard->isKeyPressed(keyboard->Num9))
			attackM(keyboard->Num9 - 27);
		// Only-Aim
		else if (keyboard->isKeyPressed(keyboard->X))
			casting = true;
		// No Spell is casting
		else  {
			casting = false;
			this->spellNumber = -1;
			castingTimer.stop();
			hud.updateBar(4, 0);
		}
	}

	// This method calculates either or not an Enemy is in the Physical range
	// to suffer from a physical attack
	bool inRange(CombatEntity* enemy)
	{
		sf::RectangleShape attackArea(sf::Vector2f(50, getSize().y + 70));
		attackArea.setPosition(sf::Vector2f(getPosition().x + getSize().x, getPosition().y - 35));

		if (frame.y == 0 || frame.y == 1)
			return Collision::boundingBox(&enemy->getSprite(), &attackArea);
		else if (frame.y == 2 || frame.y == 3)
			return Collision::boundingBox(&enemy->getSprite(), &attackArea);

		return false;
	}

	// Method responsable to execute a physical attack
	void attackF(CombatEntity* enemy)
	{
		// Verify nature of the hit
		switch (attackChance(enemy))
		{
		case 1:	// Critical Hit
			enemy->receiveHit(physicalDamage() * 2, false);
			std::cout << "Dano: " << physicalDamage() * 2 << std::endl;
			break;
		case 2:	// Normal Hit
			enemy->receiveHit(physicalDamage(), false);
			std::cout << "Dano: " << physicalDamage() << std::endl;
			break;
		case 3:	// Miss
			// EXIBIR MENSAGINHA DE MISS
			std::cout << "MISS" << std::endl;
			break;
		}
	}

	// Method responsable for executing a magical attack
	void attackM(int spellIndex) 
	{
		if (this->spellNumber != spellIndex && this->spellNumber != -1)
		{
			this->spellNumber = -2;
			castingTimer.stop();
			casting = false;
			hud.updateBar(4, 0);
		}

		// The conditions necessary for a Spell to be casted
		if (spellIndex < inventory.getActiveSpells().getSize() && 
			inventory.getActiveSpells().getSpellCard(spellIndex) != NULL &&
			inventory.getActiveSpells().getSpellCard(spellIndex)->isCharged() &&
			MP >= inventory.getActiveSpells().getSpellCard(spellIndex)->getCost() &&
			(this->spellNumber == spellIndex || this->spellNumber == -1))
		{
			// The casting starts
			casting = true;
			castingTimer.start();

			this->spellNumber = spellIndex;

			hud.updateBar(4,
				(castingTimer.getTimeElapsed() * 1.0 / inventory.getActiveSpells().getSpellCard(spellIndex)->getCastingTime()) + 0.05);

			// If the castingTimer surpass the time necessary for the skill do be casted
			// the Skill is used, the MP Cost is discounted and the Spell enters cooldown 
			if (castingTimer.getTimeElapsed() >= magicSpeed(inventory.getActiveSpells().getSpellCard(spellIndex)->getCastingTime()))
			{
				// The MP Cost is discounted
				MP -= inventory.getActiveSpells().getSpellCard(spellIndex)->getCost();
				
				// If the Spell is from the Category 2 (Beam) it does not enter on Cooldown
				if (inventory.getActiveSpells().getSpellCard(spellIndex)->getCategory() != 2) {
					this->spellNumber = -1;
					castingTimer.stop();
					casting = false;
					hud.updateBar(4, 0);
				}
				
				// The Spell is, so, used
				inventory.getActiveSpells().getSpellCard(spellIndex)->use(hud.getAimPosition(), hud.getAimRotation(), hud.getAimAngle());
			}
		}
	}

	// Method to receive a hit, subtracting the damage from the HP
	void receiveHit(int damage, bool magic) {
		damage = (magic) ? resist(damage) : defend(damage);
		HP -= damage;
	
		hud.addBattleLog(std::to_string(damage), sf::Vector2f(getCenter().x, getPosition().y), 0);
		
		std::cout << "HP: " << HP << std::endl;
	}

	// Methods responsable to add Itens to the Inventory
	// BaseCard
	void addToInventory(BaseCard baseCard) {
		inventory.addToList(baseCard);
	}

	// SpellCard
	void addToInventory(SpellCard spellCard) {
		inventory.addToList(spellCard);
	}

	// EffectCard
	void addToInventory(EffectCard effectCard) {
		inventory.addToList(effectCard);
	}

	// Renders the caracter's sprite and other elements.
	void render(sf::RenderWindow* gameWindow)
	{
		sprite.setTextureRect(sf::IntRect(0, frame.y * 57, 69, 57));
		gameWindow->draw(sprite);

		hud.render(gameWindow, this, &inventory.getActiveSpells());
	}
// ------------------------------
};

#endif