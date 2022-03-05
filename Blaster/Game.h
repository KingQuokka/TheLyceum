#pragma once

#include "Common.h"
#include "Entity.h"
#include "EntityManager.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
    sf::RenderWindow    m_window;           // creates game window
    EntityManager       m_entites;          // vector of entites to mantain
    sf::Font            m_font;             // font for text to be drawn
    sf::Text            m_text;             // text to be drawn
    PlayerConfig        m_playerConfig; 
    EnemyConfig         m_enemyConfig;
    BulletConfig        m_bulletConfig;
    int                 m_score              = 0;
    int                 m_currentFrame       = 0;
    int                 m_lastEnemySpawnTime = 0;
    bool                m_paused             = false; // whether we update game logic
    bool                m_running            = true;  // whether the game is running

    std::shared_ptr<Entity> m_player;

    void init(const std::string& config);   // initialize gamestate w/ config file
    void setPaused(bool paused);            // pauses the game
    
    void sMovement();                       // System: Entity position/movement update
    void sUserInput();                      // System: User Input
    void sLifespan();                       // System: Lifespan
    void sRender();                         // System: Render/Drawing
    void sEnemySpawner();                   // System: Spawns enemies
    void sCollision();                      // System: Collisions

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:

    Game(const std::string& config);        // constructor that takes in game config

    void run();
};