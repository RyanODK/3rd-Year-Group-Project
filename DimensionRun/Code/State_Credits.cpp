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
	m_MainTitle.setPosition(windowSize.x / 2.0f, windowSize.y / 5.0f);

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
	m_ArtistNames.setString({ "			   Ali Hussein,\n		   Harry Costello,\n Ryan O' Donoghue Kelleher\n" });
	m_ArtistNames.setCharacterSize(25);
	sf::FloatRect namesRect1 = m_ArtistNames.getLocalBounds();
	m_ArtistNames.setOrigin(namesRect1.left + namesRect1.width / 2.0f,
		namesRect1.top + namesRect1.height / 2.0f);
	m_ArtistNames.setPosition(windowSize.x / 2.0f, titleRect2.top + titleRect2.height + 610);
}

void State_Credits::OnDestroy() {}

void State_Credits::Update(const sf::Time& l_Time) {
	//// less than five seconds
	//if (m_TimePassed < 5.0f) {
	//	m_TimePassed += l_Time.asSeconds();

	//	m_MainTitle.setPosition(m_MainTitle.getPosition().x,
	//		m_MainTitle.getPosition().y - (38 * l_Time.asSeconds()));

	//	m_ProgrammerTitle.setPosition(m_ProgrammerTitle.getPosition().x,
	//		m_ProgrammerTitle.getPosition().y - (38 * l_Time.asSeconds()));

	//	m_ProgrammerNames.setPosition(m_ProgrammerNames.getPosition().x,
	//		m_ProgrammerNames.getPosition().y - (38 * l_Time.asSeconds()));

	//	m_ArtistsTitle.setPosition(m_ArtistsTitle.getPosition().x,
	//		m_ArtistsTitle.getPosition().y - (38 * l_Time.asSeconds()));

	//	m_ArtistNames.setPosition(m_ArtistNames.getPosition().x,
	//		m_ArtistNames.getPosition().y - (38 * l_Time.asSeconds()));
	//}
}

void State_Credits::Draw() {
	sf::RenderWindow* window = m_StateMgr->GetContext()->m_Wind->GetRenderWindow();

	window->draw(m_MainTitle);
	window->draw(m_ProgrammerTitle);
	window->draw(m_ProgrammerNames);
	window->draw(m_ArtistsTitle);
	window->draw(m_ArtistNames);
}

void State_Credits::MainMenu(EventDetails* l_Details){
	m_StateMgr->SwitchTo(StateType::MainMenu);
}

void State_Credits::Activate() {}

void State_Credits::Deactivate() {}

