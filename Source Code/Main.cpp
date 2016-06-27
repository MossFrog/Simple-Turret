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

	vector<projectile> projectileVector;

	//--------------------------//

	//-- Main Game Loop --//
	while (mainWindow.isOpen())
	{
		//-- Get the mouse position --//
		sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);

		//-- Calculate the delta between the mouse and the origin --//
		double deltaX = mousePos.x - turretBase.getPosition().x;
		double deltaY = mousePos.y - turretBase.getPosition().y;

		//-- Event Methods --//
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			projectile newBullet;
			newBullet.currentPos = turretBase.getPosition();
			newBullet.bulletColor = sf::Color::Red;
			newBullet.angle = (atan2(deltaY, deltaX) * 180.0 / PI);
			newBullet.render = sf::CircleShape(4);
			newBullet.render.setOrigin(2, 2);
			newBullet.render.setFillColor(newBullet.bulletColor);
			newBullet.velocity = 3;

			projectileVector.push_back(newBullet);
		}

		//-- Update all the bullet positions --//
		for (int i = 0; i < projectileVector.size(); i++)
		{
			projectileVector[i].currentPos = sf::Vector2f(projectileVector[i].currentPos.x + cos(projectileVector[i].angle*(0.017))*projectileVector[i].velocity,
				projectileVector[i].currentPos.y + sin(projectileVector[i].angle*(0.017))*projectileVector[i].velocity);

			projectileVector[i].render.setPosition(projectileVector[i].currentPos);


		}

		//-- Update the barrel rotation --//
		barrelAngle = (atan2(deltaY, deltaX) * 180.0 / PI);
		barrel.setRotation(barrelAngle);

		mainWindow.clear(sf::Color::Black);

		mainWindow.draw(turretBase);
		for (int i = 0; i < projectileVector.size(); i++)
		{
			mainWindow.draw(projectileVector[i].render);
		}
		mainWindow.draw(barrel);


		mainWindow.display();

	}


	return 0;
}