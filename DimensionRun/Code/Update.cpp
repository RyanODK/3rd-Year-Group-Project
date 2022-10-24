#include "Engine.h"

void Engine::update(float dtAsSeconds) {
	//if (!m_spawned) {
	
	// tried to fix the spawning issue as player spawns on top left
	// if i try to fix it this way, it constantly sets position of player
	// which breaks jump
	m_player.spawn(m_resolution, gravity/*, m_spawned*/);

	//}

	//enemy.spawn(resolution, elapsedTime, gravity);

	m_background.BackgroundScale(m_resolution);


	if (m_Playing) {
		m_player.update(dtAsSeconds, groundHeight);
		//enemy.update();
		m_background.Update(dtAsSeconds);
	}
}