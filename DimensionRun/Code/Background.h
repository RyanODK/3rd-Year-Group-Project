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
	Sprite getSprite1(); // this returns background sprite
	Sprite getSprite2();
	Sprite getSprite3();

private:
	Texture m_BackgroundTexture1; // holds texture of background
	Texture m_BackgroundTexture2;
	Texture m_BackgroundTexture3;

	Sprite m_BackgroundSprite1; // sprite for background
	Sprite m_BackgroundSprite2;
	Sprite m_BackgroundSprite3;

	float m_BackgroundSpeed1; // speed in which background scrolls
	float m_BackgroundX; // x value of background as scrolling will be horizontal

	Vector2f m_Resolution; // stores resolution of screen
};
#endif