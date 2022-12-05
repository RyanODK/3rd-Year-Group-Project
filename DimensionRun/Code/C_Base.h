#pragma once
#include <iostream>
#include <sstream>
#include "ECS_Types.h"

class C_Base {
public:
    C_Base(const Component& l_Type) : m_Type(l_Type) {}
    virtual ~C_Base() {}

    Component GetType() { 
        return m_Type;
    }

    friend std::stringstream& operator >>(
        std::stringstream& l_Stream, C_Base& b)
    {
        b.ReadIn(l_Stream);
        return l_Stream;
    }

    virtual void ReadIn(std::stringstream& l_Stream) = 0;
protected:
    Component m_Type;
};
