#include "Background.h"

Background::Background() {
	m_BackgroundSpeed = 0.3f;

	m_BackgroundTexture.loadFromFile("Graphics/cyberpunk-street-files/PNG/cyberpunk-street.png");
	m_BackgroundTexture.setSmooth(false);
	m_BackgroundTexture.setRepeated(true);
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	m_BackgroundSprite.setPosition(0, 0);
	m_BackgroundX = 0;
	m_BackgroundSprite.setTextureRect(IntRect(0, 0, 608, 192));
}

void Background::BackgroundScale(Vector2f resolution) {
	m_BackgroundSprite.setScale(resolution.x / m_BackgroundSprite.getLocalBounds().width,
		resolution.y / m_BackgroundSprite.getLocalBounds().height);

	// store resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Background::Update(Time& deltaTime) {
	if (m_BackgroundX < m_Resolution.x) {
		m_BackgroundX += m_BackgroundSpeed * deltaTime.asSeconds();
	}
	else {
		m_BackgroundX = 0;
	}
	m_BackgroundSprite.setTextureRect(IntRect(m_BackgroundX, 0, 608, 192));
}

void Background::Render(RenderWindow& window) {
	window.draw(m_BackgroundSprite);
}