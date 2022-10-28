#include "Engine.h"

void Engine::update(float dtAsSeconds) {
	m_player.spawn(m_resolution, gravity);

	m_SmallEnemy1.SetSprite(1);
	m_SmallEnemy2.SetSprite(2);
	m_SmallEnemy3.SetSprite(3);

	m_SmallEnemy1.spawn(Vector2f(800, 980), Vector2f(2, 2));
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

		m_background.Update(dtAsSeconds);
	}
}