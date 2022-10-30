#include "Background.h"

Background::Background() {
	m_BackgroundSpeed = 50.0f;
	m_BackgroundX = 0;

	m_BackgroundTexture1.loadFromFile(
		"Graphics/cyberpunk-street-files/PNG/layers/far-buildings.png");
	m_BackgroundTexture1.setRepeated(true); // repeats texture
	m_BackgroundSprite1.setTexture(m_BackgroundTexture1);
	m_BackgroundSprite1.setPosition(0, 0);
	m_BackgroundSprite1.setTextureRect(IntRect(0, 0, 408, 192));

	m_BackgroundTexture2.loadFromFile(
		"Graphics/cyberpunk-street-files/PNG/layers/back-buildings.png");
	m_BackgroundTexture2.setRepeated(true); // repeats texture
	m_BackgroundSprite2.setTexture(m_BackgroundTexture2);
	m_BackgroundSprite2.setPosition(0, 0);
	m_BackgroundSprite2.setTextureRect(IntRect(0, 0, 508, 192)); // sets texture rectangle to original texture size

	m_BackgroundTexture3.loadFromFile(
		"Graphics/cyberpunk-street-files/PNG/layers/foreground.png");
	m_BackgroundTexture3.setRepeated(true); // repeats texture
	m_BackgroundSprite3.setTexture(m_BackgroundTexture3);
	m_BackgroundSprite3.setPosition(0, 0);
	m_BackgroundSprite3.setTextureRect(IntRect(0, 0, 608, 192)); // sets texture rectangle to original texture size
}

void Background::BackgroundScale(Vector2f resolution) {
	m_BackgroundSprite1.setScale(resolution.x / m_BackgroundSprite1.getLocalBounds().width,
		resolution.y / m_BackgroundSprite1.getLocalBounds().height);

	m_BackgroundSprite2.setScale(resolution.x / m_BackgroundSprite2.getLocalBounds().width,
		resolution.y / m_BackgroundSprite2.getLocalBounds().height);

	m_BackgroundSprite3.setScale(resolution.x / m_BackgroundSprite3.getLocalBounds().width,
		resolution.y / m_BackgroundSprite3.getLocalBounds().height);

	// store resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Background::Scroll(float dt) {
	if (m_BackgroundX < m_Resolution.x) {
		m_BackgroundX += m_BackgroundSpeed * dt;
	}
	else {
		m_BackgroundX = 0;
	}
	m_BackgroundSprite1.setTextureRect(IntRect(m_BackgroundX, 0, 408, 192));
	m_BackgroundSprite2.setTextureRect(IntRect(m_BackgroundX, 0, 508, 192));
	m_BackgroundSprite3.setTextureRect(IntRect(m_BackgroundX, 0, 608, 192));
}

void Background::ChangeBackground(
	string filename1, string filename2, string filename3,
	IntRect rect1, IntRect rect2, IntRect rect3) {

	m_BackgroundTexture1.loadFromFile(filename1);
	m_BackgroundSprite1.setTextureRect(rect1);

	m_BackgroundTexture2.loadFromFile(filename2);
	m_BackgroundSprite2.setTextureRect(rect2); // sets texture rectangle to original texture size

	m_BackgroundTexture3.loadFromFile(filename3);
	m_BackgroundSprite3.setTextureRect(rect3); // sets texture rectangle to original texture size
}

Sprite Background::getSprite1() {
	return m_BackgroundSprite1;
}

Sprite Background::getSprite2() {
	return m_BackgroundSprite2;
}

Sprite Background::getSprite3() {
	return m_BackgroundSprite3;
}