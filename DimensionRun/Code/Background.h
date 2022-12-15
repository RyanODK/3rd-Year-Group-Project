#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "TextureHolder.h"

class Background {
public:
	Background(); // sets default background values

	void BackgroundScale(sf::Vector2u resolution); // this will scale background to resolution size
	void Scroll(float dt); // this will scroll background using deltaTime
	void ChangeBackground(
		std::string filename1, std::string filename2, std::string filename3, // this changes background
		sf::IntRect rect1, sf::IntRect rect2, sf::IntRect rect3); // changes background taking in filename and IntRect
	void setBackgroundSpeed(float backgroundSpeed); // sets background speed

	// these return background sprites
	sf::Sprite getSprite1(); 
	sf::Sprite getSprite2();
	sf::Sprite getSprite3();

private:
	// holds textures of backgrounds
	sf::Texture m_BackgroundTexture1; 
	sf::Texture m_BackgroundTexture2;
	sf::Texture m_BackgroundTexture3;

	// sprites for backgrounds
	sf::Sprite m_BackgroundSprite1;
	sf::Sprite m_BackgroundSprite2;
	sf::Sprite m_BackgroundSprite3;

	float m_BackgroundSpeed; // speed in which background scrolls
	float m_BackgroundX; // x value of background as scrolling will be horizontal

	sf::Vector2u m_Resolution; // stores resolution of screen
};