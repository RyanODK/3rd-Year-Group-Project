#include <SFML/Graphics.hpp>
#include <sstream>
#ifndef BACKGROUND_H
#define BACKGROUND_H

using namespace sf;

class Background {
public:
	Background(); // sets default background values

	void BackgroundScale(Vector2f resolution); // this will scale background to resolution size
	void Update(float dt); // this will update background scrolling using deltaTime
	Sprite getSprite(); // this returns background sprite

private:
	Texture m_BackgroundTexture; // holds texture of background

	Sprite m_BackgroundSprite; // sprite for background

	float m_BackgroundSpeed; // speed in which background scrolls
	float m_BackgroundX; // x value of background as scrolling will be horizontal

	Vector2f m_Resolution; // stores resolution of screen
};
#endif