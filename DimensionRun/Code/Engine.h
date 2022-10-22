#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"

using namespace sf;

class Engine {
public:
	Engine();

	void run();

private:
	TextureHolder th;

	bool m_Playing = false;

	Player m_player;
	Enemy m_enemy;
	Background m_background;

	const float gravity = 0.5;

	RenderWindow m_Window;
	Vector2f m_resolution;

	Time m_GameTimeTotal;

	void input();
	void update(float dtAsSeconds);
	void draw();
};
#endif