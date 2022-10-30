#include <SFML/Graphics.hpp>
#include <sstream>
#ifndef BACKGROUND_H
#define BACKGROUND_H

using namespace sf;
using namespace std;

class Background {
public:
	Background(); // sets default background values

	void BackgroundScale(Vector2f resolution); // this will scale background to resolution size
	void Scroll(float dt); // this will scroll background using deltaTime
	void ChangeBackground(
		string filename1, string filename2, string filename3, // this changes background
		IntRect rect1, IntRect rect2, IntRect rect3); // NEEDS TO BE FIXED AS IT RUINS FPS EVERY BACKGROUND CHANGE
	
	// these return background sprites
	Sprite getSprite1(); 
	Sprite getSprite2();
	Sprite getSprite3();

private:
	// holds textures of backgrounds
	Texture m_BackgroundTexture1; 
	Texture m_BackgroundTexture2;
	Texture m_BackgroundTexture3;

	// sprites for backgrounds
	Sprite m_BackgroundSprite1; 
	Sprite m_BackgroundSprite2;
	Sprite m_BackgroundSprite3;

	float m_BackgroundSpeed; // speed in which background scrolls
	float m_BackgroundX; // x value of background as scrolling will be horizontal

	Vector2f m_Resolution; // stores resolution of screen
};
#endif