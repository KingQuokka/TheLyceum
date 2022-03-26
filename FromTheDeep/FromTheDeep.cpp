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

	while (window.isOpen())
	{
		/*
		 *
		 * Handle the players input
		 *
		 */
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		 *
		 * Update the scene
		 *
		 */
		/*
		 *
		 * Draw the scene
		 *
		 */
		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		// Show everything we just drew
		window.display();
	}

	return 0;
}