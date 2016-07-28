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
	mainWindow.setKeyRepeatEnabled(false);

	//--------------------------//
	//-- Declarations Sections --//

	//-- The variable is defined with its diameter --//
	sf::CircleShape turretBase(36);
	turretBase.setOrigin(36, 36);
	turretBase.setFillColor(sf::Color::Blue);
	turretBase.setPosition(512, 350);

	sf::RectangleShape barrel;
	barrel.setOrigin(0, 6);
	barrel.setSize(sf::Vector2f(100, 12));
	barrel.setFillColor(sf::Color::Cyan);
	barrel.setPosition(512, 350);

	sf::RectangleShape healthBar;
	healthBar.setSize(sf::Vector2f(200, 30));
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setPosition(30, 30);


	int barrelAngle = 0;

	vector<projectile> projectileVector;
	vector<enemy> enemyVector;

	sf::Clock enemySpawnClock;

	sf::Clock fireClock;
	int fireRate = 150;

	//-- Menu Debugging Clock to prevent multiple click registration --//
	sf::Clock menuDebugClock;
	menuDebugClock.restart();

	//-- Player and Game Variables --//
	int playerHealth = 100;
	int playerBank = 0;
	int playerDamage = 1;
	int playerScore = 0;


	int enemiesKilled = 0;

	int gameState = 0;

	/* //-- Game States --//
	0 - Menu
	1 - Playing
	2 - Break
	3 - Game Over
	*/

	//-- Random Generation Elements --//

	//-- Sprites, Textures and Fonts --//

	sf::Texture barrelTexure;
	barrelTexure.loadFromFile("Barrel.png");

	sf::Sprite barrelSprite;
	barrelSprite.setTexture(barrelTexure);
	barrelSprite.setScale(2, 2);
	barrelSprite.setOrigin(17, 41);
	barrelSprite.setPosition(barrel.getPosition());

	sf::Texture backGroundTexture;
	backGroundTexture.loadFromFile("Terrain.PNG");

	sf::Sprite backGroundSprite;
	backGroundSprite.setTexture(backGroundTexture);
	backGroundSprite.setScale(1.24, 1.19);
	backGroundSprite.setPosition(-1, -1);

	sf::Texture turretBaseTexture;
	turretBaseTexture.loadFromFile("TurretBase.png");

	sf::Sprite turretBaseSprite;
	turretBaseSprite.setTexture(turretBaseTexture);
	turretBaseSprite.setOrigin(10, 10);
	turretBaseSprite.setScale(3.6, 3.6);
	turretBaseSprite.setPosition(512, 350);

	sf::Font mainFont;
	if (!mainFont.loadFromFile("monumentA.ttf"))
	{
	}
	else
	{
		cout << "Loaded 'monumentA.ttf'" << endl;
	}

	sf::Text startText;
	sf::Text titleText;
	sf::Text highScoresText;

	startText.setFont(mainFont);
	titleText.setFont(mainFont);
	highScoresText.setFont(mainFont);

	titleText.setString("Simple Turret");
	titleText.setCharacterSize(80);
	titleText.setPosition(200, 150);

	startText.setFont(mainFont);
	startText.setCharacterSize(60);
	startText.setString("Start");
	startText.setPosition(400, 250);

	highScoresText.setFont(mainFont);
	highScoresText.setCharacterSize(60);
	highScoresText.setString("Highscores");
	highScoresText.setPosition(300, 350);

	sf::Text bankText;
	bankText.setFont(mainFont);
	bankText.setString("Bank: " + itoa(playerBank));
	bankText.setPosition(790, 30);
	bankText.setCharacterSize(40);

	sf::Text scoreText;
	scoreText.setFont(mainFont);
	scoreText.setString("Score: " + itoa(playerScore));
	scoreText.setPosition(30, 60);
	scoreText.setCharacterSize(40);

	sf::Text gameOverText;
	gameOverText.setFont(mainFont);
	gameOverText.setString("Game Over");
	gameOverText.setPosition(250, 150);
	gameOverText.setCharacterSize(80);

	sf::Text returnToMenuText;
	returnToMenuText.setFont(mainFont);
	returnToMenuText.setString("Main Menu");
	returnToMenuText.setPosition(300, 250);
	returnToMenuText.setCharacterSize(60);

	sf::Text retryText;
	retryText.setFont(mainFont);
	retryText.setString("Retry");
	retryText.setPosition(375, 340);
	retryText.setCharacterSize(60);

	gameState = 3;

	//--------------------------//

	//-- Audio Section --//
	sf::SoundBuffer shotBuffer;
	shotBuffer.loadFromFile("Shoot.wav");

	sf::Sound shotSound;
	shotSound.setBuffer(shotBuffer);

	fireClock.restart();
	enemySpawnClock.restart();

	//-- Main Game Loop --//
	while (mainWindow.isOpen())
	{
		//-- Get the mouse position --//
		sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);

		//-- Calculate the delta between the mouse and the origin --//
		double deltaX = mousePos.x - turretBase.getPosition().x;
		double deltaY = mousePos.y - turretBase.getPosition().y;

		//-- Update the barrel rotation --//
		barrelAngle = (atan2(deltaY, deltaX) * 180.0 / PI);
		barrel.setRotation(barrelAngle);

		//-- Update the text elements --//
		bankText.setString("Bank: " + itoa(playerBank));
		scoreText.setString("Score: " + itoa(playerScore));

		//-- Update the health bar --//
		healthBar.setSize(sf::Vector2f(playerHealth * 2, 30));

		if (playerHealth <= 25)
		{
			healthBar.setFillColor(sf::Color::Red);
		}
		else if (playerHealth <= 50)
		{
			healthBar.setFillColor(sf::Color::Yellow);
		}
		else if (playerHealth > 50)
		{
			healthBar.setFillColor(sf::Color::Green);
		}


		//-- Check if the player has perished in battle. --//
		if (playerHealth <= 0)
		{
			gameState = 3;
		}

		//-- Event Methods --//
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();

			if (event.type == sf::Event::KeyPressed)
			{

			}
		}

		//-- Menu Buttons and Methods --//
		if (startText.getGlobalBounds().contains(mousePos.x, mousePos.y) && gameState == 0)
		{
			startText.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuDebugClock.getElapsedTime().asMilliseconds() > 500)
			{
				enemyVector.clear();
				projectileVector.clear();
				playerHealth = 100;
				playerBank = 0;
				playerScore = 0;
				menuDebugClock.restart();
				gameState = 1;
			}
		}

		else
		{
			startText.setColor(sf::Color::White);
		}

		if (highScoresText.getGlobalBounds().contains(mousePos.x, mousePos.y) && gameState == 0)
		{
			highScoresText.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

			}
		}

		else
		{
			highScoresText.setColor(sf::Color::White);
		}

		if (returnToMenuText.getGlobalBounds().contains(mousePos.x, mousePos.y) && gameState == 3)
		{
			returnToMenuText.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//-- Restart all variables and clear necessary memory --//
				enemyVector.clear();
				projectileVector.clear();
				playerHealth = 100;
				playerBank = 0;
				playerScore = 0;
				menuDebugClock.restart();
				gameState = 0;
			}
		}

		else
		{
			returnToMenuText.setColor(sf::Color::White);
		}

		if (retryText.getGlobalBounds().contains(mousePos.x, mousePos.y) && gameState == 3)
		{
			retryText.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//-- Restart all variables and clear necessary memory --//
				enemyVector.clear();
				projectileVector.clear();
				playerHealth = 100;
				playerBank = 0;
				playerScore = 0;
				menuDebugClock.restart();
				gameState = 1;
			}
		}

		else
		{
			retryText.setColor(sf::Color::White);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuDebugClock.getElapsedTime().asMilliseconds() > 500)
		{
			//-- If the mouse button is pressed and the turret timer is ready add a new bullet to the projectile Vector --//

			if ((fireClock.getElapsedTime().asMilliseconds() >= 300 - fireRate + 100) && gameState == 1)
			{
				projectile newBullet;
				newBullet.currentPos = turretBase.getPosition();
				newBullet.bulletColor = sf::Color::Red;
				newBullet.angle = barrelAngle;
				newBullet.render = sf::CircleShape(4);
				newBullet.render.setOrigin(4, 4);
				newBullet.render.setFillColor(newBullet.bulletColor);
				newBullet.velocity = 7;

				//-- Push the bullet to end of the barrel --//
				newBullet.currentPos = sf::Vector2f(newBullet.currentPos.x + cos(newBullet.angle*(0.01750)) * 75,
					newBullet.currentPos.y + sin(newBullet.angle*(0.01750)) * 75);


				projectileVector.push_back(newBullet);

				//-- Play the shooting sound --//
				shotSound.play();

				fireClock.restart();
			}
		}

		//-- Update all the bullet positions --//
		for (int i = 0; i < projectileVector.size(); i++)
		{
			if (gameState == 1)
			{

				projectileVector[i].currentPos = sf::Vector2f(projectileVector[i].currentPos.x + cos(projectileVector[i].angle*(0.01750))*projectileVector[i].velocity,
					projectileVector[i].currentPos.y + sin(projectileVector[i].angle*(0.01750))*projectileVector[i].velocity);

				projectileVector[i].render.setPosition(projectileVector[i].currentPos);

				//-- If the bullet position is out of the bounds of the render window then delete it --//
				if (projectileVector[i].currentPos.x > 1024 || projectileVector[i].currentPos.x < 0)
				{
					projectileVector.erase(projectileVector.begin() + i);
				}

				else if (projectileVector[i].currentPos.y > 700 || projectileVector[i].currentPos.y < 0)
				{
					projectileVector.erase(projectileVector.begin() + i);
				}

				//-- Do a collision test with all enemies --//
				for (int j = 0; j < enemyVector.size(); j++)
				{
					double tempDistance = sqrt(pow((enemyVector[j].currentPos.x - projectileVector[i].currentPos.x), 2) + pow((enemyVector[j].currentPos.y - projectileVector[i].currentPos.y), 2));
					if (tempDistance < 15)
					{
						//-- If a collision is detected remove the projectile and damage the enemy --//
						//-- If the enemy health is zero or lower then also remove the enemy --//
						enemyVector[j].health -= 1;

						//-- Additional "Slowing" Effect --//
						enemyVector[j].speed = enemyVector[j].speed * 0.5;

						projectileVector.erase(projectileVector.begin() + i);

						if (enemyVector[j].health <= 0)
						{
							if (enemyVector[j].type < 3)
							{
								playerBank += 15;
								playerScore += 150;
							}

							//-- Cyan enemies are slow but tanky --//
							else if (enemyVector[j].type < 8)
							{
								playerBank += 20;
								playerScore += 250;
							}

							//-- Red enemies are fast but squishy --//
							else
							{
								playerBank += 30;
								playerScore += 350;
							}

							enemyVector.erase(enemyVector.begin() + j);
							enemiesKilled += 1;
						}
					}
				}
			}
		}


		//-- Spawn a new enemy --//
		if ((enemySpawnClock.getElapsedTime().asMilliseconds() >= (1500 - (enemiesKilled * 3))) && gameState == 1)
		{
			enemy newEnemy;

			newEnemy.currentPos = randomSpawnPos();
			newEnemy.render.setPosition(newEnemy.currentPos);
			newEnemy.render.setRadius(15);

			randomEnemyType(newEnemy);

			newEnemy.render.setOrigin(15, 15);

			//-- We calculate each enemies xSpeed and ySpeed and then normalize it against the distance to set the speed to a constant value of 1 --//
			double distance = sqrt(pow((newEnemy.currentPos.x - turretBase.getPosition().x), 2) + pow((newEnemy.currentPos.y - turretBase.getPosition().y), 2));
			double xSpeed = (newEnemy.currentPos.x - turretBase.getPosition().x) / distance * newEnemy.speed;
			double ySpeed = (newEnemy.currentPos.y - turretBase.getPosition().y) / distance * newEnemy.speed;

			newEnemy.direction = sf::Vector2f(xSpeed, ySpeed);
			enemyVector.push_back(newEnemy);
			enemySpawnClock.restart();
		}

		//-- Enemy update loop --//
		for (int i = 0; i < enemyVector.size(); i++)
		{
			if (gameState == 1)
			{
				double currentDistance = sqrt(pow((enemyVector[i].currentPos.x - turretBase.getPosition().x), 2) + pow((enemyVector[i].currentPos.y - turretBase.getPosition().y), 2));
				if (currentDistance > 50)
				{
					enemyVector[i].currentPos = enemyVector[i].currentPos - enemyVector[i].direction;
				}

				else if (currentDistance <= 50)
				{
					//-- In this case the enemy has reached the turret base, damage the player and remove the enemy --//
					enemyVector.erase(enemyVector.begin() + i);
					playerHealth -= 5;

					if (playerHealth <= 0)
					{
						//-- Game over State --//
						playerHealth = 0;
					}
				}

				enemyVector[i].render.setPosition(enemyVector[i].currentPos);
			}
		}

		barrelSprite.setRotation(barrel.getRotation() + 90);

		mainWindow.clear(sf::Color::Black);

		mainWindow.draw(backGroundSprite);

		if (gameState == 1)
		{
			for (int i = 0; i < projectileVector.size(); i++)
			{
				mainWindow.draw(projectileVector[i].render);
			}

			for (int i = 0; i < enemyVector.size(); i++)
			{
				mainWindow.draw(enemyVector[i].render);
			}


			//-- Uncomment this section to render the barrel and base entity --//
			//mainWindow.draw(barrel);
			//mainWindow.draw(turretBase);

			mainWindow.draw(turretBaseSprite);
			mainWindow.draw(barrelSprite);

			mainWindow.draw(bankText);
			mainWindow.draw(healthBar);
			mainWindow.draw(scoreText);
		}

		else if (gameState == 0)
		{
			mainWindow.draw(titleText);
			mainWindow.draw(startText);
			mainWindow.draw(highScoresText);
		}

		else if (gameState == 3)
		{
			mainWindow.draw(gameOverText);
			mainWindow.draw(returnToMenuText);
			mainWindow.draw(retryText);
		}

		mainWindow.display();

	}

	return 0;
}