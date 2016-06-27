#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <math.h>

using namespace std;

struct projectile
{
	sf::Vector2f currentPos;
	sf::CircleShape render;
	int velocity;
	int angle;
	sf::Color bulletColor;
};