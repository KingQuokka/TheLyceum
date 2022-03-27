// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Bat.h"
#include  <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Pong", Style::Fullscreen);

	int score = 0;
	int lives = 3;

	// Create a bat at the bottom center of the screen
	Bat bat(1920 / 2, 1080 - 20);

	// Create a Text object called HUD
	Text hud;

	// Add a font, set font, size, color, and position
	Font font;
	font.loadFromFile("fonts/Roboto.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	// Here is our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		 * *************************
		 * Handle Player Input
		 * *************************
		 */

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Quit the game when window is closed
				window.close();
		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}

		/*
		 * *************************
		 * Update bat, ball, and HUD
		 * *************************
		 */

		// Update the delta time
		Time dt = clock.restart();
		bat.update(dt);

		// Update the HUD text
		std::stringstream ss;
		ss << "Score: " << score << " Live: " << lives;
		hud.setString(ss.str());

		/*
		 * *************************
		 * Draw bat, ball, and HUD
		 * *************************
		 */

		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.display();
	}
	return 0;
}

