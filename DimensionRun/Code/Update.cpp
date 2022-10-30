#include "Engine.h"

void Engine::update(float dtAsSeconds) {
	m_player.spawn(m_resolution, gravity);

	m_SmallEnemy1.SetSprite(1);
	m_SmallEnemy2.SetSprite(2);
	m_SmallEnemy3.SetSprite(3);

	m_SmallEnemy1.spawn(Vector2f(1600, 980), Vector2f(2, 2));
	m_SmallEnemy2.spawn(Vector2f(1650, 1080), Vector2f(-6, 6));
	m_SmallEnemy3.spawn(Vector2f(1100, 1000), Vector2f(-4, 4));

	m_background.BackgroundScale(m_resolution);


	if (state == State::PLAYING) {
		m_player.update(dtAsSeconds, groundHeight);
		
		m_SmallEnemy1.update(dtAsSeconds);
		m_SmallEnemy2.update(dtAsSeconds);
		m_SmallEnemy3.update(dtAsSeconds);

		m_SmallEnemy1.updateAnimation(1);
		m_SmallEnemy2.updateAnimation(2);
		m_SmallEnemy3.updateAnimation(3);

		m_background.Scroll(dtAsSeconds);

		if (m_GameTimeTotal.asSeconds() > 5.0f) {
			m_background.ChangeBackground(
				"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/back.png",
				"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/middle.png",
				"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/front.png",
				IntRect(0, 0, 408, 160), IntRect(0, 0, 508, 160), IntRect(0, 0, 608, 160));
			m_background.Scroll(dtAsSeconds);
		}

		if (m_GameTimeTotal.asSeconds() > 7.0f) {
			m_background.ChangeBackground(
				"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/back.png",
				"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/middle.png",
				"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/near.png",
				IntRect(0, 0, 408, 240), IntRect(0, 0, 508, 240), IntRect(0, 0, 608, 240));
			m_background.Scroll(dtAsSeconds);
		}

		if (m_GameTimeTotal.asSeconds() > 10.0f) {
			m_background.ChangeBackground(
				"Graphics/underwater-fantasy-files/PNG/layers/far.png",
				"Graphics/underwater-fantasy-files/PNG/layers/foregound-merged.png",
				"Graphics/underwater-fantasy-files/PNG/layers/sand.png",
				IntRect(0, 0, 408, 192),
				IntRect(0, 0, 508, 192),
				IntRect(0, 0, 608, 192));
			m_background.Scroll(dtAsSeconds);
		}
	}
}