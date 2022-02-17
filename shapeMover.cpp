// shapeMover.cpp
// creats shapes that move within a window 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    // variables 
    int cRadius = 100;                          // set variable for cirlce radius 

    // creating a window for the shpaes 
    const int wWidth = 2000;                    // set window width
    const int wHeight = 1800;                   // set window height 
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "PLEASE WORK!");
    
    // creating shapes that will appear in the window 
    sf::CircleShape circle(cRadius);            // creates cirlce with given radius 
    circle.setFillColor(sf::Color::Green);      // set circle color 
    circle.setPosition(200, 300);               // set cirlce starting position
    float circleMoveSpeed = -0.30;              // sets initial movement speed
    float circleMoveSpeedX = circleMoveSpeed;   // variable for x axis move on bounce 
    float circleMoveSpeedY = circleMoveSpeed;   // variable for y axis move on bounce  

    // loads font to display text
    sf::Font myFont;

    // load font from file
    if(!myFont.loadFromFile("Roboto.ttf")) 
    {
        // error check
        std::cerr << "COULD NOT LOAD FONT!\n\n";
        system("pause");
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
        }

        // bounce on boundry collisions
        if(circle.getPosition() .y > wHeight - (cRadius * 2) || circle.getPosition() .y < 0)
        {
            circleMoveSpeedY *= -1.0;
            circle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        } 
        else if(circle.getPosition() .x > wWidth - (cRadius * 2) || circle.getPosition() .x < 0)
        {
            circleMoveSpeedX *= -1.0;
            circle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }         

        // movement animation 
        circle.setPosition(circle.getPosition() + sf::Vector2f(circleMoveSpeedX, circleMoveSpeedY));

        // render functions
        window.clear();             // clear window
        window.draw(circle);        // draw cirlce in current positon
        window.draw(text);          // draw text to window 
        window.display();           // diplay to window 
    }

    return 0;
}