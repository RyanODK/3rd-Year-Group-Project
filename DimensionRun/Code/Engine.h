#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "GroundObstacle.h"
#include "FloatingObstacle.h"
#include "Player.h"
#include "SmallEnemy.h"
#include "MediumEnemy.h"
#include "LargeEnemy.h"
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
	FloatingObstacle m_floatingObstacle;
	GroundObstacle m_groundObstacle;
	Background m_background; // background class
	Background m_mainMenuBackground;
	SoundManager m_SoundManager; // soundmanager class

	/* Small Enemies */
	SmallEnemy m_SmallEnemy1;
	SmallEnemy m_SmallEnemy2;
	SmallEnemy m_SmallEnemy3;
	SmallEnemy m_SmallEnemy4;
	SmallEnemy m_SmallEnemy5;
	SmallEnemy m_Portal;

	/* Medium Enemies */
	MediumEnemy m_MediumEnemy1;
	MediumEnemy m_MediumEnemy2;
	MediumEnemy m_MediumEnemy3;

	/* Large Enemies */
	LargeEnemy m_LargeEnemy1;
	LargeEnemy m_LargeEnemy2;
	LargeEnemy m_LargeEnemy3;

	const float gravity = 450; // sets gravity 
	int groundHeight; // groundheight

	RenderWindow m_Window; // render window to display game
	Vector2f m_resolution; // stores resolution for future use

	Time m_GameTimeTotal; // gets total game time of current opened window

	float resetTime = 0.0f; // checks which background to draw
	int backgroundType; // checks which background is currently playing

	// checks when player can jump, slide and laser
	float jumpInterval = 0.0f; 
	float slideInterval = 0.0f;
	float laserInterval = 0.0f;
	bool canJump = true;
	bool canSlide = true;
	bool canLaser = true;

	float distanceRan = 0.0f; // track distance
	float bestDistance = 0.0f; // keeps best time
	float coinCount = 0.0f;
	Text distanceText; 
	Text bestDistanceText;
	Text coinCountText;

	void input(); // input function to handle inputs from user
	void update(float dtAsSeconds); // update function to update game 
	void draw(); // draw function to draw sprites on screen
	void checkCol(Player& player);
};
#endif