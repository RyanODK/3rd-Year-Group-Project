#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::OnCreate() {
	GUI_Manager* gui = m_StateMgr->GetContext()->m_GuiManager;

	sf::Vector2f size = m_StateMgr->GetContext()->m_Wind->GetWindowSize();

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

	EventManager* eMgr = m_StateMgr->GetContext()->m_EventManager;
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_PlayMouse", &State_MainMenu::Play, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_QuitMouse", &State_MainMenu::Quit, this);
	
	m_StateMgr->GetContext()->m_SoundManager->PlayMusic("MainMenuMusic", 25.f, true);
}

void State_MainMenu::OnDestroy() {
	m_StateMgr->GetContext()->m_GuiManager->RemoveInterface(StateType::MainMenu, "MainMenu");
	EventManager* eMgr = m_StateMgr->GetContext()->m_EventManager;
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_PlayMouse");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_QuitMouse");
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

//void State_MainMenu::MouseClick(EventDetails* l_Details) {
//	sf::Vector2i mousePos = l_Details->m_Mouse;
//
//	float halfX = m_ButtonSize.x / 2.0f;
//	float halfY = m_ButtonSize.y / 2.0f;
//
//	for (int i = 0; i < 3; i++) {
//		if (mousePos.x >= m_Rects[i].getPosition().x - halfX &&
//			mousePos.x <= m_Rects[i].getPosition().x + halfX &&
//			mousePos.y >= m_Rects[i].getPosition().y - halfY &&
//			mousePos.y <= m_Rects[i].getPosition().y + halfY) {
//			if (i == 0) {
//				m_StateMgr->SwitchTo(StateType::Game);
//			}
//			else if (i == 1) {
//				//m_StateMgr->SwitchTo(StateType::Credits);
//			}
//			else if (i == 2) {
//				m_StateMgr->GetContext()->m_Wind->Close();
//			}
//		}
//	}
//}

void State_MainMenu::Play(EventDetails* l_details) { 
	m_StateMgr->SwitchTo(StateType::Game); 
}

void State_MainMenu::Credits(EventDetails* l_details) {}

void State_MainMenu::Quit(EventDetails* l_details) { 
	m_StateMgr->GetContext()->m_Wind->Close(); 
}

void State_MainMenu::Draw() {}

void State_MainMenu::Deactivate() {}

void State_MainMenu::Update(const sf::Time& l_Time) {}