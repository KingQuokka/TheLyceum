// main.cpp
// creats shapes that move within a window 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class PolygonMovement
{
    float m_xSpeed;
    float m_ySpeed;
public:
    PolygonMovement()
    {        
    }
    PolygonMovement(float xSpeed, float ySpeed)
        : m_xSpeed(xSpeed)
        , m_ySpeed(ySpeed)
    {        
    }    
    float setxSpeed(float xS)
    {
        m_xSpeed = xS;
    }
    float setySpeed(float yS)
    {
        m_ySpeed = yS;
    }
    float getxSpeed()
    {
        return m_xSpeed;
    }
    float getySpeed()
    {
        return m_ySpeed;
    }
};

int main(int argc, char* argv[])
{
    sf::CircleShape polygon;                 // variable for shapes
    std::vector<sf::CircleShape> poly;       // vector to hold polygons
    PolygonMovement pMove;                   // velocity variable
    std::vector<PolygonMovement> polySpeeds; // vector to hold velocities
    std::ifstream fin("ShapeConfig.txt");    // polygon configurations
        float x          = 0;                // point on x axis
        float y          = 0;                // point on y axis
        float xSpeed     = 0;                // speed on x axis
        float ySpeed     = 0;                // speed on y axis
        int   polyRadius = 0;                // polygon radius
        int   polyPoints = 0;                // number of points on polygon
        
    // reads in polygon configurations and pushes them to poly vector 
    while(fin >> x)
    {
        fin >> y >> xSpeed >> ySpeed >> polyRadius >> polyPoints;
        polygon.setPosition  (x,y);
        polygon.setFillColor (sf::Color::Green);
        polygon.setRadius    (polyRadius);
        pMove.setxSpeed      (xSpeed);
        pMove.setySpeed      (ySpeed);        
        polygon.setPointCount(polyPoints);
        poly.push_back       (polygon);      // push polygon to poly vector
        polySpeeds.push_back (pMove);        // push velocity to polySpeeds vector
    }   
    // creating a window for the shpaes 
    const int wWidth  = 2000;                // set window width
    const int wHeight = 1800;                // set window height 
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SHAPE MOVER WORKS!");
       
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
        // iterate through all polygons in poly vector
        for(int i = 0; i < poly.size(); i++)
        {            
            // y boundary collisions
            if(poly[i].getPosition() .y > wHeight - (poly[i].getRadius() * 2) 
                || poly[i].getPosition() .y < 0)
            {
                // reveres direction on y axis and randomize color
                polySpeeds[i].setySpeed(polySpeeds[i].getySpeed() * -1.0); 
                poly[i].setFillColor
                    (sf::Color(rand() % 255, rand() % 255, rand() % 255));
            } 
            
            // x boundary collision 
            if(poly[i].getPosition() .x > wWidth - (poly[i].getRadius() * 2) 
                || poly[i].getPosition() .x < 0)
            {
                // reverse direction on x axis and randomize color
                polySpeeds[i].setxSpeed(polySpeeds[i].getxSpeed() * -1.0);
                poly[i].setFillColor
                    (sf::Color(rand() % 255, rand() % 255, rand() % 255));
            }               
            
            // movement animation 
            poly[i].setPosition(poly[i].getPosition() 
            + sf::Vector2f(polySpeeds[i].getxSpeed(), polySpeeds[i].getySpeed()));
        }
            
        // render functions
        window.clear();            // clear window
        
        // iterate and draw all polygons in poly vector
        for (auto it : poly)
        {
            window.draw(it);       // "draw it" draw polygons in current positon 
        }
        window.draw(text);         // draw text to window 
        window.display();          // diplay to window 
    }    
    return 0;
}