#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    // creating a window for the shpaes 
    const int wWidth = 800;
    const int wHeight = 600;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "PLEASE WORK!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}