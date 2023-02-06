#include "State_Controls.h"
#include "StateManager.h"

State_Controls::State_Controls(StateManager* l_StateManager) :
	BaseState(l_StateManager) {}

State_Controls::~State_Controls() {}

void State_Controls::OnCreate() {
	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->AddCallback(StateType::Controls, "Intro_ContinueKeyboard",
		&State_Controls::MainMenu, this);
	evMgr->AddCallback(StateType::Controls, "Intro_ContinueJoystick",
		&State_Controls::MainMenu, this);

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

	m_InGameControls.setFont(m_Font);
	m_InGameControls.setString({ "Jump                Space/ \nSlide                        T/\nPause                      P/\nMainMenu          ESC/\nFullScreen       F5/" });
	m_InGameControls.setCharacterSize(25);
	sf::FloatRect namesRect = m_InGameControls.getLocalBounds();
	m_InGameControls.setOrigin(namesRect.left + namesRect.width / 2.0f,
		namesRect.top + namesRect.height / 2.0f);
	m_InGameControls.setPosition(windowSize.x / 2.1f, titleRect1.top + titleRect1.height + 350);

	m_MainMenuControlsTitle.setFont(m_Font);
	m_MainMenuControlsTitle.setString({ "Main Menu/Game Over" });
	m_MainMenuControlsTitle.setCharacterSize(40);
	m_MainMenuControlsTitle.setStyle(sf::Text::Bold);
	sf::FloatRect titleRect2 = m_MainMenuControlsTitle.getLocalBounds();
	m_MainMenuControlsTitle.setOrigin(titleRect2.left + titleRect2.width / 2.0f,
		titleRect2.top + titleRect2.height / 2.0f);
	m_MainMenuControlsTitle.setPosition(windowSize.x / 2.0f, namesRect.top + namesRect.height + 410);

	m_MainMenuControls.setFont(m_Font);
	m_MainMenuControls.setString({ "Play                                          Mouse/ \nCredits                                    Mouse/\nControls                                Mouse/\nExit/MainMenu                      Mouse/\n" });
	m_MainMenuControls.setCharacterSize(25);
	sf::FloatRect namesRect1 = m_MainMenuControls.getLocalBounds();
	m_MainMenuControls.setOrigin(namesRect1.left + namesRect1.width / 2.0f,
		namesRect1.top + namesRect1.height / 2.0f);
	m_MainMenuControls.setPosition(windowSize.x / 2.1f, titleRect2.top + titleRect2.height + 610);

	m_MainMenuText.setFont(m_Font);
	m_MainMenuText.setString({ "Press SPACE or A to continue" });
	m_MainMenuText.setCharacterSize(20);
	sf::FloatRect continueRect = m_MainMenuText.getLocalBounds();
	m_MainMenuText.setOrigin(continueRect.left + continueRect.width / 2.0f,
		continueRect.top + continueRect.height / 2.0f);
	m_MainMenuText.setPosition(windowSize.x / 2.0f, namesRect1.top + namesRect1.height + 680);

	xboxAtextureString = "XboxA";
	xboxBtextureString = "XboxB";
	xboxXtextureString = "XboxX";
	xboxYtextureString = "XboxY";
	xboxMenutextureString = "XboxMenu";
	xboxWindowtextureString = "XboxWindow";

	if (!m_StateMgr->GetContext()->m_TextureManager->RequireResource(xboxAtextureString)) {
		std::cout << "cant find texture" << std::endl;
		xboxAtextureString = "";
		return;
	}
	if (!m_StateMgr->GetContext()->m_TextureManager->RequireResource(xboxBtextureString)) {
		std::cout << "cant find texture" << std::endl;
		xboxBtextureString = "";
		return;
	}
	if (!m_StateMgr->GetContext()->m_TextureManager->RequireResource(xboxXtextureString)) {
		std::cout << "cant find texture" << std::endl;
		xboxXtextureString = "";
		return;
	}
	if (!m_StateMgr->GetContext()->m_TextureManager->RequireResource(xboxYtextureString)) {
		std::cout << "cant find texture" << std::endl;
		xboxYtextureString = "";
		return;
	}
	if (!m_StateMgr->GetContext()->m_TextureManager->RequireResource(xboxMenutextureString)) {
		std::cout << "cant find texture" << std::endl;
		xboxMenutextureString = "";
		return;
	}
	if (!m_StateMgr->GetContext()->m_TextureManager->RequireResource(xboxWindowtextureString)) {
		std::cout << "cant find texture" << std::endl;
		xboxWindowtextureString = "";
		return;
	}

	xboxATexture = m_StateMgr->GetContext()->m_TextureManager->GetResource(xboxAtextureString);
	xboxA.setTexture(*xboxATexture);
	xboxA.setPosition(1050, 310);
	//xboxA.setPosition((windowSize.x / 100) * 53.98, (windowSize.y / 100) * 21.98);
	xboxA.setScale(0.4, 0.4);

	xboxA1.setTexture(*xboxATexture);
	xboxA1.setPosition(1140, 570);
	//xboxA1.setPosition((windowSize.x / 100) * 57.98, (windowSize.y / 100) * 40.5);
	xboxA1.setScale(0.4, 0.4);

	xboxBTexture = m_StateMgr->GetContext()->m_TextureManager->GetResource(xboxBtextureString);
	xboxB.setTexture(*xboxBTexture);
	xboxB.setPosition(1050, 340);
	//xboxB.setPosition((windowSize.x / 100) * 53.98, (windowSize.y / 100) * 24.1);
	xboxB.setScale(0.4, 0.4);

	xboxB1.setTexture(*xboxBTexture);
	xboxB1.setPosition(1140, 660);
	//xboxB1.setPosition((windowSize.x / 100) * 57.98, (windowSize.y / 100) * 47.4);
	xboxB1.setScale(0.4, 0.4);

	xboxXTexture = m_StateMgr->GetContext()->m_TextureManager->GetResource(xboxXtextureString);
	xboxX.setTexture(*xboxXTexture);
	xboxX.setPosition(1140, 600);
	//xboxX.setPosition((windowSize.x / 100) * 57.98, (windowSize.y / 100) * 42.8);
	xboxX.setScale(0.4, 0.4);

	xboxYTexture = m_StateMgr->GetContext()->m_TextureManager->GetResource(xboxYtextureString);
	xboxY.setTexture(*xboxYTexture);
	xboxY.setPosition(1050, 370);
	//xboxY.setPosition((windowSize.x / 100) * 53.98, (windowSize.y / 100) * 26.4);
	xboxY.setScale(0.4, 0.4);

	xboxY1.setTexture(*xboxYTexture);
	xboxY1.setPosition(1140, 630);
	//xboxY1.setPosition((windowSize.x / 100) * 57.98, (windowSize.y / 100) * 45.1);
	xboxY1.setScale(0.4, 0.4);

	xboxMenuTexture = m_StateMgr->GetContext()->m_TextureManager->GetResource(xboxMenutextureString);
	xboxMenu.setTexture(*xboxMenuTexture);
	xboxMenu.setPosition(1050, 400);
	//xboxMenu.setPosition((windowSize.x / 100) * 53.98, (windowSize.y / 100) * 28.6);
	xboxMenu.setScale(0.4, 0.4);

	xboxWindowTexture = m_StateMgr->GetContext()->m_TextureManager->GetResource(xboxWindowtextureString);
	xboxWindow.setTexture(*xboxWindowTexture);
	xboxWindow.setPosition(1050, 430);
	//xboxWindow.setPosition((windowSize.x / 100) * 53.98, (windowSize.y / 100) * 30.6);
	xboxWindow.setScale(0.4, 0.4);

	m_StateMgr->GetContext()->m_SoundManager->PlayMusic("CreditsMusic", 10.f, true);
}

void State_Controls::OnDestroy() {
	EventManager* evMgr = m_StateMgr->GetContext()->m_EventManager;
	evMgr->RemoveCallback(StateType::Controls, "Intro_ContinueKeyboard");
	evMgr->RemoveCallback(StateType::Controls, "Intro_ContinueJoystick");

	m_StateMgr->GetContext()->m_TextureManager->ReleaseResource(xboxAtextureString);
	m_StateMgr->GetContext()->m_TextureManager->ReleaseResource(xboxBtextureString);
	m_StateMgr->GetContext()->m_TextureManager->ReleaseResource(xboxXtextureString);
	m_StateMgr->GetContext()->m_TextureManager->ReleaseResource(xboxYtextureString);
	m_StateMgr->GetContext()->m_TextureManager->ReleaseResource(xboxMenutextureString);
	m_StateMgr->GetContext()->m_TextureManager->ReleaseResource(xboxWindowtextureString);
}

void State_Controls::Update(const sf::Time& l_Time) {}

void State_Controls::Draw() {
	sf::RenderWindow* window = m_StateMgr->GetContext()->m_Wind->GetRenderWindow();

	window->draw(m_MainTitle);
	window->draw(m_GameControlsTitle);
	window->draw(m_InGameControls);
	window->draw(m_MainMenuControlsTitle);
	window->draw(m_MainMenuControls);
	window->draw(xboxA);
	window->draw(xboxA1);
	window->draw(xboxB);
	window->draw(xboxB1);
	window->draw(xboxX);
	window->draw(xboxY);
	window->draw(xboxY1);
	window->draw(xboxMenu);
	window->draw(xboxWindow);
	window->draw(m_MainMenuText);
}

void State_Controls::MainMenu(EventDetails* l_Details) {
	m_StateMgr->SwitchTo(StateType::MainMenu);
}

void State_Controls::Activate() {}

void State_Controls::Deactivate() {}