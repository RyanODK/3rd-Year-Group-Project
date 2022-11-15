#include "Engine.h"

void Engine::update() {
	m_Window.Update();
	m_StateManager.Update(m_Elapsed);

	//m_player.spawn(m_resolution, gravity);
	////m_groundObstacle.spawn(m_resolution);
	////m_floatingObstacle.spawn(m_resolution);

	//m_mainMenuBackground.setBackgroundSpeed(40);
	//m_mainMenuBackground.ChangeBackground(
	//	"Graphics/warped city files/ENVIRONMENT/background/skyline-b.png",
	//	"Graphics/warped city files/ENVIRONMENT/background/buildings-bg.png",
	//	"Graphics/warped city files/ENVIRONMENT/background/near-buildings-bg.png",
	//	IntRect(0, 0, 408, 240),
	//	IntRect(0, 0, 508, 240),
	//	IntRect(0, 0, 608, 192));
	//m_mainMenuBackground.Scroll(dtAsSeconds);
	//m_mainMenuBackground.BackgroundScale(m_resolution);

	//if (state == State::PLAYING) {
	//	m_player.update(dtAsSeconds, groundHeight);

	//	//if active is true then spawn, if false dont, have random number to spawn 

	//	m_groundObstacle.spawn(Vector2f(
	//		(m_resolution.x / 100) * 80, (m_resolution.y / 100) * 80), Vector2f(
	//			(m_resolution.x / 100) * 0.06, (m_resolution.y / 100) * 0.1));
	//	m_floatingObstacle.spawn(Vector2f(
	//		(m_resolution.x / 100) * 90, (m_resolution.y / 100) * 67), Vector2f(
	//			(m_resolution.x / 100) * 0.06, (m_resolution.y / 100) * 0.1));


	//	m_floatingObstacle.update(dtAsSeconds);
	//	m_groundObstacle.update(dtAsSeconds);
	//	checkCol(m_player);

	//	m_background.Scroll(dtAsSeconds);

	//	if (resetTime < 5.0f) {
	//		backgroundType = 1;
	//		m_background.setBackgroundSpeed(40);
	//		m_background.ChangeBackground(
	//			"Graphics/cyberpunk-street-files/PNG/layers/far-buildings.png",
	//			"Graphics/cyberpunk-street-files/PNG/layers/back-buildings.png",
	//			"Graphics/cyberpunk-street-files/PNG/layers/foreground.png",
	//			IntRect(0, 0, 408, 192),
	//			IntRect(0, 0, 508, 192),
	//			IntRect(0, 0, 608, 192));
	//		m_background.Scroll(dtAsSeconds);
	//		m_background.BackgroundScale(m_resolution);
	//	}

	//	if (resetTime >= 5.0f) {
	//		backgroundType = 2;
	//		m_background.setBackgroundSpeed(35);
	//		m_background.ChangeBackground(
	//			"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/back.png",
	//			"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/middle.png",
	//			"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/front.png",
	//			IntRect(0, 0, 408, 160),
	//			IntRect(0, 0, 508, 160),
	//			IntRect(0, 0, 608, 160));
	//		m_background.Scroll(dtAsSeconds);
	//		m_background.BackgroundScale(m_resolution);
	//	}

	//	if (resetTime >= 10.0f) {
	//		backgroundType = 3;
	//		m_background.setBackgroundSpeed(20);
	//		m_background.ChangeBackground(
	//			"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/back.png",
	//			"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/middle.png",
	//			"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/near.png",
	//			IntRect(0, 0, 408, 240),
	//			IntRect(0, 0, 508, 240),
	//			IntRect(0, 0, 608, 240));
	//		m_background.Scroll(dtAsSeconds);
	//		m_background.BackgroundScale(m_resolution);
	//	}

	//	if (resetTime >= 15.0f) {
	//		backgroundType = 4;
	//		m_background.setBackgroundSpeed(20);
	//		m_background.ChangeBackground(
	//			"Graphics/gothicvania-cemetery-files/demo/assets/environment/bg-moon.png",
	//			"Graphics/gothicvania-cemetery-files/demo/assets/environment/bg-mountains.png",
	//			"Graphics/gothicvania-cemetery-files/demo/assets/environment/bg-graveyard.png",
	//			IntRect(0, 0, 408, 224),
	//			IntRect(0, 0, 508, 192),
	//			IntRect(0, 0, 608, 192));
	//		m_background.Scroll(dtAsSeconds);
	//		m_background.BackgroundScale(m_resolution);
	//	}

	//	/*if (resetTime >= 15.0f) {
	//		m_background.setBackgroundSpeed(35);
	//		m_background.ChangeBackground(
	//			"Graphics/underwater-fantasy-files/PNG/layers/far.png",
	//			"Graphics/underwater-fantasy-files/PNG/layers/foregound-merged.png",
	//			"Graphics/underwater-fantasy-files/PNG/layers/sand.png",
	//			IntRect(0, 0, 408, 192),
	//			IntRect(0, 0, 508, 192),
	//			IntRect(0, 0, 608, 192));
	//		m_background.Scroll(dtAsSeconds);
	//		m_background.BackgroundScale(m_resolution);
	//	}*/

	//	if (resetTime >= 20.0f) {
	//		backgroundType = 5;
	//		m_background.setBackgroundSpeed(20);
	//		m_background.ChangeBackground(
	//			"Graphics/Tall Forest Files/Layers/back.png",
	//			"Graphics/Tall Forest Files/Layers/far.png",
	//			"Graphics/Tall Forest Files/Layers/middle.png",
	//			IntRect(0, 0, 408, 240),
	//			IntRect(0, 0, 508, 240),
	//			IntRect(0, 0, 608, 240));
	//		m_background.Scroll(dtAsSeconds);
	//		m_background.BackgroundScale(m_resolution);
	//	}

	//	if (resetTime >= 25.0f) {
	//		resetTime = 0;
	//	}

	//	m_Portal.SetSprite(6);
	//	m_Portal.spawn(Vector2f(
	//		(m_resolution.x / 100) - 770, (m_resolution.y / 100) + 120), Vector2f(
	//			(m_resolution.x / 100) * 0.1, (m_resolution.y / 100) * 0.22));
	//	m_Portal.update(dtAsSeconds, 0);
	//	m_Portal.updateAnimation(6);

	//	if (backgroundType == 1) {
	//		m_SmallEnemy1.SetSprite(1);
	//		m_SmallEnemy1.spawn(Vector2f(
	//			(m_resolution.x / 100) * 65, (m_resolution.y / 100) * 77), Vector2f(
	//				(m_resolution.x / 100) * -0.22, (m_resolution.y / 100) * 0.4));
	//		m_SmallEnemy1.update(dtAsSeconds, 90);
	//		m_SmallEnemy1.updateAnimation(1);
	//	}
	//	else if (backgroundType == 2) {
	//		m_SmallEnemy2.SetSprite(2);
	//		m_SmallEnemy2.spawn(Vector2f(
	//			(m_resolution.x / 100) * 50, (m_resolution.y / 100) * 81), Vector2f(
	//				(m_resolution.x / 100) * 0.18, (m_resolution.y / 100) * 0.37));
	//		m_SmallEnemy2.update(dtAsSeconds, 80);
	//		m_SmallEnemy2.updateAnimation(2);
	//	}
	//	else if (backgroundType == 3) {
	//		m_SmallEnemy3.SetSprite(3);
	//		m_SmallEnemy3.spawn(Vector2f(
	//			(m_resolution.x / 100) * 55, (m_resolution.y / 100) * 77), Vector2f(
	//				(m_resolution.x / 100) * -0.22, (m_resolution.y / 100) * 0.37));
	//		m_SmallEnemy3.update(dtAsSeconds, 50);
	//		m_SmallEnemy3.updateAnimation(3);
	//	}
	//	else if (backgroundType == 4) {
	//		m_SmallEnemy4.SetSprite(4);
	//		m_SmallEnemy4.spawn(Vector2f(
	//			(m_resolution.x / 100) * 55, (m_resolution.y / 100) * 76), Vector2f(
	//				(m_resolution.x / 100) * -0.15, (m_resolution.y / 100) * 0.25));
	//		m_SmallEnemy4.update(dtAsSeconds, 50);
	//		m_SmallEnemy4.updateAnimation(4);
	//	}
	//	else if (backgroundType == 5) {
	//		m_SmallEnemy5.SetSprite(5);
	//		m_SmallEnemy5.spawn(Vector2f(
	//			(m_resolution.x / 100) * 55, (m_resolution.y / 100) * 80), Vector2f(
	//				(m_resolution.x / 100) * -0.18, (m_resolution.y / 100) * 0.28));
	//		m_SmallEnemy5.update(dtAsSeconds, 50);
	//		m_SmallEnemy5.updateAnimation(5);
	//	}
	//}
}