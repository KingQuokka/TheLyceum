#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED  = 200;
	const float START_HEALTH = 100;

	Vector2f m_Position;	// Where is the player
	Sprite	 m_Sprite;		// Player sprite
	Texture  m_Texture;		// Sprite texture
	Vector2f m_Resolution;	// What is the screen resolution
	IntRect	 m_Arena;		// What is the size of the arena
	int		 m_TileSize;	// How big is each tile
	bool	 m_UpPressed;	// What direction is the player moving
	bool	 m_DownPressed;
	bool	 m_LeftPressed;
	bool	 m_RightPressed;
	int		 m_Health;		// How much health does the player have
	int		 m_MaxHealth;	// What is the players max health
	Time	 m_LastHit;		// When was the player last hit
	float	 m_Speed;		// Speed in pixels per second
public:
	Player();
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// Call this at the end of every game
	void resetPlayerStats();

	// Handle player getting hit by zombie
	bool hit(Time timeHit);

	// How long ago was the player last hit
	Time getLastHitTime();

	// Where is the player
	FloatRect getPosition();

	// Where is the center of the player
	Vector2f getCenter();

	// What agnle is the player facing
	float getRotation();

	// Send a copy of the sprite to main function
	Sprite getSprite();

	// move the player
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// Stop the player moving in a specific direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	// Call this function once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	// Give the player a speed boost
	void upgradeSpeed();

	// Give the player some health
	void upgradeHealth();

	// Increase max health
	void increaseHealthLevel(int amount);

	// How much health does the player currently have
	int getHealth();
};