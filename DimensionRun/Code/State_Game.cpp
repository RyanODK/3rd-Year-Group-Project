#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager* l_StateManager) : 
	BaseState(l_StateManager) {}

State_Game::~State_Game() {}

void State_Game::OnCreate() {
	srand((unsigned)time(NULL));

	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->AddCallback(StateType::Game, "Key_MainMenuKeyboard", &State_Game::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_MainMenuJoystick", &State_Game::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_PauseKeyboard", &State_Game::Pause, this);
	evMgr->AddCallback(StateType::Game, "Key_PauseJoystick", &State_Game::Pause, this);
	evMgr->AddCallback(StateType::Game, "Key_O", &State_Game::ToggleOverlay, this);

	sf::Vector2f size = m_StateMgr->GetContext()->m_Wind->GetWindowSize();
	m_View.setSize(size.x, size.y);
	m_View.setCenter(size.x / 2, size.y / 2);

	if (size.x == 2560 && size.y == 1440) {
		m_View.zoom(0.5f);
	}
	else if (size.x == 1920 && size.y == 1080) {
		m_View.zoom(0.7f);
	}
	else if (size.x == 1680 && size.y == 1050) {
		m_View.zoom(0.7f);
	}
	else {
		m_View.zoom(0.7f);
	}
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->setView(m_View);

	m_GameMap = new Map(m_StateMgr->GetContext(), this);
	m_GameMap->CreateMap();
	m_GameMap->LoadMap("Code/Maps/map1.map");

	randomMusic = 1 + (rand() % 3);

	if (randomMusic == 1) {
		m_StateMgr->GetContext()->m_SoundManager->PlayMusic("InGameMusic1", 10.f, true);
	}
	else if (randomMusic == 2) {
		m_StateMgr->GetContext()->m_SoundManager->PlayMusic("InGameMusic2", 10.f, true);
	}
	else if (randomMusic == 3) {
		m_StateMgr->GetContext()->m_SoundManager->PlayMusic("InGameMusic3", 10.f, true);
	}
}

void State_Game::OnDestroy() {
	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_MainMenuKeyboard");
	evMgr->RemoveCallback(StateType::Game, "Key_MainMenuJoystick");
	evMgr->RemoveCallback(StateType::Game, "Key_PauseKeyboard"); 
	evMgr->RemoveCallback(StateType::Game, "Key_PauseJoystick");
	evMgr->RemoveCallback(StateType::Game, "Key_O");
	
	delete m_GameMap;
	m_GameMap = nullptr;
}

void State_Game::Draw() {
	m_GameMap->Draw();
	m_StateMgr->GetContext()->m_EntityManager->Draw();
	m_StateMgr->GetContext()->m_Wind->Draw(distanceText);
	m_StateMgr->GetContext()->m_Wind->Draw(coinCountText);
}

void State_Game::Update(const sf::Time& l_Time) {
	SharedContext* context = m_StateMgr->GetContext();
	EntityBase* player = context->m_EntityManager->Find("Player");
	sf::Vector2f size = m_StateMgr->GetContext()->m_Wind->GetWindowSize();
	m_Distance += l_Time.asSeconds();

	if (!player) {
		std::cout << "Respawning player..." << std::endl;
		context->m_EntityManager->AddEntity(EntityType::Player, "Player");
		player = context->m_EntityManager->Find("Player");
		player->SetPosition(m_GameMap->GetPlayerStart());
		m_StateMgr->SwitchTo(StateType::GameOver);
		m_StateMgr->Remove(StateType::Game);
	}
	else {
		if (size.x == 2560 && size.y == 1440) {
			m_View.setCenter(player->GetPosition().x + 300, (size.y / 100) * 70);
		}
		else if(size.x == 1920 && size.y == 1080) {
			m_View.setCenter(player->GetPosition().x + 300, (size.y / 100) * 92);
		}
		else if (size.x == 1680 && size.y == 1050) {
			m_View.setCenter(player->GetPosition().x + 300, (size.y / 100) * 95);
		}
		else {
			m_View.setCenter(player->GetPosition().x + 300, (size.y / 100) * 95);
		}
		context->m_Wind->GetRenderWindow()->setView(m_View);
	}

	sf::FloatRect viewSpace = context->m_Wind->GetViewSpace();

	if (viewSpace.left <= 0) {
		m_View.setCenter(viewSpace.width / 2, m_View.getCenter().y);
		context->m_Wind->GetRenderWindow()->setView(m_View);
	}
	else if (viewSpace.left + viewSpace.width > (m_GameMap->GetMapSize().x + 1) * Sheet::Tile_Size) {
		m_View.setCenter(((m_GameMap->GetMapSize().x + 1) * Sheet::Tile_Size) - (viewSpace.width / 2), m_View.getCenter().y);
		context->m_Wind->GetRenderWindow()->setView(m_View);
	}

	distanceText.setFont(*m_StateMgr->GetContext()->m_FontManager->GetResource("Main"));
	distanceText.setPosition(context->m_Wind->GetRenderWindow()->getView().getCenter() - sf::Vector2f(
		context->m_Wind->GetRenderWindow()->getView().getSize().x / 2,
		context->m_Wind->GetRenderWindow()->getView().getSize().y / 3));
	distanceText.setCharacterSize(70);
	distanceText.setFillColor(sf::Color::White);

	coinCountText.setFont(*m_StateMgr->GetContext()->m_FontManager->GetResource("Main"));
	coinCountText.setPosition(context->m_Wind->GetRenderWindow()->getView().getCenter() - sf::Vector2f(
		context->m_Wind->GetRenderWindow()->getView().getSize().x / 2,
		context->m_Wind->GetRenderWindow()->getView().getSize().y / 2));
	coinCountText.setCharacterSize(70);
	coinCountText.setFillColor(sf::Color::White);

	m_GameMap->CreateMap();
	m_GameMap->Update(l_Time.asSeconds());
	m_StateMgr->GetContext()->m_EntityManager->Update(l_Time.asSeconds());

	coinCount = player->GetCoinCount();
	//std::cout << coinCount << std::endl;

	std::stringstream distanceStream;
	std::stringstream coinStream;
	distanceStream << m_Distance;
	coinStream << coinCount;

	distanceText.setString(distanceStream.str());
	coinCountText.setString("hi: " + coinStream.str());
}

void State_Game::MainMenu(EventDetails* l_details) {
	m_StateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* l_details) {
	m_StateMgr->SwitchTo(StateType::Paused);
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}

void State_Game::ToggleOverlay(EventDetails* l_details) {
	m_StateMgr->GetContext()->m_DebugOverlay.SetDebug(!m_StateMgr->GetContext()->m_DebugOverlay.Debug());
}