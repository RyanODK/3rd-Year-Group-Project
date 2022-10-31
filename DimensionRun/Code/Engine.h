#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"
#include "SmallEnemy.h"
#include "Background.h"
#include "SoundManager.h"

using namespace sf;

class Engine {
public:
	Engine(); // default constructor to set game resolution and ground height

	void run(); // runs game

	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING, MAIN_MENU }; // all possible states of game
	State state = State::MAIN_MENU; // default state to Main Menu

private:
	TextureHolder th; // TextureHolder class to hold textures

	Font font; // font for game
	Text mainMenuText; // main menu text
	Text pauseMenuText; // pause menu text

	//bool m_spawned = false;

	Player m_player; // player class
	Background m_background; // background class
	Background m_mainMenuBackground;
	SoundManager m_SoundManager; // soundmanager class

	/* Small Enemies */
	SmallEnemy m_SmallEnemy1;
	SmallEnemy m_SmallEnemy2;
	SmallEnemy m_SmallEnemy3;

	const float gravity = 900; // sets gravity 
	int groundHeight; // groundheight

	RenderWindow m_Window; // render window to display game
	Vector2f m_resolution; // stores resolution for future use

	Time m_GameTimeTotal; // gets total game time of current opened window

	float distanceRan = 0.0f; // track distance
	Text distanceText;

	void input(); // input function to handle inputs from user
	void update(float dtAsSeconds); // update function to update game 
	void draw(); // draw function to draw sprites on screen
};
#endif