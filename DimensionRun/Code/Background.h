#include <SFML/Graphics.hpp>
#include <sstream>
#ifndef BACKGROUND_H
#define BACKGROUND_H

using namespace sf;

class Background {
public:
	Background();
	void BackgroundScale(Vector2f resolution);
	void Update(Time& deltaTime);
	void Render(RenderWindow& window);

private:
	Texture m_BackgroundTexture;

	Sprite m_BackgroundSprite;

	float m_BackgroundSpeed;
	float m_BackgroundX;

	Vector2f m_Resolution;
};
#endif