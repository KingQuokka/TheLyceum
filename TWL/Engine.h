#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

using namespace sf;

class Engine
{
private:

    // The texture holder
    TextureHolder th;

    const int TILE_SIZE     = 50;
    const int VERTS_IN_QUAD = 4;    
    const int GRAVITY       = 300; // Force pushing player down

    // A regular RenderWindow
    RenderWindow m_Window;

    // The main Views
    View m_MainView;
    View m_LeftView;
    View m_RightView;

    // Three views for the background
    View m_BGMainView;
    View m_BGLeftView;
    View m_BGRightView;
    View m_HudView;

    // Declare a sprite and a Texture for the background
    Sprite  m_BackgroundSprite;
    Texture m_BackgroundTexture;       
    bool    m_Playing            = false; // Is game playing?
    bool    m_Character1         = true;  // Is char 1 or 2 the focus 
    bool    m_SplitScreen        = false; // Start full screen not split
    float   m_TimeRemaining      = 10;    // Level time remaining 
    Time    m_GameTimeTotal;
    bool    m_NewLevelRequired   = true;  // Is is time for a new level

    // Private functions for internal use only
    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    // The Engine constructor
    Engine();

    // Run will call all the private functions
    void run();
};