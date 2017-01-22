// *****************************************************
// ********* IMPLEMENTATION OF THE STAGE CLASS *********
// *****************************************************

#include "Stage.h"
#include <fstream>
#include <sstream>

using namespace std;

// Standart
Stage::Stage()
{
	// Stage Identification Initialization
	this->stageID = "null";

	// Stage Tileset Initialization
	string temp = stageID;
	tileset.loadFromFile("BlackCandle/Stages/" + temp + "/tileset.png");

	// Stage Tilemap Sprite Initialization
	tileMap.setTexture(tileset);

	// Loading the TileMap and the CollisionMap
	loadMap();
	loadCollision();

	// ***************** TESTE
	for (int i = 0; i < 20; i++)
	{
		CombatEntity *monstro = new CombatEntity;
		monstro->setPosition(400, 400);
		listMonster.push_back(monstro);
	}
}

// Custom
Stage::Stage(const char* stageID)
{
	// Stage Identification Initialization
	this->stageID = stageID;

	// Stage Tileset Initialization
	string temp = stageID;
	tileset.loadFromFile("BlackCandle/Stages/" + temp + "/tileset.png");

	// Stage Tilemap Sprite Initialization
	tileMap.setTexture(tileset);

	// Loading the TileMap and the CollisionMap
	loadMap();
	loadCollision();
}

// GETTERS
std::string Stage::getID() {
	return stageID;
}

std::vector<Tile> &Stage::getCollisionMap() {
	return collisionMap;
}

std::vector<CombatEntity*> &Stage::getMonsterList() {
	return listMonster;
}

sf::Vector2f Stage::getSize() {
	return sf::Vector2f((mapTemplate[0].size() - 1) * 32, (mapTemplate.size() - 1) * 32);
}

// Method for loading the Tile Map from a ".bin" file
void Stage::loadMap()
{
	// Opening the tileMap ".bin" file
	string temp = stageID;
	ifstream file("BlackCandle/Stages/" + temp + "/" + temp + ".bin", ios::in | ios::binary);

	if (file.is_open())
	{
		// Temporary vector to compose the matrix
		vector<sf::Vector2i> tempMap;

		// Cleaning all the vectors
		mapTemplate.clear();
		tempMap.clear();

		// While the end of the ".bin" file...
		while (!file.eof())
		{
			// We read a line
			string line, value;
			getline(file, line);

			// Put it on a stream
			stringstream stream(line);

			while (getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					// We create two strings to represent the two-digit number
					// one for every number between the comma
					string xx = value.substr(0, value.find(','));
					string yy = value.substr(value.find(',') + 1);

					// So, we declare two variables to transform
					// "xx" and "yy" to actual numeric values
					int x, y;

					// And declare another two variables: i and j.
					// Those will tell if there was something than numbers
					// inside the value
					int i, j;

					for (i = 0; i < xx.length(); i++)
						if (!isdigit(xx[i]))
							break;

					for (j = 0; j < yy.length(); j++)
						if (!isdigit(xx[j]))
							break;

					// So, we can pass the values of "xx" and "yy"
					// to "x" and "y", but only if the test above
					// was sucessfull. Otherwise, "-1" will be assigned.
					x = (xx.length() == i) ? atoi(xx.c_str()) : -1;
					y = (yy.length() == j) ? atoi(yy.c_str()) : -1;

					// So we create the vector
					tempMap.push_back(sf::Vector2i(x, y));
				}
			}

			// We pass the to the matrix and prepare
			// the "tempMap" to the next line
			mapTemplate.push_back(tempMap);
			tempMap.clear();
		}

		// We close the ".bin" file
		file.close();
	}
	else
		// Error Message: the ".bin" was not opened!
		cout << "Unable to open \"" << stageID << ".bin\"! Stage was not loaded!" << endl;
}

//
void Stage::loadCollision() 
{
	// Opening the tileMap ".bin" file
	string temp = stageID;
	ifstream file("BlackCandle/Stages/" + temp + "/" + temp + "_c.bin", ios::in | ios::binary);

	if (file.is_open())
	{
		// Cleaning all the vectors
		collisionMap.clear();

		// We declare a Vector2i vector to
		// represent the axis to position the Tiles
		sf::Vector2i axis(0, 0);

		// While the end of the ".bin" file...
		while (!file.eof())
		{
			// We read a line
			string line, value;
			getline(file, line);

			// Put it on a stream
			stringstream stream(line);

			while (getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					// We create one string to represent a possible two-digit number
					string xx = value;
					
					// We declare one variable to receive the numeric
					// value of the Tile-Collision Class
					int classValue;

					// And declare another a variable: i;
					// This will tell if there was something than numbers
					// inside that value
					int i;

					for (i = 0; i < xx.length(); i++)
						if (!isdigit(xx[i]))
							break;

					// So, we can pass the values of "xx" and "yy"
					// to "x" and "y", but only if the test above
					// was sucessfull. Otherwise, "-1" will be assigned.
					classValue = (xx.length() == i) ? atoi(xx.c_str()) : -1;

					// So we create the vector, putting the class, size and position
					// of all the Collision-Maps Tiles that are not "-1" and "0" (Don't Collide)
					if (classValue != -1 && classValue != 0)
						collisionMap.push_back(Tile(classValue, 32, sf::Vector2f(axis.x * 32, axis.y * 32)));

					// We increment the "x" axis
					axis.x++;
				}
			}

			// We increment the "y" axis for the next line
			// and reset the "x" axis
			axis.y++;
			axis.x = 0;
		}

		// We close the ".bin" file
		file.close();
	}
	else
		// Error Message: the ".bin" was not opened!
		cout << "Unable to open \"" << stageID << "_c.bin\"! Stage was not loaded!" << endl;
}

// Method for rendering the TileMap in the Game's Window
void Stage::renderMap(sf::RenderWindow* gameWindow)
{
	for (int i = 0; i < mapTemplate.size(); i++)
	{
		for (int j = 0; j < mapTemplate[i].size(); j++)
		{
			if (mapTemplate[i][j].x != -1 && mapTemplate[i][j].y != -1) {
				tileMap.setPosition(j * 32, i * 32);

				tileMap.setTextureRect(sf::IntRect(mapTemplate[i][j].x * 32, mapTemplate[i][j].y * 32, 32, 32));

				gameWindow->draw(tileMap);
			}
		}
	}

	// *************** TESTE
	for (int k = 0; k < listMonster.size(); k++) 
	{
		gameWindow->draw(listMonster[k]->getSprite());
	}
}
