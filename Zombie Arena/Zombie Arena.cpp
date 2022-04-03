// Zombie Arena.cpp

#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "ZombieArena.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h" 

using namespace sf;

int main()
{
	// Here is the instance of TextureHolder
	TextureHolder holder;

	// The game will always be in one of 4 states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

	// Start with the GAME_OVER state
	State state = State::GAME_OVER;

	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y)
		, "Zombie Arena", Style::Fullscreen);


	// Create an SFML view for the main action
	View mainView(sf::FloatRect(0, 0
		, resolution.x, resolution.y));

	// Clock for timing everything
	Clock clock;

	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;

	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	IntRect arena;

	// Create the background
	VertexArray background;

	// Load the texture for our background vertex array
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background_sheet.png");

	// Prepare for a horde of zombies!!
	int numZombies;
	int numZombiesAlive;

	Zombie* zombies = nullptr;

	// 100 bullets should do
	Bullet bullets[100];

	int   currentBullet = 0;
	int   bulletsSpare  = 24;
	int   bulletsInClip = 6;
	int	  clipSize      = 6;
	float fireRate      = 1;

	// When was teh fire button last pressed
	Time lastPressed;

	// Hide the mouse pointer and replace with cross-hair
	window.setMouseCursorVisible(true);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture
		("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	// Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	// About the game
	int score   = 0;
	int hiScore = 0;

	// For the home/game over screen
	Sprite spriteGameover;
	Texture textureGameOver = TextureHolder::GetTexture("graphics/bg.png");
	spriteGameover.setTexture(textureGameOver);
	spriteGameover.setPosition(resolution.x / 4, resolution.y / 4);

	// Create a view for the HUD
	View hudView(sf::FloatRect(0, 0
		, resolution.x, resolution.y));

	// Create a sprite for the ammo icon
	Sprite spriteAmmoIcon;
	Texture textureAmmoIcon = TextureHolder::GetTexture
		("graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(resolution.x / 2 - 50, resolution.y - 400);

	// Load the font
	Font font;
	font.loadFromFile("fonts/zombiecontrolcond.ttf");

	// Paused
	Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(resolution.x / 2 - 400, resolution.y / 2 - 200);
	pausedText.setString("Press Enter \nto continue");

	// Game over
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(resolution.x / 2 - 400, resolution.y / 2 - 200);
	gameOverText.setString("Press Enter to Play");

	// Leveling up
	Text levelingUpText;
	levelingUpText.setFont(font);
	levelingUpText.setCharacterSize(80);
	levelingUpText.setFillColor(Color::White);
	levelingUpText.setPosition(resolution.x / 4, resolution.y / 4);
	std::stringstream levelUpStream;
	levelUpStream << "1- Increased rate of fire"
		<< "\n2- Increased clip size(next reload)"
		<< "\n3- Increased max health"
		<< "\n4- Increased run speed"
		<< "\n5- More and better health pickups"
		<< "\n6- More and better ammo pickups";
	levelingUpText.setString(levelUpStream.str());

	// Ammo
	Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(resolution.x / 2, resolution.y - 400);

	// Score
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 0);

	// Load the high score from a text file
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		// Reads the data
		inputFile >> hiScore;
		inputFile.close();
	}

	// High Score
	Text highScoreText;
	highScoreText.setFont(font);
	highScoreText.setCharacterSize(55);
	highScoreText.setFillColor(Color::White);
	highScoreText.setPosition(resolution.x / 2 - 200, 0);
	std::stringstream s;
	s << "High Score:" << hiScore;
	highScoreText.setString(s.str());

	// Zombies remaining
	Text zombiesRemainingText;
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition(resolution.x - 600, resolution.y - 600);
	zombiesRemainingText.setString("Zombies: 100");

	// Wave number
	int wave = 0;
	Text waveNumberText;
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(Color::White);
	waveNumberText.setPosition(resolution.x - 600, resolution.y - 400);
	waveNumberText.setString("Wave: 0");

	// Health bar
	RectangleShape healthBar;
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(resolution.x /2, resolution.y - 600);
	
	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;

	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;

	// Prepare the hit sound
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	Sound hit;
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	SoundBuffer splatBuffer;
	splatBuffer.loadFromFile("sound/splat.wav");
	Sound splat;
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sound/shoot.wav");
	Sound shoot;
	shoot.setBuffer(shootBuffer);

	// Prepare reload sound
	SoundBuffer reloadBeffer;
	reloadBeffer.loadFromFile("sound/reload.wav");
	Sound reload;
	reload.setBuffer(reloadBeffer);

	// Prepare power up sound
	SoundBuffer powerUpBuffer;
	powerUpBuffer.loadFromFile("sound/powerup.wav");
	Sound powerUp;
	powerUp.setBuffer(powerUpBuffer);

	// Prepare pickup sound
	SoundBuffer pickupBuffer;
	pickupBuffer.loadFromFile("sound/pickup.wav");
	Sound pickup;
	pickup.setBuffer(pickupBuffer);

	// Prepare reload failed sound
	SoundBuffer reloadFailedBuffer;
	reloadFailedBuffer.loadFromFile("sound / reload_failed.wav");
	Sound reloadFailed;
	reloadFailed.setBuffer(reloadFailedBuffer);

	// The main loop
	while (window.isOpen())
	{
		/*
		 * ***********************
		 * Handle Input
		 * ***********************
		 */

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;

					// Reset the clock so there isn't a frame jump
					clock.restart();
				}

				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;

					wave  = 0;
					score = 0;

					// Prepare the gun and ammo for the next game
					currentBullet = 0;
					bulletsSpare  = 24;
					bulletsInClip = 6;
					clipSize	  = 6;
					fireRate	  = 1;

					// Reset the player's stats
					player.resetPlayerStats();

				}

				if (state == State::PLAYING)
				{
					// Reloading
					if (event.key.code == Keyboard::R)
					{
						if (bulletsSpare >= clipSize)
						{
							// Plenty of bullets. Reload
							bulletsInClip = clipSize;
							bulletsSpare -= clipSize;
							reload.play();
						}
						else if (bulletsSpare > 0)
						{
							// Only a few bullets left
							bulletsInClip = bulletsSpare;
							bulletsSpare = 0;
							reload.play();
						}
						else
						{
							reloadFailed.play();
						}
					}
				}

			}

		}// End event polling

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle WASD while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}

			// Fire a bullet
			if (Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds()
					> 1000 / fireRate && bulletsInClip > 0)
				{
					// Pass center of player and center of cross-hair to shoot()
					bullets[currentBullet].shoot(player.getCenter().x
						, player.getCenter().y, mouseWorldPosition.x
						, mouseWorldPosition.y);

					currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}

					lastPressed = gameTimeTotal;
					shoot.play();
					bulletsInClip--;
				}
			}// End fire a bullet

		}// End WASD while playing

		// Handle the LEVELING up state
		if (state == State::LEVELING_UP)
		{
			// Handle the player LEVELING up
			if (event.key.code == Keyboard::Num1)
			{
				// Increase fire rate
				fireRate++;

				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2)
			{
				// Increase clip size
				clipSize += clipSize;

				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3)
			{
				// Increase health
				player.upgradeHealth();

				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num4)
			{
				// Increase speed
				player.upgradeSpeed();

				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num5)
			{
				// Upgrade pickup
				healthPickup.upgrade();

				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num6)
			{
				// Upgrade pickup
				ammoPickup.upgrade();

				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{
				// Increase the wave number
				wave++;

				// Prepare the level				
				arena.width	 = 500 * wave;
				arena.height = 500 * wave;
				arena.left   = 0;
				arena.top    = 0;

				// Pass vertex array by reference to createBackground function
				int tileSize = createBackground(background, arena);
				
				// Spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Configure the pickups
				healthPickup.setArena(arena);
				ammoPickup.setArena(arena);

				// Create a horde of zombies
				numZombies = 5 * wave;

				// Delete the previously allocated memory if it exists
				delete[] zombies;

				zombies = createHorde(numZombies, arena);

				numZombiesAlive = numZombies;

				// Play the power up sound
				powerUp.play();

				// Reset the clock so there isn't a frame jump
				clock.restart();
			}

		}// End LEVELING up

		/*
		 * ***********************
		 * Update the frame
		 * ***********************
		 */

		if (state == State::PLAYING)
		{
			// Update the delta time
			Time dt = clock.restart();

			// Update the total game time
			gameTimeTotal += dt;

			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition()
				, mainView);

			// Set the cross-hair to the mouse world location
			spriteCrosshair.setPosition(mouseWorldPosition);

			// Update the player
			player.update(dtAsSeconds, Mouse::getPosition());

			// Make a note of the players new position
			Vector2f playerPosition(player.getCenter());

			// Make the view centre around the player
			mainView.setCenter(player.getCenter());

			// Loop through each zombie and update them
			for (int i = 0; i < numZombies; i++)
			{
				if (zombies[i].isAlive())
				{
					zombies[i].update(dt.asSeconds(), playerPosition);
				}
			}

			// Update any bullets that are in-flight
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}

			// Update the pickups
			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);

			// COLLISION DETECTION

			// Have any zombies been shot
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < numZombies; j++)
				{
					if (bullets[i].isInFlight() && zombies[j].isAlive())
					{
						if (bullets[i].getPosition().intersects
							(zombies[j].getPosition()))
						{
							// Stop the bullet
							bullets[i].stop();

							// Register the hit and see if it was killed
							if (zombies[j].hit())
							{
								// hit and kill
								score += 10;

								if (score >= hiScore)
								{
									hiScore = score;
								}

								numZombiesAlive--;

								// When all the zombies are dead
								if (numZombiesAlive == 0)
								{
									state = State::LEVELING_UP;
								}
							}

							splat.play();
						}
					}
				}
			}// End of zombie being shot

			// Have any zombies touched the player
			for (int i = 0; i < numZombies; i++)
			{
				if (player.getPosition().intersects(zombies[i].getPosition()) 
					&& zombies[i].isAlive())
				{
					if (player.hit(gameTimeTotal))
					{
						hit.play();
					}

					if (player.getHealth() <= 0)
					{
						state = State::GAME_OVER;

						std::ofstream outputFile("gamedata/scores.txt");

						// Write the data to the file
						outputFile << hiScore;
						outputFile.close();
					}
				}
			}// End zombies touch player

			// Has the player touched a heath pickup
			if (player.getPosition().intersects(healthPickup.getPosition())
				&& healthPickup.isSpawned())
			{
				player.increaseHealthLevel(healthPickup.gotIt());
				pickup.play();
			}

			// Has the player touched an ammo pickup
			if (player.getPosition().intersects(ammoPickup.getPosition()) 
				&& ammoPickup.isSpawned())
			{
				bulletsSpare += ammoPickup.gotIt();
				pickup.play();
			}

			// Size of the health bar
			healthBar.setSize(Vector2f(player.getHealth() * 3, 50));

			// Increment the number of frames since the previous update
			framesSinceLastHUDUpdate++;

			// Recalculate every fpsMeasurementFrameInterval frames
			if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
			{
				// Update game HUD text
				std::stringstream ssAmmo;
				std::stringstream ssScore;
				std::stringstream ssHighScore;
				std::stringstream ssWave;
				std::stringstream ssZombiesAlive;

				// Update the ammo text
				ssAmmo << bulletsInClip << "/" << bulletsSpare;
				ammoText.setString(ssAmmo.str());

				// Update the score text
				ssScore << "Score:" << score;
				scoreText.setString(ssScore.str());

				// Update the high score
				ssHighScore << "High Score:" << hiScore;
				highScoreText.setString(ssHighScore.str());

				// Update wave
				ssWave << "Wave:" << wave;
				waveNumberText.setString(ssWave.str());

				// Update number of zombies alive
				ssZombiesAlive << "Zombies:" << numZombiesAlive;
				zombiesRemainingText.setString(ssZombiesAlive.str());

				framesSinceLastHUDUpdate = 0;
			}// End of HUD update
		}// End updating the scene

		/*
		 * **************************
		 * Draw the scene
		 * **************************
		 */

		if (state == State::PLAYING)
		{
			window.clear();

			// Set mainView to be displayed in window and draw everything related to it
			window.setView(mainView);

			// Draw the background
			window.draw(background, &textureBackground);

			// Draw the zombies
			for (int i = 0; i < numZombies; i ++)
			{
				window.draw(zombies[i].getSprite());
			}

			// Draw bullets
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					window.draw(bullets[i].getShape());
				}
			}

			// Draw the player
			window.draw(player.getSprite());

			// Draw pickups if spawned
			if (ammoPickup.isSpawned())
			{
				window.draw(ammoPickup.getSprite());
			}

			if (healthPickup.isSpawned())
			{
				window.draw(healthPickup.getSprite());
			}

			// Draw teh cross-hair
			window.draw(spriteCrosshair);

			// Switch to the HUD view
			window.setView(hudView);

			// Draw the elements of the HUD
			window.draw(spriteAmmoIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(highScoreText);
			window.draw(healthBar);
			window.draw(waveNumberText);
			window.draw(zombiesRemainingText);
		}

		if (state == State::LEVELING_UP)
		{
			window.draw(spriteGameover);
			window.draw(levelingUpText);
		}

		if (state == State::PAUSED)
		{
			window.draw(pausedText);
		}

		if (state == State::GAME_OVER)
		{
			window.draw(spriteGameover);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(highScoreText);
		}

		window.display();

	}// End game loop

	// Delete the previously allocated memory if it exists
	delete[] zombies;

	return 0;
}