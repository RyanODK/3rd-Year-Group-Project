#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager* l_StateManager) : 
	BaseState(l_StateManager) {}

State_Game::~State_Game() {}

void State_Game::OnCreate() {
	//m_Resolution.x = sf::VideoMode::getDesktopMode().width;
	//m_Resolution.y = sf::VideoMode::getDesktopMode().height;

	//// sets groundheight to 75% of screen resolution
	////groundHeight = (m_Resolution.y / 100) * 75;

	////transform.translate(0, (m_Resolution.y / 100) * 89);

	//m_Font.loadFromFile("Graphics/Fonts/futuremillennium/FutureMillennium Italic.ttf");

	//// current distance text
	//distanceText.setFont(m_Font);
	//distanceText.setCharacterSize(70);
	//distanceText.setFillColor(sf::Color::White);
	//distanceText.setPosition(0, 0);

	//// best distance text
	//bestDistanceText.setFont(m_Font);
	//bestDistanceText.setCharacterSize(35);
	//bestDistanceText.setFillColor(sf::Color::White);
	//bestDistanceText.setPosition(0, 70);

	//// coin count text
	//coinCountText.setFont(m_Font);
	//coinCountText.setCharacterSize(50);
	//coinCountText.setFillColor(sf::Color::Yellow);
	//coinCountText.setPosition(0, 105);

	//GetSoundManager()->stopMainMenuMusic();
	//GetSoundManager()->playInGameMusic();

	//m_background1 = GetFloor()->getTexture();
	//m_background1.setSrgb(false);

	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
	evMgr->AddCallback(StateType::Game, "Key_O", &State_Game::ToggleOverlay, this);
	evMgr->AddCallback(StateType::Game, "Player_MoveLeft", &State_Game::PlayerMove, this);
	evMgr->AddCallback(StateType::Game, "Player_MoveRight", &State_Game::PlayerMove, this);
	evMgr->AddCallback(StateType::Game, "Player_MoveUp", &State_Game::PlayerMove, this);
	evMgr->AddCallback(StateType::Game, "Player_MoveDown", &State_Game::PlayerMove, this);

	sf::Vector2u size = m_StateMgr->GetContext()->m_Wind->GetWindowSize();
	m_View.setSize(size.x, size.y);
	m_View.setCenter(size.x / 2, size.y / 2);
	//m_View.zoom(0.5f);
	m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->setView(m_View);

	m_GameMap = new Map(m_StateMgr->GetContext());
	m_GameMap->LoadMap("Code/Maps/map1.map");

	EntityManager* entities = m_StateMgr->GetContext()->m_EntityManager;
	m_StateMgr->GetContext()->m_SystemManager->GetSystem<S_Collision>(System::Collision)->SetMap(m_GameMap);
	m_StateMgr->GetContext()->m_SystemManager->GetSystem<S_Movement>(System::Movement)->SetMap(m_GameMap);
	m_Player = m_GameMap->GetPlayerId();

	//m_StateMgr->GetContext()->m_SoundManager->PlayMusic("InGameMusic1", 40.f, true);
}

void State_Game::OnDestroy() {
	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_Escape");
	evMgr->RemoveCallback(StateType::Game, "Key_P");
	evMgr->RemoveCallback(StateType::Game, "Key_O");
	evMgr->RemoveCallback(StateType::Game, "Player_MoveLeft");
	evMgr->RemoveCallback(StateType::Game, "Player_MoveRight");
	evMgr->RemoveCallback(StateType::Game, "Player_MoveUp");
	evMgr->RemoveCallback(StateType::Game, "Player_MoveDown");
	
	delete m_GameMap;
}

void State_Game::Draw() {
	for (unsigned int i = 0; i < Sheet::Num_Layers; ++i) {
		m_GameMap->Draw(i);
		m_StateMgr->GetContext()->m_SystemManager->Draw(
			m_StateMgr->GetContext()->m_Wind, i);
	}
}

void State_Game::Update(const sf::Time& l_Time) {
	SharedContext* context = m_StateMgr->GetContext();
	UpdateCamera();
	m_GameMap->Update(l_Time.asSeconds());
	context->m_SystemManager->Update(l_Time.asSeconds());
}

void State_Game::MainMenu(EventDetails* l_details) {
	m_StateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails* l_details) {
	m_StateMgr->SwitchTo(StateType::Paused);
}

void State_Game::UpdateCamera() {
	if (m_Player == -1) { return; }
	SharedContext* context = m_StateMgr->GetContext();
	C_Position* pos = m_StateMgr->GetContext()->m_EntityManager->
		GetComponent<C_Position>(m_Player, Component::Position);

 	m_View.setCenter(pos->GetPosition());
	context->m_Wind->GetRenderWindow()->setView(m_View);

	sf::FloatRect viewSpace = context->m_Wind->GetViewSpace();
	if (viewSpace.left <= 0) {
		m_View.setCenter(viewSpace.width / 2, m_View.getCenter().y);
		context->m_Wind->GetRenderWindow()->setView(m_View);
	}
	else if (viewSpace.left + viewSpace.width >
		(m_GameMap->GetMapSize().x) * Sheet::Tile_Size)
	{
		m_View.setCenter(
			((m_GameMap->GetMapSize().x) * Sheet::Tile_Size) -
			(viewSpace.width / 2), m_View.getCenter().y);
		context->m_Wind->GetRenderWindow()->setView(m_View);
	}

	if (viewSpace.top <= 0) {
		m_View.setCenter(m_View.getCenter().x, viewSpace.height / 2);
		context->m_Wind->GetRenderWindow()->setView(m_View);
	}
	else if (viewSpace.top + viewSpace.height >
		(m_GameMap->GetMapSize().y) * Sheet::Tile_Size)
	{
		m_View.setCenter(m_View.getCenter().x,
			((m_GameMap->GetMapSize().y) * Sheet::Tile_Size) -
			(viewSpace.height / 2));
		context->m_Wind->GetRenderWindow()->setView(m_View);
	}

	if (context->m_DebugOverlay.Debug()) {
		sf::Text* d_pos = new sf::Text();
		sf::Text* d_Animation = new sf::Text();
		C_SpriteSheet* sheet = m_StateMgr->GetContext()->m_EntityManager->GetComponent<C_SpriteSheet>(m_Player, Component::SpriteSheet);
		const std::string& animName = sheet->GetSpriteSheet()->GetCurrentAnim()->GetName();

		d_pos->setFont(*m_StateMgr->GetContext()->m_FontManager->GetResource("Main"));
		d_pos->setString("Player position: " +
			std::to_string((long long)pos->GetPosition().x) + "x " + std::to_string((long long)pos->GetPosition().y) + "y");
		d_pos->setCharacterSize(20);
		d_pos->setPosition(context->m_Wind->GetRenderWindow()->getView().getCenter() - sf::Vector2f(
			context->m_Wind->GetRenderWindow()->getView().getSize().x / 2,
			context->m_Wind->GetRenderWindow()->getView().getSize().y / 2));

		d_Animation->setFont(*m_StateMgr->GetContext()->m_FontManager->GetResource("Main"));
		d_Animation->setString("Player animation: " + animName);
		d_Animation->setCharacterSize(20);
		d_Animation->setPosition(context->m_Wind->GetRenderWindow()->getView().getCenter() - sf::Vector2f(
			context->m_Wind->GetRenderWindow()->getView().getSize().x / 2,
			context->m_Wind->GetRenderWindow()->getView().getSize().y / 3));

		context->m_DebugOverlay.Add(d_pos);
		context->m_DebugOverlay.Add(d_Animation);
	}
}

void State_Game::PlayerMove(EventDetails* l_details) {
	Message msg((MessageType)EntityMessage::Move);
	if (l_details->m_Name == "Player_MoveLeft") {
		msg.m_int = (int)Direction::Left;
	}
	else if (l_details->m_Name == "Player_MoveRight") {
		msg.m_int = (int)Direction::Right;
	}
	else if (l_details->m_Name == "Player_MoveUp") {
		msg.m_int = (int)Direction::Up;
	}
	else if (l_details->m_Name == "Player_MoveDown") {
		msg.m_int = (int)Direction::Down;
	}
	msg.m_receiver = m_Player;
	m_StateMgr->GetContext()->m_SystemManager->GetMessageHandler()->Dispatch(msg);
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}

void State_Game::ToggleOverlay(EventDetails* l_details) {
	m_StateMgr->GetContext()->m_DebugOverlay.SetDebug(!m_StateMgr->GetContext()->m_DebugOverlay.Debug());
}