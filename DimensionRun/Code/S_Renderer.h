#pragma once
#include "S_Base.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Window.h"

class S_Renderer : public S_Base {
public:
	S_Renderer(SystemManager* l_systemMgr);
	~S_Renderer();

	void Update(float l_dT);
	void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
	void Notify(const Message& l_message);
	void Render(Window* l_wind, unsigned int l_layer);
private:
	void SortDrawables();
};
