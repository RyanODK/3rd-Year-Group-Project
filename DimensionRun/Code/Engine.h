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
	Engine(); // default constructor to set game resolution and ground height

	void run(); // runs game

private:
	TextureHolder th; // TextureHolder class to hold textures

	//bool m_spawned = false;
	bool m_Playing = false; // check if game is playing

	Player m_player; // player class
	Enemy m_enemy; // enemy class
	Background m_background; // background class

	const float gravity = 550; // sets gravity 
	int groundHeight; // groundheight

	RenderWindow m_Window; // render window to display game
	Vector2f m_resolution; // stores resolution for future use

	Time m_GameTimeTotal; // gets total game time of current opened window

	void input(); // input function to handle inputs from user
	void update(float dtAsSeconds); // update function to update game 
	void draw(); // draw function to draw sprites on screen
};
#endif