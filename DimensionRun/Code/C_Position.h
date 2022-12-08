#pragma once
#include "C_Base.h"
#include <SFML/System/Vector2.hpp>

class C_Position : public C_Base {
public:
    C_Position() : C_Base(Component::Position), m_Elevation(0) {}
    ~C_Position() {}

    void ReadIn(std::stringstream& l_Stream) {
        l_Stream >> m_Position.x >> m_Position.y >> m_Elevation;
    }

    const sf::Vector2f& GetPosition() {
        return m_Position; 
    }

    const sf::Vector2f& GetOldPosition() { 
        return m_PositionOld; 
    }

    unsigned int GetElevation() {
        return m_Elevation; 
    }

    void SetPosition(float l_X, float l_Y) {
        m_PositionOld = m_Position;
        m_Position = sf::Vector2f(l_X, l_Y);
    }

    void SetPosition(const sf::Vector2f& l_Vec) {
        m_PositionOld = m_Position;
        m_Position = l_Vec;
    }

    void SetElevation(unsigned int l_Elevation) {
        m_Elevation = l_Elevation;
    }

    void MoveBy(float l_X, float l_Y) {
        m_PositionOld = m_Position;
        m_Position += sf::Vector2f(l_X, l_Y);
    }

    void MoveBy(const sf::Vector2f& l_Vec) {
        m_PositionOld = m_Position;
        m_Position += l_Vec;
    }

private:
    sf::Vector2f m_Position;
    sf::Vector2f m_PositionOld;
    unsigned int m_Elevation;
};
