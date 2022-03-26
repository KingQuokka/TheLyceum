// From The Deep
// First project from Beginning C++ Programming 2nd Edition

// Include important libraries here
#include <SFML/Graphics.hpp>

// Make code easier to type with "using name space"
using namespace sf;

// This is where our fame starts from
int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window fro the game
	RenderWindow window(vm, "From The Deep!", Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/FTDbackground.png");

	// Create a spite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Preparing the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	// Is the bee currently moving?
	bool beeActive = false;
	// How fast can the bee fly
	float beeSpeed = 0.0f;

	// Preparing the clouds
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);	
	// Position the clouds on the left of the screen
	// at different heights
	spriteCloud1.setPosition(0, 0);
	spriteCloud1.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	// Are the clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	// How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Variables to control time itself
	Clock clock;


	while (window.isOpen())
	{
		/*
		 *************************************
		 * Handle the players input
		 *************************************
		 */

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		 *************************************
		 * Update the scene
		 *************************************
		 */

		// Measure time
		Time dt = clock.restart();

		// Setup the bee
		if (!beeActive)
		{
			// How fast is the bee
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;

			// How high is the bee
			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			spriteBee.setPosition(2000, height);
			beeActive = true;
		}
		else
		{
			spriteBee.setPosition(
				spriteBee.getPosition().x -
				(beeSpeed * dt.asSeconds())
				, spriteBee.getPosition().y);
			// Has the bee reached the left-hand edge of the screen?
			if (spriteBee.getPosition().x <-100)
			{
				//Setup a whole new bee for the next frame
				beeActive = false;
			}
		}

		// Manage the clouds
		// Cloud 1
		if (! cloud1Active)
		{
			// How fast is the cloud?
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);
			// How high is the cloud?
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(-200, height);
			cloud1Active = true;
		}
		else
		{
			spriteCloud1.setPosition(
				spriteCloud1.getPosition().x
				+ (cloud1Speed * dt.asSeconds())
				, spriteCloud1.getPosition().y);
			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud1.getPosition().x > 1920)
			{
				// Setup a new cloud for the next frame
				cloud1Active = false;
			}
		}

		/*
		 *************************************
		 * Draw the scene
		 *************************************
		 */

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);
		// Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		// Draw the tree
		window.draw(spriteTree);
		// Draw the bee
		window.draw(spriteBee);

		// Show everything we just drew
		window.display();
	}

	return 0;
}