#include "State_GameOver.h"
#include "StateManager.h"

State_GameOver::State_GameOver(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_GameOver::~State_GameOver() {}

void State_GameOver::OnCreate() {
	GUI_Manager* gui = m_StateMgr->GetContext()->m_GuiManager;

	sf::Vector2f size = m_StateMgr->GetContext()->m_Wind->GetWindowSize();

	if (size.x == 2560 && size.y == 1440) {
		gui->LoadInterface(StateType::GameOver, "GameOver1440.interface", "GameOver");
	}
	else if (size.x == 1920 && size.y == 1080) {
		gui->LoadInterface(StateType::GameOver, "GameOver1080.interface", "GameOver");
	}
	else if (size.x == 1680 && size.y == 1050) {
		gui->LoadInterface(StateType::GameOver, "GameOver1050.interface", "GameOver");
	}
	else {
		gui->LoadInterface(StateType::GameOver, "GameOver1080.interface", "GameOver");
	}

	gui->GetInterface(StateType::GameOver, "GameOver")->SetPosition(
		sf::Vector2f((sf::VideoMode::getDesktopMode().width / 100) * 0,
			(sf::VideoMode::getDesktopMode().height / 100) * 0));

	EventManager* eMgr = m_StateMgr->GetContext()->m_EventManager;
	eMgr->AddCallback(StateType::GameOver, "GameOver_RetryMouse", &State_GameOver::Retry, this);
	eMgr->AddCallback(StateType::GameOver, "GameOver_MainMenuMouse", &State_GameOver::MainMenu, this);

	m_StateMgr->GetContext()->m_SoundManager->PlayMusic("GameOverMusic", 40.f, true);
}

void State_GameOver::OnDestroy() {
	m_StateMgr->GetContext()->m_GuiManager->RemoveInterface(StateType::GameOver, "GameOver");
	EventManager* eMgr = m_StateMgr->GetContext()->m_EventManager;
	GUI_Manager* gui = m_StateMgr->GetContext()->m_GuiManager;
	gui->RemoveInterface(StateType::GameOver, "GameOver");
	eMgr->RemoveCallback(StateType::GameOver, "GameOver_RetryMouse");
	eMgr->RemoveCallback(StateType::GameOver, "GameOver_MainMenuMouse");
}

void State_GameOver::Update(const sf::Time& l_Time) {}

void State_GameOver::Draw() {}

void State_GameOver::Retry(EventDetails* l_Details)
{
	m_StateMgr->SwitchTo(StateType::Game);
	m_StateMgr->Remove(StateType::GameOver);
}

void State_GameOver::MainMenu(EventDetails* l_Details)
{
	m_StateMgr->SwitchTo(StateType::MainMenu);
	m_StateMgr->Remove(StateType::GameOver);
}

void State_GameOver::Activate() {}

void State_GameOver::Deactivate() {}

