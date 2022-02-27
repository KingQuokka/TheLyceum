// main.cpp
// creats shapes that move within a window 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class Circle
{
    float   m_xPos;
    float   m_yPos;
    float   m_xSpeed;
    float   m_ySpeed;
    int     m_cRad;
    int     m_cID;
public:
    Circle()
    {
    }
    Circle(float x, float y, float xS, float yS, int cR, int cID)
        : m_xPos  (x)
        , m_yPos  (y)
        , m_xSpeed(xS)
        , m_ySpeed(yS)
        , m_cRad  (cR)
        , m_cID   (cID)  
    {
    }
    float getxPos()
    {
        return m_xPos;
    }
    float getyPos()
    {
        return m_yPos;
    }
    float getxSpeed()
    {
        return m_xSpeed;
    }
    float getySpeed()
    {
        return m_ySpeed;
    }
    int getcRad()
    {
        return m_cRad;
    }
    int getcID()
    {
        return m_cID;
    }
    void print()
    {
        std::cout << m_cID << "\n";
    }
};

class Shapes
{    
    std::vector<Circle> m_circles;
    std::string         m_type;
public:
    
    Shapes(const std::string& type)
        : m_type(type)
    {        
    }
    void addCircle(const Circle& c)
    {
        m_circles.push_back(c);
    }

    std::vector<Circle>& getCircles()
    {
        return m_circles;
    }

    void addShapesFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        float x   = 0;
        float y   = 0;
        float xS  = 0;
        float yS  = 0;
        int   cR  = 0;  
        int   cID = 0;

        while(fin >> x)
        fin >> y >> xS >> yS >> cR >> cID;

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
        int cRadius = c.getcRad();                   // set variable for cirlce radius 

        // creating a window for the shpaes 
        const int wWidth = 2000;                    // set window width
        const int wHeight = 1800;                   // set window height 
        sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "PLEASE WORK!");
    
        // creating shapes that will appear in the window 
        sf::CircleShape circle(cRadius);            // creates cirlce with given radius 
        circle.setFillColor(sf::Color::Green);      // set circle color 
        circle.setPosition(c.getxPos(), c.getyPos());   // set cirlce starting position
        float circleMoveSpeedX = c.getxSpeed();        // variable for x axis move on bounce 
        float circleMoveSpeedY = c.getySpeed();        // variable for y axis move on bounce  

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
    };
    return 0;
}