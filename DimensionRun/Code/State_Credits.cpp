#include "State_Credits.h"
#include "StateManager.h"

State_Credits::State_Credits(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_Credits::~State_Credits() {}

void State_Credits::OnCreate() {
	sf::Vector2u windowSize = m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->getSize();

	m_Font.loadFromFile("Graphics/Fonts/futuremillennium/FutureMillenniumItalic.ttf");

	m_MainTitle.setFont(m_Font);
	m_MainTitle.setString({ "Credits" });
	m_MainTitle.setCharacterSize(90);
	sf::FloatRect titleRect = m_MainTitle.getLocalBounds();
	m_MainTitle.setOrigin(titleRect.left + titleRect.width / 2.0f,
		titleRect.top + titleRect.height / 2.0f);
	m_MainTitle.setPosition(windowSize.x / 2.0f, windowSize.y / 5.5f);

	m_ProgrammerTitle.setFont(m_Font);
	m_ProgrammerTitle.setString({ "Programmers" });
	m_ProgrammerTitle.setCharacterSize(40);
	m_ProgrammerTitle.setStyle(sf::Text::Bold);
	sf::FloatRect titleRect1 = m_ProgrammerTitle.getLocalBounds();
	m_ProgrammerTitle.setOrigin(titleRect1.left + titleRect1.width / 2.0f,
		titleRect1.top + titleRect1.height / 2.0f);
	m_ProgrammerTitle.setPosition(windowSize.x / 2.0f, titleRect.top + titleRect.height + 285);

	m_ProgrammerNames.setFont(m_Font);
	m_ProgrammerNames.setString({ "			   Ali Hussein,\n		   Harry Costello,\n Ryan O' Donoghue Kelleher\n" });
	m_ProgrammerNames.setCharacterSize(25);
	sf::FloatRect namesRect = m_ProgrammerNames.getLocalBounds();
	m_ProgrammerNames.setOrigin(namesRect.left + namesRect.width / 2.0f,
		namesRect.top + namesRect.height / 2.0f);
	m_ProgrammerNames.setPosition(windowSize.x / 2.0f, titleRect1.top + titleRect1.height + 420);

	m_ArtistsTitle.setFont(m_Font);
	m_ArtistsTitle.setString({ "Artists" });
	m_ArtistsTitle.setCharacterSize(40);
	m_ArtistsTitle.setStyle(sf::Text::Bold);
	sf::FloatRect titleRect2 = m_ArtistsTitle.getLocalBounds();
	m_ArtistsTitle.setOrigin(titleRect2.left + titleRect2.width / 2.0f,
		titleRect2.top + titleRect2.height / 2.0f);
	m_ArtistsTitle.setPosition(windowSize.x / 2.0f, namesRect.top + namesRect.height + 450);

	m_ArtistNames.setFont(m_Font);
	m_ArtistNames.setString({ "Luis Zuno (@ansimuz),\n	   Moeda Dourada\n" });
	m_ArtistNames.setCharacterSize(25);
	sf::FloatRect namesRect1 = m_ArtistNames.getLocalBounds();
	m_ArtistNames.setOrigin(namesRect1.left + namesRect1.width / 2.0f,
		namesRect1.top + namesRect1.height / 2.0f);
	m_ArtistNames.setPosition(windowSize.x / 2.0f, titleRect2.top + titleRect2.height + 610);

	m_SoundTitle.setFont(m_Font);
	m_SoundTitle.setString({ "Sound" });
	m_SoundTitle.setCharacterSize(40);
	m_SoundTitle.setStyle(sf::Text::Bold);
	sf::FloatRect titleRect3 = m_SoundTitle.getLocalBounds();
	m_SoundTitle.setOrigin(titleRect3.left + titleRect3.width / 2.0f,
		titleRect3.top + titleRect3.height / 2.0f);
	m_SoundTitle.setPosition(windowSize.x / 2.0f, namesRect1.top + namesRect1.height + 640);

	m_SoundNames.setFont(m_Font);
	m_SoundNames.setString({ "phoenix1291\n" });
	m_SoundNames.setCharacterSize(25);
	sf::FloatRect namesRect2 = m_SoundNames.getLocalBounds();
	m_SoundNames.setOrigin(namesRect2.left + namesRect2.width / 2.0f,
		namesRect2.top + namesRect2.height / 2.0f);
	m_SoundNames.setPosition(windowSize.x / 2.0f, titleRect3.top + titleRect3.height + 750);

	m_MusicTitle.setFont(m_Font);
	m_MusicTitle.setString({ "Music" });
	m_MusicTitle.setCharacterSize(40);
	m_MusicTitle.setStyle(sf::Text::Bold);
	sf::FloatRect titleRect4 = m_MusicTitle.getLocalBounds();
	m_MusicTitle.setOrigin(titleRect4.left + titleRect4.width / 2.0f,
		titleRect4.top + titleRect4.height / 2.0f);
	m_MusicTitle.setPosition(windowSize.x / 2.0f, namesRect2.top + namesRect2.height + 780);

	m_MusicNames.setFont(m_Font);
	m_MusicNames.setString({ "		     DavidKBD,\n  Luis Zuno (@ansimuz),\n          Abstraction\n" });
	m_MusicNames.setCharacterSize(25);
	sf::FloatRect namesRect3 = m_MusicNames.getLocalBounds();
	m_MusicNames.setOrigin(namesRect3.left + namesRect3.width / 2.0f,
		namesRect3.top + namesRect3.height / 2.0f);
	m_MusicNames.setPosition(windowSize.x / 2.0f, titleRect4.top + titleRect4.height + 880);

	m_MainMenuText.setFont(m_Font);
	m_MainMenuText.setString({ "Press SPACE or A for Main Menu" });
	m_MainMenuText.setCharacterSize(20);
	sf::FloatRect mainMenuRect = m_MainMenuText.getLocalBounds();
	m_MainMenuText.setOrigin(mainMenuRect.left + mainMenuRect.width / 2.0f,
		mainMenuRect.top + mainMenuRect.height / 2.0f);
	m_MainMenuText.setPosition(windowSize.x / 2.0f, namesRect3.top + namesRect3.height + 960);

	m_StateMgr->GetContext()->m_SoundManager->PlayMusic("CreditsMusic", 10.f, true);

	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->AddCallback(StateType::Credits, "Intro_ContinueKeyboard",
		&State_Credits::MainMenu, this);
	evMgr->AddCallback(StateType::Credits, "Intro_ContinueJoystick",
		&State_Credits::MainMenu, this);
}

void State_Credits::OnDestroy() {
	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->RemoveCallback(StateType::Credits, "Intro_ContinueKeyboard");
	evMgr->RemoveCallback(StateType::Credits, "Intro_ContinueJoystick");
}

void State_Credits::Update(const sf::Time& l_Time) {}

void State_Credits::Draw() {
	sf::RenderWindow* window = m_StateMgr->GetContext()->m_Wind->GetRenderWindow();

	window->draw(m_MainTitle);
	window->draw(m_ProgrammerTitle);
	window->draw(m_ProgrammerNames);
	window->draw(m_ArtistsTitle);
	window->draw(m_ArtistNames);
	window->draw(m_SoundTitle);
	window->draw(m_SoundNames);
	window->draw(m_MusicTitle);
	window->draw(m_MusicNames);
	window->draw(m_MainMenuText);
}

void State_Credits::MainMenu(EventDetails* l_Details){
	m_StateMgr->SwitchTo(StateType::MainMenu);
}

void State_Credits::Activate() {}

void State_Credits::Deactivate() {}

