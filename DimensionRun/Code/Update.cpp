#include "Engine.h"

void Engine::update(float dtAsSeconds) {
	m_player.spawn(m_resolution, gravity);

	//enemy.spawn(resolution, elapsedTime, gravity);

	m_background.BackgroundScale(m_resolution);


	if (m_Playing) {
		m_player.update(dtAsSeconds);
		//enemy.update();
		m_background.Update(dtAsSeconds);
	}
}