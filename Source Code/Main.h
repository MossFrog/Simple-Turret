#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <math.h>
#include <cmath>
#include "randgen.h"

using namespace std;

#define PI 3.14159265

struct projectile
{
	sf::Vector2f currentPos;
	sf::CircleShape render;
	int velocity;
	int angle;
	sf::Color bulletColor;
};

struct enemy
{
	sf::Vector2f currentPos;
	sf::CircleShape render;
	int speed;
	int health;
	sf::Vector2f direction;
};

sf::Vector2f randomSpawnPos()
{
	sf::Vector2f resultPos;
	RandGen randPole;
	RandGen randX;
	RandGen randY;
	int pole = randPole.RandInt(4);

	//-- Spawn Creatures at different Poles (N,S,E,W) --//
	if (pole == 0)
	{
		//-- North Spawn --//
		resultPos.x = randX.RandInt(1024);
		resultPos.y = -(randY.RandInt(500)) - 15;
		cout << "North" << endl;
	}

	else if (pole == 1)
	{
		//-- South Spawn --//
		resultPos.x = randX.RandInt(1024);
		resultPos.y = randY.RandInt(500) + 715;
		cout << "South" << endl;

	}

	else if (pole == 2)
	{
		//-- East Spawn --//
		resultPos.x = randX.RandInt(500) + 1024;
		resultPos.y = randY.RandInt(700);
		cout << "East" << endl;

	}

	else if (pole == 3)
	{
		//-- West Spawn --//
		resultPos.x = -(randX.RandInt(500) + 1024);
		resultPos.y = randY.RandInt(700);
		cout << "West" << endl;

	}

	return resultPos;
}

