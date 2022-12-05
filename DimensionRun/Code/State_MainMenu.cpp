#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::OnCreate() {
	GetBackground()->setBackgroundSpeed(40);
	GetBackground()->ChangeBackground(
		"Graphics/warped city files/ENVIRONMENT/background/skyline-b.png",
		"Graphics/warped city files/ENVIRONMENT/background/buildings-bg.png",
		"Graphics/warped city files/ENVIRONMENT/background/near-buildings-bg.png",
		sf::IntRect(0, 0, 408, 240),
		sf::IntRect(0, 0, 508, 240),
		sf::IntRect(0, 0, 608, 192));
	GetBackground()->BackgroundScale(sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));

	m_Font.loadFromFile("Graphics/Fonts/futuremillennium/FutureMillennium Italic.ttf");
	m_MainTitle.setFont(m_Font);
	m_MainTitle.setString({ "Dimension Run" });
	m_MainTitle.setCharacterSize(80);
	sf::FloatRect titleRect = m_MainTitle.getLocalBounds();
	m_MainTitle.setOrigin(titleRect.left + titleRect.width / 2.0f,
		titleRect.top + titleRect.height / 2.0f);
	m_MainTitle.setPosition(400, 100);

	m_ButtonSize = sf::Vector2f(300.0f, 32.0f);
	m_ButtonPos = sf::Vector2f(400, 200);
	m_ButtonPadding = 4;

	std::string str[3];
	str[0] = "PLAY";
	str[1] = "CREDITS";
	str[2] = "EXIT";

	for (int i = 0; i < 3; i++) {
		sf::Vector2f buttonPosition(m_ButtonPos.x, m_ButtonPos.y +
			(i * (m_ButtonSize.y + m_ButtonPadding)));
		m_Rects[i].setSize(m_ButtonSize);
		m_Rects[i].setFillColor(sf::Color::Red);

		m_Rects[i].setOrigin(m_ButtonSize.x / 2.0f,
			m_ButtonSize.y / 2.0f);
		m_Rects[i].setPosition(buttonPosition);

		m_Options[i].setFont(m_Font);
		m_Options[i].setString(sf::String(str[i]));
		m_Options[i].setCharacterSize(40);

		sf::FloatRect rect = m_Options[i].getLocalBounds();
		m_Options[i].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_Options[i].setPosition(buttonPosition);
	}

	//GetSoundManager()->stopInGameMusic();
	//GetSoundManager()->playMainMenuMusic();
	m_StateMgr->GetContext()->m_SoundManager->PlayMusic("MainMenuMusic", 40.f, true);

	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->AddCallback(StateType::MainMenu, "Mouse_Left",
		&State_MainMenu::MouseClick, this);
}

void State_MainMenu::OnDestroy() {
	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}

void State_MainMenu::Activate() {
	if (m_StateMgr->HasState(StateType::Game) &&
		m_Options[0].getString() == "PLAY") {
		sf::FloatRect rect = m_Options[0].getLocalBounds();
		m_Options[0].setOrigin(rect.left + rect.width / 2.0f, rect.top +
			rect.height / 2.0f);
	}
}

void State_MainMenu::MouseClick(EventDetails* l_Details) {
	sf::Vector2i mousePos = l_Details->m_Mouse;

	float halfX = m_ButtonSize.x / 2.0f;
	float halfY = m_ButtonSize.y / 2.0f;

	for (int i = 0; i < 3; i++) {
		if (mousePos.x >= m_Rects[i].getPosition().x - halfX &&
			mousePos.x <= m_Rects[i].getPosition().x + halfX &&
			mousePos.y >= m_Rects[i].getPosition().y - halfY &&
			mousePos.y <= m_Rects[i].getPosition().y + halfY) {
			if (i == 0) {
				m_StateMgr->SwitchTo(StateType::Game);
			}
			else if (i == 1) {
				//m_StateMgr->SwitchTo(StateType::Credits);
			}
			else if (i == 2) {
				m_StateMgr->GetContext()->m_Wind->Close();
			}
		}
	}
}

void State_MainMenu::Draw() {
	sf::RenderWindow* window = m_StateMgr->GetContext()->m_Wind->GetRenderWindow();
	window->draw(GetBackground()->getSprite1());
	window->draw(GetBackground()->getSprite2());
	window->draw(GetBackground()->getSprite3());
	window->draw(m_MainTitle);

	for (int i = 0; i < 3; i++) {
		window->draw(m_Rects[i]);
		window->draw(m_Options[i]);
	}
}

void State_MainMenu::Deactivate() {}

void State_MainMenu::Update(const sf::Time& l_Time){
	//m_dtAsSeconds += l_Time.asSeconds();
	GetBackground()->Scroll(l_Time.asSeconds());
}