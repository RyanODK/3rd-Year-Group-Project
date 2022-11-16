#include "State_Game.h"

State_Game::State_Game(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_Game::~State_Game() {}

void State_Game::OnCreate() {
	//if (resetTime < 5.0f) {
	//	//backgroundType = 1;
	//	GetBackground()->setBackgroundSpeed(40);
	//	GetBackground()->ChangeBackground(
	//		"Graphics/cyberpunk-street-files/PNG/layers/far-buildings.png",
	//		"Graphics/cyberpunk-street-files/PNG/layers/back-buildings.png",
	//		"Graphics/cyberpunk-street-files/PNG/layers/foreground.png",
	//		sf::IntRect(0, 0, 408, 192),
	//		sf::IntRect(0, 0, 508, 192),
	//		sf::IntRect(0, 0, 608, 192));
	//	GetBackground()->BackgroundScale(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	//}

	//if (resetTime >= 5.0f) {
	//	//backgroundType = 2;
	//	GetBackground()->setBackgroundSpeed(35);
	//	GetBackground()->ChangeBackground(
	//		"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/back.png",
	//		"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/middle.png",
	//		"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/front.png",
	//		sf::IntRect(0, 0, 408, 160),
	//		sf::IntRect(0, 0, 508, 160),
	//		sf::IntRect(0, 0, 608, 160));
	//	GetBackground()->BackgroundScale(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	//}

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

	/*if (resetTime >= 10.0f) {
		resetTime = 0;
	}

	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->AddCallback(StateType::Game, "Mouse_Left",
		&State_MainMenu::MouseClick, this);*/
}

void State_Game::OnDestroy() {}

void State_Game::Activate() {}

void State_Game::Draw() {}

void State_Game::Deactivate() {}

void State_Game::Update(const sf::Time& l_Time) {
	/*resetTime += l_Time.asSeconds();

	GetBackground()->Scroll(l_Time.asSeconds());*/
}