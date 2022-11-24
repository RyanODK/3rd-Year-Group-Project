#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_Game::~State_Game() {}

void State_Game::OnCreate() {
	m_Resolution.x = sf::VideoMode::getDesktopMode().width;
	m_Resolution.y = sf::VideoMode::getDesktopMode().height;

	// sets groundheight to 75% of screen resolution
	groundHeight = (m_Resolution.y / 100) * 75;

	transform.translate(0, (m_Resolution.y / 100) * 89);

	m_Font.loadFromFile("Graphics/Fonts/futuremillennium/FutureMillennium Italic.ttf");

	// current distance text
	distanceText.setFont(m_Font);
	distanceText.setCharacterSize(70);
	distanceText.setFillColor(sf::Color::White);
	distanceText.setPosition(0, 0);

	// best distance text
	bestDistanceText.setFont(m_Font);
	bestDistanceText.setCharacterSize(35);
	bestDistanceText.setFillColor(sf::Color::White);
	bestDistanceText.setPosition(0, 70);

	// coin count text
	coinCountText.setFont(m_Font);
	coinCountText.setCharacterSize(50);
	coinCountText.setFillColor(sf::Color::Yellow);
	coinCountText.setPosition(0, 105);

	GetSoundManager()->stopMainMenuMusic();
	//GetSoundManager()->playInGameMusic();

	m_background1 = GetFloor()->getTexture();
	m_background1.setSrgb(false);

	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->AddCallback(StateType::Game, "Key_Escape",
		&State_Game::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_P",
		&State_Game::Pause, this);
	evMgr->AddCallback(StateType::Game, "Jump",
		&State_Game::Jump, this);
}

void State_Game::OnDestroy() {
	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_Escape");
	evMgr->RemoveCallback(StateType::Game, "Key_P");
}

void State_Game::Draw() {
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetBackground()->getSprite1());
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetBackground()->getSprite2());
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetBackground()->getSprite3());
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(distanceText);
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(bestDistanceText);
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(coinCountText);
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(background, &m_background1);
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetFloatingObstacle()->getSprite());
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetGroundObstacle()->getSprite());
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetPlayer()->getSprite());

	// Small enemy drawing
	if (backgroundType == 1) {
		m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetSmallEnemy1()->getSprite());
	}

	if (backgroundType == 2) {
		m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetSmallEnemy2()->getSprite());
	}

	if (backgroundType == 3) {
		m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetSmallEnemy3()->getSprite());
	}

	if (backgroundType == 4) {
		m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetSmallEnemy4()->getSprite());
	}

	if (backgroundType == 5) {
		m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->draw(GetSmallEnemy5()->getSprite());
	}
}

void State_Game::Update(const sf::Time& l_Time) {
	resetTime += l_Time.asSeconds();
	distanceRan += l_Time.asSeconds();

	/* TEXT ON SCREEN */
	// current distance
	std::stringstream distanceStream;
	distanceStream.precision(0); // no decimal places
	// fixed will keep it as numbers rather than scientific notation
	distanceStream << std::fixed <<
		distanceRan <<
		"m";

	distanceText.setString(distanceStream.str());

	// best distance
	std::stringstream bestDistanceStream;
	bestDistanceStream.precision(0);
	bestDistanceStream << std::fixed <<
		"Best: " <<
		bestDistance <<
		"m";

	bestDistanceText.setString(bestDistanceStream.str());

	// coin count
	std::stringstream coinStream;
	coinStream.precision(0);
	coinStream << std::fixed <<
		coinCount;

	coinCountText.setString(coinStream.str());

	GetPlayer()->spawn(m_Resolution, gravity);

	// Obstacles
	GetGroundObstacle()->spawn(sf::Vector2f(
			(m_Resolution.x / 100) * 80, (m_Resolution.y / 100) * 80), sf::Vector2f(
				(m_Resolution.x / 100) * 0.06, (m_Resolution.y / 100) * 0.1));

	GetFloatingObstacle()->spawn(sf::Vector2f(
			(m_Resolution.x / 100) * 90, (m_Resolution.y / 100) * 67), sf::Vector2f(
				(m_Resolution.x / 100) * 0.06, (m_Resolution.y / 100) * 0.1));

	GetFloor()->createFloor(background, sf::Vector2f((m_Resolution.x / 100) * 50, (m_Resolution.y / 100) * 50));

	GetGroundObstacle()->update(l_Time.asSeconds());
	GetFloatingObstacle()->update(l_Time.asSeconds());

	CheckCol();

	//GetFloor()->update(l_Time.asSeconds());

	if (resetTime < 5.0f) {
		backgroundType = 1;
		GetBackground()->setBackgroundSpeed(40);
		GetBackground()->ChangeBackground(
			"Graphics/cyberpunk-street-files/PNG/layers/far-buildings.png",
			"Graphics/cyberpunk-street-files/PNG/layers/back-buildings.png",
			"Graphics/cyberpunk-street-files/PNG/layers/foreground.png",
			sf::IntRect(0, 0, 408, 192),
			sf::IntRect(0, 0, 508, 192),
			sf::IntRect(0, 0, 608, 192));
		GetBackground()->BackgroundScale(m_Resolution);
	}

	if (resetTime >= 5.0f) {
		backgroundType = 2;
		GetBackground()->setBackgroundSpeed(35);
		GetBackground()->ChangeBackground(
			"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/back.png",
			"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/middle.png",
			"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/background/front.png",
			sf::IntRect(0, 0, 408, 160),
			sf::IntRect(0, 0, 508, 160),
			sf::IntRect(0, 0, 608, 160));
		GetBackground()->BackgroundScale(m_Resolution);
	}

	if (resetTime >= 10.0f) {
		backgroundType = 3;
		GetBackground()->setBackgroundSpeed(35);
		GetBackground()->ChangeBackground(
			"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/back.png",
			"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/middle.png",
			"Graphics/Rocky Pass Files/Rocky Pass Files/PNG/near.png",
			sf::IntRect(0, 0, 408, 240),
			sf::IntRect(0, 0, 508, 240),
			sf::IntRect(0, 0, 608, 240));
		GetBackground()->BackgroundScale(m_Resolution);
	}

	if (resetTime >= 15.0f) {
		backgroundType = 4;
		GetBackground()->setBackgroundSpeed(35);
		GetBackground()->ChangeBackground(
			"Graphics/gothicvania-cemetery-files/demo/assets/environment/bg-moon.png",
			"Graphics/gothicvania-cemetery-files/demo/assets/environment/bg-mountains.png",
			"Graphics/gothicvania-cemetery-files/demo/assets/environment/bg-graveyard.png",
			sf::IntRect(0, 0, 408, 224),
			sf::IntRect(0, 0, 508, 192),
			sf::IntRect(0, 0, 608, 192));
		GetBackground()->BackgroundScale(m_Resolution);
	}

	/*if (resetTime >= 15.0f) {
		m_background.setBackgroundSpeed(35);
		m_background.ChangeBackground(
			"Graphics/underwater-fantasy-files/PNG/layers/far.png",
			"Graphics/underwater-fantasy-files/PNG/layers/foregound-merged.png",
			"Graphics/underwater-fantasy-files/PNG/layers/sand.png",
			sf::IntRect(0, 0, 408, 192),
			sf::IntRect(0, 0, 508, 192),
			sf::IntRect(0, 0, 608, 192));
		m_background.Scroll(dtAsSeconds);
		m_background.BackgroundScale(m_Resolution);
	}*/

	if (resetTime >= 20.0f) {
		backgroundType = 5;
		GetBackground()->setBackgroundSpeed(40);
		GetBackground()->ChangeBackground(
			"Graphics/Tall Forest Files/Layers/back.png",
			"Graphics/Tall Forest Files/Layers/far.png",
			"Graphics/Tall Forest Files/Layers/middle.png",
			sf::IntRect(0, 0, 408, 240),
			sf::IntRect(0, 0, 508, 240),
			sf::IntRect(0, 0, 608, 240));
		GetBackground()->BackgroundScale(m_Resolution);
	}

	if (resetTime >= 25.0f) {
		resetTime = 0;
	}

	if (backgroundType == 1) {
		GetSmallEnemy1()->SetSprite(1);
		GetSmallEnemy1()->spawn(sf::Vector2f(
			(m_Resolution.x / 100) * 65, (m_Resolution.y / 100) * 77), sf::Vector2f(
				(m_Resolution.x / 100) * -0.22, (m_Resolution.y / 100) * 0.4));
		GetSmallEnemy1()->update(l_Time.asSeconds(), 130);
		GetSmallEnemy1()->updateAnimation(1);
	}
	else if (backgroundType == 2) {
		GetSmallEnemy2()->SetSprite(2);
		GetSmallEnemy2()->spawn(sf::Vector2f(
			(m_Resolution.x / 100) * 50, (m_Resolution.y / 100) * 81), sf::Vector2f(
				(m_Resolution.x / 100) * 0.18, (m_Resolution.y / 100) * 0.37));
		GetSmallEnemy2()->update(l_Time.asSeconds(), 130);
		GetSmallEnemy2()->updateAnimation(2);
	}
	else if (backgroundType == 3) {
		GetSmallEnemy3()->SetSprite(3);
		GetSmallEnemy3()->spawn(sf::Vector2f(
			(m_Resolution.x / 100) * 55, (m_Resolution.y / 100) * 77), sf::Vector2f(
				(m_Resolution.x / 100) * -0.22, (m_Resolution.y / 100) * 0.37));
		GetSmallEnemy3()->update(l_Time.asSeconds(), 90);
		GetSmallEnemy3()->updateAnimation(3);
	}
	else if (backgroundType == 4) {
		GetSmallEnemy4()->SetSprite(4);
		GetSmallEnemy4()->spawn(sf::Vector2f(
			(m_Resolution.x / 100) * 55, (m_Resolution.y / 100) * 76), sf::Vector2f(
				(m_Resolution.x / 100) * -0.15, (m_Resolution.y / 100) * 0.25));
		GetSmallEnemy4()->update(l_Time.asSeconds(), 90);
		GetSmallEnemy4()->updateAnimation(4);
	}
	else if (backgroundType == 5) {
		GetSmallEnemy5()->SetSprite(5);
		GetSmallEnemy5()->spawn(sf::Vector2f(
			(m_Resolution.x / 100) * 55, (m_Resolution.y / 100) * 80), sf::Vector2f(
				(m_Resolution.x / 100) * -0.18, (m_Resolution.y / 100) * 0.28));
		GetSmallEnemy5()->update(l_Time.asSeconds(), 90);
		GetSmallEnemy5()->updateAnimation(5);
	}

	GetPlayer()->update(l_Time.asSeconds(), groundHeight);
	GetBackground()->Scroll(l_Time.asSeconds());
}

void State_Game::Jump(EventDetails* l_Details) {
	if (l_Details->m_Name == "Jump") {
		GetPlayer()->Jump();
	}
}

void State_Game::MainMenu(EventDetails* l_details) {
	m_StateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* l_details) {
	m_StateMgr->SwitchTo(StateType::Paused);
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}