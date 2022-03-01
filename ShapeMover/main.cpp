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

// class for all shapes
class Shapes
{    
    // vector to hold circle shapes
    std::vector<Polygon> m_polygon;
    // variable to hold shape type
    std::string         m_type;
public:
    // shape type constructor 
    Shapes(const std::string& type)
        : m_type(type)
    {        
    }
    // adds circles to Circle vector
    void addPolygon(const Polygon &polys)
    {
        m_polygon.push_back(polys);
    }
    // return cirlces in Circle vector 
    std::vector<Polygon>& getPolygons()
    {
        return m_polygon;
    }
    // gets shape paramaters from file and adds shape
    void addShapesFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        float x   = 0;
        float y   = 0;
        float xS  = 0;
        float yS  = 0;
        int   pR  = 0;  
        int   p   = 0;

        // itterates throught each line in file
        while(fin >> x)
        fin >> y >> xS >> yS >> pR >> p;

        // adds circle 
        Polygon polys(x, y, xS, yS, pR, p);
        addPolygon(polys);
    }    
};

int main(int argc, char* argv[])
{
       
    Shapes polys("Polygons");
    polys.addShapesFromFile("ShapeConfig.txt");
    
    for (auto & polys : polys.getPolygons())
    {                
        // creating a window for the shpaes 
        const int wWidth = 2000;                     // set window width
        const int wHeight = 1800;                    // set window height 
        sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "PLEASE WORK!");
    
        // creating shapes that will appear in the window 
        sf::CircleShape circle(polys.getpRad(), polys.getp()); // cirlce with given radius 
        circle.setFillColor(sf::Color::Green);                 // circle color 
        circle.setPosition(polys.getxPos(), polys.getyPos());  // cirlce starting position
        float circleMoveSpeedX = polys.getxSpeed();            // x axis move on bounce 
        float circleMoveSpeedY = polys.getySpeed();            // y axis move on bounce  

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
            if(circle.getPosition() .y > wHeight - (polys.getpRad() * 2) 
                || circle.getPosition() .y < 0)
            {
                // reveres direction on y axis and randomize color
                circleMoveSpeedY *= -1.0; 
                circle.setFillColor
                    (sf::Color(rand() % 255, rand() % 255, rand() % 255));
            } 
            // x boundary collision 
            else if(circle.getPosition() .x > wWidth - (polys.getpRad() * 2) 
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
            window.clear();       // clear window
            window.draw(circle);  // draw cirlce in current positon
            window.draw(text);    // draw text to window 
            window.display();     // diplay to window 
        }
    }
    return 0;
}