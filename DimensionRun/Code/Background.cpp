#include "Background.h"

Background::Background() {
	m_BackgroundSpeed = 50.0f;
	m_BackgroundX = 0;
}

void Background::BackgroundScale(sf::Vector2f resolution) {
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

	m_BackgroundSprite1.setTextureRect(sf::IntRect(
		m_BackgroundX,
		m_BackgroundSprite1.getTextureRect().top,
		m_BackgroundSprite1.getTextureRect().width,
		m_BackgroundSprite1.getTextureRect().height));

	m_BackgroundSprite2.setTextureRect(sf::IntRect(
		m_BackgroundX,
		m_BackgroundSprite2.getTextureRect().top,
		m_BackgroundSprite2.getTextureRect().width,
		m_BackgroundSprite2.getTextureRect().height));

	m_BackgroundSprite3.setTextureRect(sf::IntRect(
		m_BackgroundX,
		m_BackgroundSprite3.getTextureRect().top,
		m_BackgroundSprite3.getTextureRect().width,
		m_BackgroundSprite3.getTextureRect().height));
}

void Background::ChangeBackground(
	std::string filename1, std::string filename2, std::string filename3,
	sf::IntRect rect1, sf::IntRect rect2, sf::IntRect rect3) {

	m_BackgroundSprite1 = sf::Sprite(TextureHolder::GetTexture(filename1, true));
	m_BackgroundSprite1.setTextureRect(rect1);

	m_BackgroundSprite2 = sf::Sprite(TextureHolder::GetTexture(filename2, true));
	m_BackgroundSprite2.setTextureRect(rect2);

	m_BackgroundSprite3 = sf::Sprite(TextureHolder::GetTexture(filename3, true));
	m_BackgroundSprite3.setTextureRect(rect3);
}

sf::Sprite Background::getSprite1() {
	return m_BackgroundSprite1;
}

sf::Sprite Background::getSprite2() {
	return m_BackgroundSprite2;
}

sf::Sprite Background::getSprite3() {
	return m_BackgroundSprite3;
}

void Background::setBackgroundSpeed(float backgroundSpeed) {
	m_BackgroundSpeed = backgroundSpeed;
}