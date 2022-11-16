#include "State_Paused.h"
#include "StateManager.h"

State_Paused::State_Paused(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_Paused::~State_Paused() {}

void State_Paused::OnCreate() {
	SetTransparent(true);

	m_Font.loadFromFile("Graphics/Fonts/futuremillennium/FutureMillennium Italic.ttf");
	m_PausedText.setFont(m_Font);
	m_PausedText.setString(sf::String("PAUSED"));
	m_PausedText.setCharacterSize(80);
	m_PausedText.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->getSize();

	sf::FloatRect textRect = m_PausedText.getLocalBounds();
	m_PausedText.setOrigin(textRect.left + textRect.width / 2.0f, 
		textRect.top + textRect.height / 2.0f);
	m_PausedText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_Rect.setSize(sf::Vector2f(windowSize));
	m_Rect.setPosition(0, 0);
	m_Rect.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->AddCallback(StateType::Paused, "Key_P", &State_Paused::Unpause, this);
}

void State_Paused::OnDestroy() {
	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->RemoveCallback(StateType::Paused, "Key_P");
}

void State_Paused::Draw() {
	sf::RenderWindow* wind = m_StateMgr->GetContext()->m_Wind->GetRenderWindow();

	wind->draw(m_Rect);
	wind->draw(m_PausedText);
}

void State_Paused::Unpause(EventDetails* l_Details) {
	m_StateMgr->SwitchTo(StateType::Game);
}

void State_Paused::Update(const sf::Time& l_Time){}

void State_Paused::Activate(){}

void State_Paused::Deactivate(){}