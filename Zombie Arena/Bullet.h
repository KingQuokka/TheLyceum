#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private:
	Vector2f	   m_Position;			  // Where is teh bullet
	RectangleShape m_BulletShape;		  // What each bullet looks like
	bool		   m_InFlight    = false; // Is the bullet in flight
	float		   m_BulletSpeed = 1000;  // How fast is the bullet
	float		   m_BulletDistanceX;	  // x/y distance traveled each frame 
	float		   m_BulletDistanceY;     // derived from m_BulletSpeed
	float		   m_MaxX;				  // boundaries for the bullet 
	float		   m_MinX;
	float		   m_MaxY;
	float		   m_MinY;
public:
	// Constructor
	Bullet();

	// Stop the bullet
	void stop();

	// Returns the value of m_InFlight
	bool isInFlight();

	// Launch a new bullet
	void shoot(float startX, float startY, float xTarget, float yTarget);

	// Tell the calling code where the bullet is in the world
	FloatRect getPosition();

	// Return the actual shape for drawing
	RectangleShape getShape();

	// Update the bullet each frame
	void update(float elapsedTime);
};