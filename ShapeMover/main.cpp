// main.cpp
// creats shapes that move within a window 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

// class for polygon shapes
class Polygon
{
    float   m_xPos;     // x axis position
    float   m_yPos;     // y axis position
    float   m_xSpeed;   // x speed
    float   m_ySpeed;   // y speed
    int     m_pRad;     // radius
    int     m_points;   // circle ID
public:
    // default circle constructor
    Polygon()
    {
    }
    // circle constructor 
    Polygon(float x, float y, float xS, float yS, int pR, int p)
        : m_xPos   (x)
        , m_yPos   (y)
        , m_xSpeed (xS)
        , m_ySpeed (yS)
        , m_pRad   (pR)
        , m_points (p)  
    {
    }
    float getxPos()     // returns x axis position
    {
        return m_xPos;
    }
    float getyPos()     // returns y axis position
    {
        return m_yPos;
    }
    float getxSpeed()   // returns speed on x axis
    {
        return m_xSpeed;
    }
    float getySpeed()   // returns speed on y axis
    {
        return m_ySpeed;
    }
    int getpRad()       // returns circle radius
    {
        return m_pRad;
    }
    int getp()          // returns circle ID
    {
        return m_points;
    }    
};

int main(int argc, char* argv[])
{
       
    std::vector<Polygon> polysVector;
    std::ifstream fin("ShapeConfig.txt");
        float x   = 0;
        float y   = 0;
        float xS  = 0;
        float yS  = 0;
        int   pR  = 0;  
        int   p   = 0;

    // itterates throught each line in file
    while(fin >> x)
    {
        fin >> y >> xS >> yS >> pR >> p;

        // adds circle 
        Polygon polys(x, y, xS, yS, pR, p);
        polysVector.push_back(polys);
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
            for (int i = 0; i < polysVector.size(); i++)
            {    
                // creating shapes that will appear in the window 
                sf::CircleShape circle(polysVector[i].getpRad(), polysVector[i].getp()); // cirlce with given radius 
                circle.setFillColor(sf::Color::Green);                 // circle color 
                circle.setPosition(polysVector[i].getxPos(),polysVector[i].getyPos());  // cirlce starting position
                float circleMoveSpeedX = polysVector[i].getxSpeed();            // x axis move on bounce 
                float circleMoveSpeedY = polysVector[i].getySpeed();            // y axis move on bounce   
                     
            
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
                if(circle.getPosition() .y > wHeight - (polysVector[i].getpRad() * 2) 
                    || circle.getPosition() .y < 0)
                {
                    // reveres direction on y axis and randomize color
                    circleMoveSpeedY *= -1.0; 
                    circle.setFillColor
                        (sf::Color(rand() % 255, rand() % 255, rand() % 255));
                } 
            
                // x boundary collision 
                else if(circle.getPosition() .x > wWidth - (polysVector[i].getpRad() * 2) 
                    || circle.getPosition() .x < 0)
                {
                    // reverse direction on x axis and randomize color
                    circleMoveSpeedX *= -1.0;
                    circle.setFillColor
                        (sf::Color(rand() % 255, rand() % 255, rand() % 255));
                }         
            
                // movement animation 
                circle.setPosition(circle.getPosition() 
                    + sf::Vector2f(circleMoveSpeedX, circleMoveSpeedY));
            
                // render functions
                //window.clear();       // clear window
                window.draw(circle);  // draw cirlce in current positon
                window.draw(text);    // draw text to window 
                window.display();     // diplay to window 
            }
        }
    return 0;
}