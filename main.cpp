// creats shapes that move within a window 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    // variables 
    int cRadius = 100;                        // set variable for cirlce radius 

    // creating a window for the shpaes 
    const int wWidth = 1600;                 // set window width
    const int wHeight = 1200;                // set window height 
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "PLEASE WORK!");
    
    // creating shapes that will appear in the window 
    sf::CircleShape circle(cRadius);         // creates cirlce with given radius 
    circle.setFillColor(sf::Color::Green);   // set circle color 
    circle.setPosition(300, 300);            // set cirlce starting position
    float circleMoveSpeed = -0.05;           // sets movement speed  

    // loads font to display text
    sf::Font myFont;

    // load font from file
    if(!myFont.loadFromFile("Roboto.ttf")) 
    {
        // error check
        std::cerr << "COULD NOT LOAD FONT!\n\n";
        exit(-1);
    } 

    // string, font, size
    sf::Text text("SHAPE MOVER", myFont, 60);
        
    //  align text to bottom left corner
    text.setPosition(0, wHeight - (float)text.getCharacterSize());

    // main loop
    while (window.isOpen())
    {
        // event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            // window close event trigger
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // keypress event trigger
            if (event.type == sf::Event::KeyPressed)
            {
                // print which key was pressed to console
                std::cout << "Key pressed with code = " << event.key.code << "\n";

                // event when r is pressed
                if (event.key.code == sf::Keyboard::R)
                {
                    // reverse the direction of the circle 
                    circleMoveSpeed *= -1.0;
                }
            }            
        }
        // bounce on boundry collisions
        if(circle.getPosition() .x > 1600 - (cRadius * 2) || circle.getPosition() .y > 1200 - (cRadius *2))
        {
            circleMoveSpeed *= -1.0;
        } 
        if(circle.getPosition() .x < 0 || circle.getPosition() .y < 0)
        {
            circleMoveSpeed *= -1.0;
        }         

        // movement animation 
        circle.setPosition(circle.getPosition() + sf::Vector2f(circleMoveSpeed, circleMoveSpeed));

        // render functions
        window.clear();             // clear window
        window.draw(circle);        // draw cirlce in current positon
        window.draw(text);          // draw text to window 
        window.display();           // diplay to window 
    }

    return 0;
}