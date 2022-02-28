// main.cpp
// creats shapes that move within a window 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

// class for circle shapes
class Circle
{
    float   m_xPos;     // x axis position
    float   m_yPos;     // y axis position
    float   m_xSpeed;   // x speed
    float   m_ySpeed;   // y speed
    int     m_cRad;     // radius
    int     m_cID;      // circle ID
public:
    // default circle constructor
    Circle()
    {
    }
    // circle constructor 
    Circle(float x, float y, float xS, float yS, int cR, int cID)
        : m_xPos  (x)
        , m_yPos  (y)
        , m_xSpeed(xS)
        , m_ySpeed(yS)
        , m_cRad  (cR)
        , m_cID   (cID)  
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
    int getcRad()       // returns circle radius
    {
        return m_cRad;
    }
    int getcID()        // returns circle ID
    {
        return m_cID;
    }
    void print()        // print for verification 
    {
        std::cout << m_cID << "\n";
    }
};

// class for all shapes
class Shapes
{    
    // vector to hold circle shapes
    std::vector<Circle> m_circles;
    // variable to hold shape type
    std::string         m_type;
public:
    // shape type constructor 
    Shapes(const std::string& type)
        : m_type(type)
    {        
    }
    // adds circles to Circle vector
    void addCircle(const Circle& c)
    {
        m_circles.push_back(c);
    }
    // return cirlces in Circle vector 
    std::vector<Circle>& getCircles()
    {
        return m_circles;
    }
    // gets shape paramaters from file and adds shape
    void addShapesFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        float x   = 0;
        float y   = 0;
        float xS  = 0;
        float yS  = 0;
        int   cR  = 0;  
        int   cID = 0;

        // itterates throught each line in file
        while(fin >> x)
        fin >> y >> xS >> yS >> cR >> cID;

        // adds circle 
        Circle c(x, y, xS, yS, cR, cID);
        addCircle(c);
    }
    
};

int main(int argc, char* argv[])
{
       
    Shapes c("Circles");
    c.addShapesFromFile("ShapeConfig.txt");
    
    for (Circle& c : c.getCircles())
    {

        // variables 
        int cRadius = c.getcRad();                   // cirlce radius 

        // creating a window for the shpaes 
        const int wWidth = 2000;                     // set window width
        const int wHeight = 1800;                    // set window height 
        sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "PLEASE WORK!");
    
        // creating shapes that will appear in the window 
        sf::CircleShape circle(cRadius);              // cirlce with given radius 
        circle.setFillColor(sf::Color::Green);        // circle color 
        circle.setPosition(c.getxPos(), c.getyPos()); // cirlce starting position
        float circleMoveSpeedX = c.getxSpeed();       // x axis move on bounce 
        float circleMoveSpeedY = c.getySpeed();       // y axis move on bounce  

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
            if(circle.getPosition() .y > wHeight - (cRadius * 2) 
                || circle.getPosition() .y < 0)
            {
                // reveres direction on y axis and randomize color
                circleMoveSpeedY *= -1.0; 
                circle.setFillColor
                    (sf::Color(rand() % 255, rand() % 255, rand() % 255));
            } 
            // x boundary collision 
            else if(circle.getPosition() .x > wWidth - (cRadius * 2) 
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