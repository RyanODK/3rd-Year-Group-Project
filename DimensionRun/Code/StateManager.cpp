#include "StateManager.h"
#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Game.h"
#include "State_GameOver.h"
#include "State_Paused.h"
#include "State_Credits.h"

StateManager::StateManager(SharedContext* l_Shared) : m_Shared(l_Shared) {
    RegisterState<State_Intro>(StateType::Intro);
	RegisterState<State_MainMenu>(StateType::MainMenu);
	RegisterState<State_Game>(StateType::Game);
	RegisterState<State_Paused>(StateType::Paused);
    /*RegisterState<State_GameOver>(StateType::GameOver);
    RegisterState<State_Credits>(StateType::Credits);*/
}

StateManager::~StateManager() {
	for (auto& itr : m_States) {
		itr.second->OnDestroy();
		delete itr.second;
	}
}

void StateManager::Draw() {
    if (m_States.empty()) { 
        return; 
    }

    if (m_States.back().second->IsTransparent() && m_States.size() > 1)
    {
        auto itr = m_States.end();
        while (itr != m_States.begin()) {
            if (itr != m_States.end()) {
                if (!itr->second->IsTransparent()) {
                    break;
                }
            }
            --itr;
        }
        for (; itr != m_States.end(); ++itr) {
            m_Shared->m_Wind->GetRenderWindow()->setView(itr->second->GetView());
            itr->second->Draw();
        }
    }
    else {
        m_States.back().second->Draw();
    }
}

void StateManager::Update(const sf::Time& l_time) {
    if (m_States.empty()) { return; }
    if (m_States.back().second->IsTranscendent() && m_States.size() > 1)
    {
        auto itr = m_States.end();
        while (itr != m_States.begin()) {
            if (itr != m_States.end()) {
                if (!itr->second->IsTranscendent()) {
                    break;
                }
            }
            --itr;
        }
        for (; itr != m_States.end(); ++itr) {
            itr->second->Update(l_time);
        }
    }
    else {
        m_States.back().second->Update(l_time);
    }
}

SharedContext* StateManager::GetContext() { 
    return m_Shared; 
}

bool StateManager::HasState(const StateType& l_type) {
    for (auto itr = m_States.begin();
        itr != m_States.end(); ++itr)
    {
        if (itr->first == l_type) {
            auto removed = std::find(m_ToRemove.begin(),
                m_ToRemove.end(), l_type);
            if (removed == m_ToRemove.end()) { return true; }
            return false;
        }
    }
    return false;
}

void StateManager::Remove(const StateType& l_type) {
    m_ToRemove.emplace_back(l_type);
}

void StateManager::ProcessRequests() {
    while (m_ToRemove.begin() != m_ToRemove.end()) {
        RemoveState(*m_ToRemove.begin());
        m_ToRemove.erase(m_ToRemove.begin());
    }
}

void StateManager::SwitchTo(const StateType& l_type) {
    m_Shared->m_EventManager->SetCurrentState(l_type);
    m_Shared->m_GuiManager->SetCurrentState(l_type);
    m_Shared->m_SoundManager->ChangeState(l_type);
    for (auto itr = m_States.begin();
        itr != m_States.end(); ++itr)
    {
        if (itr->first == l_type) {
            m_States.back().second->Deactivate();
            StateType tmp_type = itr->first;
            BaseState* tmp_state = itr->second;
            m_States.erase(itr);
            m_States.emplace_back(tmp_type, tmp_state);
            tmp_state->Activate();
            m_Shared->m_Wind->GetRenderWindow()->setView(tmp_state->GetView());
            return;
        }
    }

    // State with l_type wasn't found.
    if (!m_States.empty()) { 
        m_States.back().second->Deactivate(); 
    }
    CreateState(l_type);
    m_States.back().second->Activate();
    m_Shared->m_Wind->GetRenderWindow()->setView(m_States.back().second->GetView());
}

void StateManager::CreateState(const StateType& l_type) {
    auto newState = m_StateFactory.find(l_type);
    if (newState == m_StateFactory.end()) { 
        return; 
    }
    BaseState* state = newState->second();
    state->m_View = m_Shared->m_Wind->GetRenderWindow()->getDefaultView();
    m_States.emplace_back(l_type, state);
    state->OnCreate();
}

void StateManager::RemoveState(const StateType& l_type) {
    for (auto itr = m_States.begin(); itr != m_States.end(); ++itr)
    {
        if (itr->first == l_type) {
            itr->second->OnDestroy();
            delete itr->second;
            m_States.erase(itr);
            m_Shared->m_SoundManager->RemoveState(l_type);
            return;
        }
    }
}