#include "State_Intro.h"
#include "StateManager.h"

State_Intro::State_Intro(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_Intro::~State_Intro() {}

void State_Intro::OnCreate() {
	sf::Vector2u windowSize = m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->getSize();

	m_Font.loadFromFile("Graphics/Fonts/futuremillennium/FutureMillenniumItalic.ttf");

	m_MainTitle.setFont(m_Font);
	m_MainTitle.setString({ "Dimension Run" });
	m_MainTitle.setCharacterSize(80);
	sf::FloatRect titleRect = m_MainTitle.getLocalBounds();
	m_MainTitle.setOrigin(titleRect.left + titleRect.width / 2.0f,
		titleRect.top + titleRect.height / 2.0f);
	m_MainTitle.setPosition(windowSize.x / 2.0f, 0);

	m_Names.setFont(m_Font);
	m_Names.setString({ "			Ali Hussein,\n		Harry Costello,\nRyan O' Donoghue Kelleher,\n		Edvinas Dirmeikis" });
	m_Names.setCharacterSize(30);
	sf::FloatRect namesRect = m_Names.getLocalBounds();
	m_Names.setOrigin(namesRect.left + namesRect.width / 2.0f,
		namesRect.top + namesRect.height / 2.0f);
	m_Names.setPosition(windowSize.x / 2.0f, titleRect.top + titleRect.height + 20);

	m_continueText.setFont(m_Font);
	m_continueText.setString({ "Press SPACE to continue" });
	m_continueText.setCharacterSize(20);
	sf::FloatRect continueRect = m_continueText.getLocalBounds();
	m_continueText.setOrigin(continueRect.left + continueRect.width / 2.0f,
		continueRect.top + continueRect.height / 2.0f);
	m_continueText.setPosition(windowSize.x / 2.0f, namesRect.top + namesRect.height + 45);

	m_StateMgr->GetContext()->m_SoundManager->PlayMusic("IntroMusic", 40.f, true);

	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->AddCallback(StateType::Intro, "Intro_ContinueKeyboard",
		&State_Intro::Continue, this);
	evMgr->AddCallback(StateType::Intro, "Intro_ContinueJoystick",
		&State_Intro::Continue, this);
}

void State_Intro::OnDestroy() {
	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->RemoveCallback(StateType::Intro, "Intro_ContinueKeyboard");
	evMgr->RemoveCallback(StateType::Intro, "Intro_ContinueJoystick");
}

void State_Intro::Update(const sf::Time& l_Time) {
	// less than five seconds
	if (m_TimePassed < 5.0f) {
		m_TimePassed += l_Time.asSeconds();
		m_MainTitle.setPosition(m_MainTitle.getPosition().x,
			m_MainTitle.getPosition().y + (38 * l_Time.asSeconds()));

		m_Names.setPosition(m_Names.getPosition().x,
			m_Names.getPosition().y + (38 * l_Time.asSeconds()));

		m_continueText.setPosition(m_continueText.getPosition().x,
			m_continueText.getPosition().y + (38 * l_Time.asSeconds()));
	}
}

void State_Intro::Draw() {
	sf::RenderWindow* window = m_StateMgr->GetContext()->m_Wind->GetRenderWindow();

	window->draw(m_MainTitle);

	if (m_TimePassed >= 5.0f) {
		window->draw(m_Names);
		window->draw(m_continueText);
	}
}

void State_Intro::Continue(EventDetails* l_Details) {
	if (m_TimePassed >= 5.0f) {
		m_StateMgr->SwitchTo(StateType::MainMenu);
		m_StateMgr->Remove(StateType::Intro);
	}
}

void State_Intro::Activate() {

}

void State_Intro::Deactivate() {

}

