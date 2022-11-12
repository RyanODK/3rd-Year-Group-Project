#include "Engine.h"

void Engine::update(float dtAsSeconds) {
	m_player.spawn(m_resolution, gravity);
	//m_groundObstacle.spawn(m_resolution);
	//m_floatingObstacle.spawn(m_resolution);

	m_mainMenuBackground.setBackgroundSpeed(40);
	m_mainMenuBackground.ChangeBackground(
		"Graphics/warped city files/ENVIRONMENT/background/skyline-b.png",
		"Graphics/warped city files/ENVIRONMENT/background/buildings-bg.png",
		"Graphics/warped city files/ENVIRONMENT/background/near-buildings-bg.png",
		IntRect(0, 0, 408, 240),
		IntRect(0, 0, 508, 240),
		IntRect(0, 0, 608, 192));
	m_mainMenuBackground.Scroll(dtAsSeconds);
	m_mainMenuBackground.BackgroundScale(m_resolution);

	if (state == State::PLAYING) {
		m_player.update(dtAsSeconds, groundHeight);

		//if active is true then spawn, if false dont, have random number to spawn 

		m_groundObstacle.spawn(Vector2f(
			(m_resolution.x / 100) * 80, (m_resolution.y / 100) * 80), Vector2f(
				(m_resolution.x / 100) * 0.06, (m_resolution.y / 100) * 0.1));
		m_floatingObstacle.spawn(Vector2f(
			(m_resolution.x / 100) * 90, (m_resolution.y / 100) * 67), Vector2f(
				(m_resolution.x / 100) * 0.06, (m_resolution.y / 100) * 0.1));


		m_floatingObstacle.update(dtAsSeconds);
		m_groundObstacle.update(dtAsSeconds);
		checkCol(m_player);

		m_background.Scroll(dtAsSeconds);

		if (resetTime < 5.0f) {
			backgroundType = 1;
			m_background.setBackgroundSpeed(40);
			m_background.ChangeBackground(
				"Graphics/cyberpunk-street-files/PNG/layers/far-buildings.png",
				"Graphics/cyberpunk-street-files/PNG/layers/back-buildings.png",
				"Graphics/cyberpunk-street-files/PNG/layers/foreground.png",
				IntRect(0, 0, 408, 192),
				IntRect(0, 0, 508, 192),
				IntRect(0, 0, 608, 192));
			m_background.Scroll(dtAsSeconds);
			m_background.BackgroundScale(m_resolution);
		}

		if (resetTime >= 5.0f) {
			backgroundType = 2;
			m_background.setBackgroundSpeed(35);
			m_background.ChangeBackground(
				"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/back.png",
				"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/middle.png",
				"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/front.png",
				IntRect(0, 0, 408, 160),
				IntRect(0, 0, 508, 160),
				IntRect(0, 0, 608, 160));
			m_background.Scroll(dtAsSeconds);
			m_background.BackgroundScale(m_resolution);
		}

		if (resetTime >= 10.0f) {
			backgroundType = 3;
			m_background.setBackgroundSpeed(20);
			m_background.ChangeBackground(
				"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/back.png",
				"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/middle.png",
				"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/near.png",
				IntRect(0, 0, 408, 240),
				IntRect(0, 0, 508, 240),
				IntRect(0, 0, 608, 240));
			m_background.Scroll(dtAsSeconds);
			m_background.BackgroundScale(m_resolution);
		}

		if (resetTime >= 15.0f) {
			m_background.setBackgroundSpeed(35);
			m_background.ChangeBackground(
				"Graphics/underwater-fantasy-files/PNG/layers/far.png",
				"Graphics/underwater-fantasy-files/PNG/layers/foregound-merged.png",
				"Graphics/underwater-fantasy-files/PNG/layers/sand.png",
				IntRect(0, 0, 408, 192),
				IntRect(0, 0, 508, 192),
				IntRect(0, 0, 608, 192));
			m_background.Scroll(dtAsSeconds);
			m_background.BackgroundScale(m_resolution);
		}

		if (resetTime >= 20.0f) {
			m_background.setBackgroundSpeed(20);
			m_background.ChangeBackground(
				"Graphics/Tall Forest Files/Layers/back.png",
				"Graphics/Tall Forest Files/Layers/far.png",
				"Graphics/Tall Forest Files/Layers/middle.png",
				IntRect(0, 0, 408, 240),
				IntRect(0, 0, 508, 240),
				IntRect(0, 0, 608, 240));
			m_background.Scroll(dtAsSeconds);
			m_background.BackgroundScale(m_resolution);
		}

		if (resetTime >= 25.0f) {
			resetTime = 0;
		}


		if (backgroundType == 1) {
			m_SmallEnemy1.SetSprite(1);
			m_SmallEnemy1.spawn(Vector2f(
				(m_resolution.x / 100) * 65, (m_resolution.y / 100) * 77), Vector2f(
					(m_resolution.x / 100) * -0.22, (m_resolution.y / 100) * 0.4));
			m_SmallEnemy1.update(dtAsSeconds, 90);
			m_SmallEnemy1.updateAnimation(1);
		}
		else if (backgroundType == 2) {
			m_SmallEnemy2.SetSprite(2);
			m_SmallEnemy2.spawn(Vector2f(
				(m_resolution.x / 100) * 70, (m_resolution.y / 100) * 73), Vector2f(
					(m_resolution.x / 100) * 0.1, (m_resolution.y / 100) * 0.2));
			m_SmallEnemy2.update(dtAsSeconds, 80);
			m_SmallEnemy2.updateAnimation(2);
		}
		else if (backgroundType == 3) {
			m_SmallEnemy3.SetSprite(3);
			m_SmallEnemy3.spawn(Vector2f(
				(m_resolution.x / 100) * 55, (m_resolution.y / 100) * 78), Vector2f(
					(m_resolution.x / 100) * -0.22, (m_resolution.y / 100) * 0.37));
			m_SmallEnemy3.update(dtAsSeconds, 50);
			m_SmallEnemy3.updateAnimation(3);
		}
	}
}