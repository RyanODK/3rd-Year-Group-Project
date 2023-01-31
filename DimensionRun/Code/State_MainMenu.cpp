#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::OnCreate() {
	EventManager* eMgr = m_StateMgr->GetContext()->m_EventManager;
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_PlayMouse", &State_MainMenu::Play, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_CreditsMouse", &State_MainMenu::Credits, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_QuitMouse", &State_MainMenu::Quit, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_PlayJoystick", &State_MainMenu::Play, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_CreditsJoystick", &State_MainMenu::Credits, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_QuitJoystick", &State_MainMenu::Quit, this);

	GUI_Manager* gui = m_StateMgr->GetContext()->m_GuiManager;

	sf::Vector2f size = m_StateMgr->GetContext()->m_Wind->GetWindowSize();

	m_StateMgr->GetContext()->m_SoundManager->PlayMusic("MainMenuMusic", 10.f, true);

	buttonBuffer.loadFromFile("Code/Resources/Media/Audio/InGameSounds/Sounds/button.ogg");
	buttonSound.setBuffer(buttonBuffer);
	buttonSound.setVolume(50);

	textureString = "XboxA";

	if (!m_StateMgr->GetContext()->m_TextureManager->RequireResource(textureString)) {
		std::cout << "cant find texture" << std::endl;
		textureString = "";
		return;
	}

	texture = m_StateMgr->GetContext()->m_TextureManager->GetResource(textureString);
	XboxA.setTexture(*texture);

	sf::Vector2u textureSize1 = texture->getSize();
	m_ScaleFactors.x = size.x / textureSize1.x;
	m_ScaleFactors.y = size.y / textureSize1.y;
	XboxA.setScale(m_ScaleFactors);
	XboxA.setPosition(1400, 500);

	if (size.x == 2560 && size.y == 1440) {
		gui->LoadInterface(StateType::MainMenu, "MainMenu1440.interface", "MainMenu");
	}
	else if (size.x == 1920 && size.y == 1080) {
		gui->LoadInterface(StateType::MainMenu, "MainMenu1080.interface", "MainMenu");
	}
	else if (size.x == 1680 && size.y == 1050) {
		gui->LoadInterface(StateType::MainMenu, "MainMenu1050.interface", "MainMenu");
	}
	else {
		gui->LoadInterface(StateType::MainMenu, "MainMenu1080.interface", "MainMenu");
	}

	gui->GetInterface(StateType::MainMenu, "MainMenu")->SetPosition(
		sf::Vector2f((sf::VideoMode::getDesktopMode().width / 100) * 0,
			(sf::VideoMode::getDesktopMode().height / 100) * 0));
}

void State_MainMenu::OnDestroy() {
	EventManager* eMgr = m_StateMgr->GetContext()->m_EventManager;
	GUI_Manager* gui = m_StateMgr->GetContext()->m_GuiManager;
	gui->RemoveInterface(StateType::MainMenu, "MainMenu");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_PlayMouse");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_CreditsMouse");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_QuitMouse");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_PlayJoystick");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_CreditsJoystick");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_QuitJoystick");

	m_StateMgr->GetContext()->m_TextureManager->ReleaseResource(textureString);
}

void State_MainMenu::Activate() {
	auto& play = *m_StateMgr->GetContext()->m_GuiManager->
		GetInterface(StateType::MainMenu, "MainMenu")->GetElement("Play");
	if (m_StateMgr->HasState(StateType::Game)) {
		// Resume
		play.SetText("Resume");
	}
	else {
		// Play
		play.SetText("Play");
	}
}

void State_MainMenu::Play(EventDetails* l_details) { 
	buttonSound.play();
	m_StateMgr->SwitchTo(StateType::Game); 
}

void State_MainMenu::Credits(EventDetails* l_details) {
	buttonSound.play();
	m_StateMgr->SwitchTo(StateType::Credits);
}

void State_MainMenu::Quit(EventDetails* l_details) { 
	buttonSound.play();
	exit(0);
	m_StateMgr->GetContext()->m_Wind->Close(); 
}

void State_MainMenu::Draw() {
	sf::RenderWindow* window = m_StateMgr->GetContext()->m_Wind->GetRenderWindow();

	window->draw(XboxA);
}

void State_MainMenu::Deactivate() {}

void State_MainMenu::Update(const sf::Time& l_Time) {}