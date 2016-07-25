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
	double speed;
	int health;
	sf::Vector2f direction;
	int type;
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


void randomEnemyType(enemy & spawnedEnemy)
{
	RandGen randGenerator;
	int type = randGenerator.RandInt(10);

	//-- Green enemies are normal and have an average speed --//
	if (type < 3)
	{
		spawnedEnemy.health = 2;
		spawnedEnemy.render.setFillColor(sf::Color::Green);
		spawnedEnemy.speed = 1.5;
	}

	//-- Cyan enemies are slow but tanky --//
	else if (type < 8)
	{
		spawnedEnemy.health = 3;
		spawnedEnemy.render.setFillColor(sf::Color::Cyan);
		spawnedEnemy.speed = 1;
	}

	//-- Red enemies are fast but squishy --//
	else
	{
		spawnedEnemy.health = 1;
		spawnedEnemy.render.setFillColor(sf::Color::Red);
		spawnedEnemy.speed = 3;
	}
}