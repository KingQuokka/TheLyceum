#pragma once

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"

using namespace sf;

class Engine
{
private:

    // The texture holder
    TextureHolder th;

    // Thomas and Bob
    Thomas    m_Thomas;
    Bob       m_Bob;

    // A class to manage all levels
    LevelManager m_LM;

    // Create a SoundManager
    SoundManager m_SM;

    // The HUD
    Hud m_Hud;
    int m_FramesSinceLastHUDUpdate = 0;
    int m_TargetFramesPerHUDUpdate = 500;

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

    // The Vertex array for the level tiles
    VertexArray m_VALevel;

    // 2D array with map for the level, a pointer to a pointer
    int** m_ArrayLevel = NULL;

    // Texture for the level tiles
    Texture m_TextureTiles;

    // Private functions for internal use only
    void input();
    void update(float dtAsSeconds);
    void draw();

    // Load a new level
    void loadLevel();

    bool detectCollisions(PlayableCharacter& character);

    // Make a vector of the best places to emit sound
    void populateEmitters(vector<Vector2f>& vSoundEmitters, int** arrayLevel);

    // A vector of Vector2f for the fire emitter locations
    vector <Vector2f> m_FireEmitters;

public:
    // The Engine constructor
    Engine();

    // Run will call all the private functions
    void run();
};