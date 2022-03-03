// main.cpp
// creats shapes that move within a window 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>


int main(int argc, char* argv[])
{
    sf::CircleShape polygon;
    std::vector<sf::CircleShape> poly;
    std::ifstream fin("ShapeConfig.txt");
        float x = 0;
        float y = 0;
        float xSpeed = 0;
        float ySpeed = 0;
        int   polyRadius = 0;
        int   polyPoints = 0;
    while(fin >> x)
    {
        fin >> y >> xSpeed >> ySpeed >> polyRadius >> polyPoints;
        polygon.setPosition(x,y);
        polygon.setFillColor(sf::Color::Green);
        float polygonMoveSpeedX = xSpeed;
        float polygonMoveSpeedY = ySpeed;
        polygon.setRadius(polyRadius);
        polygon.setPointCount(polyPoints);
        poly.push_back(polygon);
    }              
    
    // creating a window for the shpaes 
    const int wWidth = 2000;                     // set window width
    const int wHeight = 1800;                    // set window height 
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "PLEASE WORK!");
    
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
        
    // align text to bottom left corner
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
        // y boundary collisions
        if(polygon.getPosition() .y > wHeight - (polyRadius * 2) 
            || polygon.getPosition() .y < 0)
        {
            // reveres direction on y axis and randomize color
            ySpeed *= -1.0; 
            polygon.setFillColor
                (sf::Color(rand() % 255, rand() % 255, rand() % 255));
        } 
        // x boundary collision 
        else if(polygon.getPosition() .x > wWidth - (polyRadius * 2) 
            || polygon.getPosition() .x < 0)
        {
            // reverse direction on x axis and randomize color
            xSpeed *= -1.0;
            polygon.setFillColor
                (sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }         

        // movement animation 
        polygon.setPosition(polygon.getPosition() 
            + sf::Vector2f(xSpeed, ySpeed));

        // render functions
        window.clear();       // clear window
        for(int i = 0; i < poly.size(); i++)
        {
            window.draw(poly[i]);  // draw cirlce in current positon
        }
        window.draw(text);    // draw text to window 
        window.display();     // diplay to window 
    }
    return 0;
}