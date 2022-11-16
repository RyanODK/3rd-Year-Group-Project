#include "FloatingObstacle.h"
#include <iostream>

FloatingObstacle::FloatingObstacle()
{
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"Graphics/Free/Terrain/TerrainFloating.png", false));
	m_Sprite.setTextureRect(sf::IntRect{ 0, 0, 48, 48 });
	//m_Sprite.setPosition(2000, 600);
}
void FloatingObstacle::spawn(sf::Vector2f startPosition, sf::Vector2f scale) {
	resetPosition.x = startPosition.x;
	resetPosition.y = startPosition.y;

	m_Sprite.setScale(scale);

	m_Sprite.setPosition(startPosition);
}
//void FloatingObstacle::spawn(Vector2f startPosition, Vector2f scale) {
//	// depending on resolution set position and scale of player
//	if (m_Resolution.x == 2560 && m_Resolution.y == 1440) {
//		//m_Sprite.setPosition(250, 1080);
//		m_Sprite.setScale(4, 4);
//	}
//	else if (m_Resolution.x == 1920 && m_Resolution.y == 1080) {
//		//m_Sprite.setPosition(200, 850);
//		m_Sprite.setScale(2, 2);
//	}
//	else if (m_Resolution.x == 1680 && m_Resolution.y == 1050) {
//		//m_Sprite.setPosition(200, 800);
//		m_Sprite.setScale(4, 4);
//	}
//
//	// store resolution for future use
//	m_Resolution.x = resolution.x;
//	m_Resolution.y = resolution.y;
//
//	m_Sprite.setPosition(2000, 600);
//
//
//	//m_Position.x = 900;
//	//m_Position.y = 600;
//}


void FloatingObstacle::update(float elapsedTime) {
	//cout << m_Position.x << "\n";
	if (!obstacleActive)
	{
		//obstacleSpeed = 30;

		//m_Sprite.setPosition(900, 600);
		m_Position.x = 2000;
		m_Position.y = 600;
		obstacleActive = true;

	}
	else
	{
		m_Position.x -= 90 * 2 * elapsedTime;
		//cout << m_Position.x << "\n";
		//m_Sprite.setPosition(m_Position);

		if (m_Position.x < -300)
		{
			obstacleActive = false;
		}
	}

	// plays player run animation
	//setSpriteFromSheet(IntRect(0, 0, 71, 67));
	//moveTextureRect(elapsedTime);

	// set sprites position
	m_Sprite.setPosition(m_Position);
}

void FloatingObstacle::setSpriteFromSheet(sf::IntRect textureBox)
{
	// get sprite sheets left and top values
	sheetCoordinate = sf::Vector2i(textureBox.left, textureBox.top);
	// set sprite size
	spriteSize = sf::Vector2i(48, 48);

	//// if sprite sheet width is greater than sprite size x
	//if (textureBox.width > spriteSize.x)
	//{
	//	// set animation iterator limit to width of sprite sheet / sprite size x
	//	animation_it_limit = textureBox.width / spriteSize.x;
	//}
	//// else if sprite sheet height is greater than sprite size y
	//else if (textureBox.height > spriteSize.y)
	//{
	//	// set animation iterator limit to height of sprite sheet / sprite size y
	//	animation_it_limit = textureBox.height / spriteSize.y;
	//}
	//// else throw error 
	//else
	//	throw logic_error("Animation bounding box must contain multiply sprites, setSprite(sf::IntRect )\n");

	// set sprites texture rect size to sheet coordinate (left and top) by sprite size (x and y)
	m_Sprite.setTextureRect(sf::IntRect{ sheetCoordinate, spriteSize });

}

void FloatingObstacle::moveTextureRect(float elapsedTime) {
	m_Sprite.setTextureRect(sf::IntRect(sheetCoordinate + sf::Vector2i(
		spriteSize.x, 0), spriteSize));
}

sf::FloatRect FloatingObstacle::getPosition() {
	return m_Sprite.getLocalBounds();
}

sf::FloatRect FloatingObstacle::getGlobal() {
	return m_Sprite.getGlobalBounds();
}

sf::Sprite FloatingObstacle::getSprite() {
	return m_Sprite;
}