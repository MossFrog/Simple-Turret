#include "Main.h"

int main()
{
	//-- Rendering Settings --//
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//-- Create the render Window --//
	sf::RenderWindow mainWindow(sf::VideoMode(1024, 700), "Turet Demo", sf::Style::Close, settings);
	mainWindow.setFramerateLimit(120);

	

	//-- Disable Key Repetition to enable button pressed events. --//
	//mainWindow.setKeyRepeatEnabled(false);

	//--------------------------//
	//-- Declarations Sections --//

	double PI = 3.14;

	//-- The variable is defined with its diameter --//
	sf::CircleShape turretBase(36);
	turretBase.setOrigin(36,36);
	turretBase.setFillColor(sf::Color::Blue);
	turretBase.setPosition(512, 350);

	sf::RectangleShape barrel;
	barrel.setOrigin(0, 6);
	barrel.setSize(sf::Vector2f(100, 12));
	barrel.setFillColor(sf::Color::Cyan);
	barrel.setPosition(512,350);

	int barrelAngle = 0;

	vector<sf::RectangleShape> projectileVector;

	//--------------------------//

	//-- Main Game Loop --//
	while (mainWindow.isOpen())
	{
		//-- Event Methods --//
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();

			if (event.key.code == sf::Keyboard::Down)
			{
				barrelAngle += 5;
				barrel.setRotation(barrelAngle);
			}

			if (event.key.code == sf::Keyboard::Up)
			{
				barrelAngle -= 5;
				barrel.setRotation(barrelAngle);
			}
		}

		//-- Get the mouse position --//
		sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);

		//-- Calculate the delta between the mouse and the origin --//
		double deltaX = mousePos.x - turretBase.getPosition().x;
		double deltaY = mousePos.y - turretBase.getPosition().y;

		//-- Update the barrel rotation --//
		barrelAngle = (atan2(deltaY, deltaX) * 180.0 / PI);
		barrel.setRotation(barrelAngle);

		mainWindow.clear(sf::Color::Black);

		mainWindow.draw(turretBase);
		mainWindow.draw(barrel);

		mainWindow.display();

	}


	return 0;
}