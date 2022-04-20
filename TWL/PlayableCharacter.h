#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:

	Sprite	m_Sprite;		// Character sprite
	float	m_JumpDuration;	// How long does the jump last
	bool	m_IsJumping;	// Is the character jumping
	bool	m_IsFalling;
	bool	m_LeftPressed;	// Is the character moving
	bool	m_RightPressed;
	float	m_TimeThisJump;	// How long has this jump lasted
	bool	m_JustJumped = false;

private:

	float	  m_Gravity;		// What is the gravity
	float	  m_Speed = 400;	// Character speed
	Vector2f  m_Position;		// Where is the player
	FloatRect m_Feet;			// Where is the characters body parts
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;
	Texture	  m_Texture;		// Texture

public:

	void spawn(Vector2f startPosition, float gravity);

	// This is a pure virtual function
	bool virtual handleInput() = 0;
	// This class is now abstract and cannot be instantiated

	// Where is the player
	FloatRect getPosition();

	// Rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Make character stand firm
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	// Where is the center of the character
	Vector2f getCenter();

	// Call once every frame
	void update(float elapsedTime);

};// End of the class
