#ifndef _STAGE_H_
#define _STAGE_H_

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Character.h"
#include "CombatEntity.h"
#include "Tile.h"
#include <string>
#include <vector>

// Stage - class responsable for reading, loading 
// and rendering all the game's stages.
class Stage
{
// -------- Attributes ---------- 
private:
	// The Loading Basics
	std::string stageID;
	std::vector<std::vector<sf::Vector2i>> mapTemplate;
	std::vector<const char*> nextID;

	// The Rendering Basics
	sf::Sprite background[2];
	sf::Sprite tileMap;
	sf::Texture tileset;

	// The Collision Basics
	std::vector<Tile> collisionMap;

	// NPC's, Monsters, Secondary Elements, etc.
	// ***** UM VECTOR COM PONTEIRO PARA CADA UM TIPO
	std::vector<Character*> listNPC;
	std::vector<CombatEntity*> listMonster;

// ------------------------------
// --------- Methods ------------
public:
	// Constructors
	// Standart
	Stage();

	// Custom
	Stage(const char* stageID);

	// GETTERS
	std::string getID();
	std::vector<Tile> &getCollisionMap();
	std::vector<CombatEntity*> &getMonsterList();
	sf::Vector2f getSize();

	// Method for loading the Tile Map from a ".bin" file
	void loadMap();
	void loadCollision();
	void renderMap(sf::RenderWindow* gameWindow);

	// ***** FAZER MÉTODOS ESPECIAIS PARA CARREGAR CADA UMA
	// DAS LISTAS DE ELEMENTOS SECONDÁRIOS DO MAPA

// ------------------------------
};

#endif