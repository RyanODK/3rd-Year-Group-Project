#include "State_Controls.h"
#include "StateManager.h"

State_Controls::State_Controls(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_Controls::~State_Controls() {}

void State_Controls::OnCreate() {
	sf::Vector2u windowSize = m_StateMgr->GetContext()->m_Wind->GetRenderWindow()->getSize();

	m_Font.loadFromFile("Graphics/Fonts/futuremillennium/FutureMillenniumItalic.ttf");

	m_MainTitle.setFont(m_Font);
	m_MainTitle.setString({ "Controls" });
	m_MainTitle.setCharacterSize(90);
	sf::FloatRect titleRect = m_MainTitle.getLocalBounds();
	m_MainTitle.setOrigin(titleRect.left + titleRect.width / 2.0f,
		titleRect.top + titleRect.height / 2.0f);
	m_MainTitle.setPosition(windowSize.x / 2.0f, windowSize.y / 7.0f);

	m_GameControlsTitle.setFont(m_Font);
	m_GameControlsTitle.setString({ "In-Game" });
	m_GameControlsTitle.setCharacterSize(40);
	m_GameControlsTitle.setStyle(sf::Text::Bold);
	sf::FloatRect titleRect1 = m_GameControlsTitle.getLocalBounds();
	m_GameControlsTitle.setOrigin(titleRect1.left + titleRect1.width / 2.0f,
		titleRect1.top + titleRect1.height / 2.0f);
	m_GameControlsTitle.setPosition(windowSize.x / 2.0f, titleRect.top + titleRect.height + 205);

	m_ProgrammerNames.setFont(m_Font);
	m_ProgrammerNames.setString({ "Jump            Space/ \nSlide\nPause\nMainMenu\nFullScreen" });
	m_ProgrammerNames.setCharacterSize(25);
	sf::FloatRect namesRect = m_ProgrammerNames.getLocalBounds();
	m_ProgrammerNames.setOrigin(namesRect.left + namesRect.width / 2.0f,
		namesRect.top + namesRect.height / 2.0f);
	m_ProgrammerNames.setPosition(windowSize.x / 2.1f, titleRect1.top + titleRect1.height + 350);

	xboxAtextureString = "XboxA";

	if (!m_StateMgr->GetContext()->m_TextureManager->RequireResource(xboxAtextureString)) {
		std::cout << "cant find texture" << std::endl;
		xboxAtextureString = "";
		return;
	}

	xboxATexture = m_StateMgr->GetContext()->m_TextureManager->GetResource(xboxAtextureString);
	xboxA.setTexture(*xboxATexture);
	xboxA.setPosition(1340, 310);
	xboxA.setScale(0.4, 0.4);
}

void State_Controls::OnDestroy() {}

void State_Controls::Update(const sf::Time& l_Time) {}

void State_Controls::Draw() {
	sf::RenderWindow* window = m_StateMgr->GetContext()->m_Wind->GetRenderWindow();

	window->draw(m_MainTitle);
	window->draw(m_GameControlsTitle);
	window->draw(m_ProgrammerNames);
	window->draw(xboxA);
	//window->draw(m_ArtistsTitle);
	//window->draw(m_ArtistNames);
	//window->draw(m_SoundTitle);
	//window->draw(m_SoundNames);
	//window->draw(m_MusicTitle);
	//window->draw(m_MusicNames);
	//window->draw(m_MainMenuText);
}

void State_Controls::MainMenu(EventDetails* l_Details) {
	m_StateMgr->SwitchTo(StateType::MainMenu);
}

void State_Controls::Activate() {}

void State_Controls::Deactivate() {}