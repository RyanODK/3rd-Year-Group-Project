#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>
#include <array>
#include <iostream>
#include <cstdlib>
#include "Utilities.h"
#include "SharedContext.h"
#include "BaseState.h"

//tile sheet info
enum Sheet { Tile_Size = 43, Sheet_Width = 258, Sheet_Height = 258 };

//type alias for ids
using TileID = unsigned int;

//Tile information structure
struct TileInfo {
	//information for tile
	TileInfo(SharedContext* l_Context, const std::string& l_Texture = "", TileID l_Id = 0) : m_Context(l_Context), m_Id(0), m_Deadly(false)
	{
		//texture the tile is using
		TextureManager* tmgr = l_Context->m_TextureManager;
		if (l_Texture == "")
		{ 
			m_Id = l_Id; 
			return; 
		}
		if (!tmgr->RequireResource(l_Texture))
		{ 
			return; 
		}
		m_Texture = l_Texture;
		m_Id = l_Id;
		//sprite points to tile sheet texture
		m_Sprite.setTexture(*tmgr->GetResource(m_Texture));
		//crops tile sheet to the sprite
		sf::IntRect tileBoundaries(m_Id % (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size,
			m_Id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
			Sheet::Tile_Size, Sheet::Tile_Size);
		//sets text rect for sprite to the cropped boundaries
		m_Sprite.setTextureRect(tileBoundaries);
	}

	~TileInfo() 
	{
		if (m_Texture == "") 
		{
			return;
		}
		m_Context->m_TextureManager->ReleaseResource(m_Texture);
	}

	sf::Sprite m_Sprite;

	TileID m_Id;
	std::string m_Name;
	sf::Vector2f m_Friction;
	bool m_Deadly;

	SharedContext* m_Context;
	std::string m_Texture;
};

//destructor for tileinfo
struct Tile {
	TileInfo* m_Properties;
	bool m_Warp; // Is the tile a warp. tiles that warps player to next dimension
	bool m_Solid;
};

//tile map is un ordered map container, holds pointers to tile objects 
using TileMap = std::unordered_map<TileID, Tile*>;
//tile set is for the container of all types of tiles, tied to tile id
using TileSet = std::unordered_map<TileID, TileInfo*>;

class Map {
public:
	Map(SharedContext* l_context, BaseState* l_currentState);
	~Map();

	Tile* GetTile(unsigned int l_X, unsigned int l_Y);

	TileInfo* GetDefaultTile();

	float GetGravity() const;
	unsigned int GetTileSize() const;
	const sf::Vector2u& GetMapSize() const;
	const sf::Vector2f& GetPlayerStart() const;

	void CreateMap();
	void LoadMap(const std::string& l_Path);
	void LoadNext(); 

	void Update(float l_deltaTime);
	void Draw();

private:
	// Method for converting 2D coordinates to 1D ints.
	unsigned int ConvertCoords(unsigned int l_X, unsigned int l_Y);

	void LoadTiles(const std::string& l_Path);

	void PurgeMap();
	void PurgeTileSet();

	std::string m_BackgroundBack;
	std::string m_BackgroundMiddle;
	std::string m_BackgroundFront;
	sf::Sprite m_Background1;
	sf::Sprite m_Background2;
	sf::Sprite m_Background3;
	sf::Vector2f m_ScaleFactors;
	float m_BackgroundSpeed;
	float m_BackgroundX;

	TileSet m_TileSet;
	TileMap m_TileMap;

	TileInfo m_DefaultTile;

	sf::Vector2u m_MaxMapSize;
	sf::Vector2f m_PlayerStart;

	float m_MapGravity;
	int m_PlayerId;
	int m_MapCount = 1;
	int m_MapSize;
	int m_RandomDeadlyTile;
	
	int m_DeadlyInt = 0;
	int m_LastDeadly = 0;
	int m_AirInt = 0;
	int m_LastAir = 0;
	int m_Gap = 0;
	int m_Floating;

	bool m_DeadlyTile;
	bool m_AirTile;
	bool m_NextGap;

	int c = 0;
	int d = 0;
	int e = 0;
	int z = 0;

	int m_RandEnemy = 0;
	int m_LastEnemy = 0;

	bool m_HasNext;
	int m_LastTile = 0;

	bool m_HasNext27;
	int m_LastTile27 = 0;

	int map1Layer31[100];
	int map1Layer29[100];
	int map1Layer27[100];

	int map2Layer31[100];
	int map2Layer29[100];
	int map2Layer27[100];

	int map3Layer31[100];
	int map3Layer29[100];
	int map3Layer27[100];

	int map4Layer31[100];
	int map4Layer29[100];
	int map4Layer27[100];

	int map5Layer31[100];
	int map5Layer29[100];
	int map5Layer27[100];

	bool m_LoadNextMap;
	std::string m_NextMap;
	unsigned int m_TileCount;
	unsigned int m_TileSetCount;

	BaseState* m_CurrentState;
	SharedContext* m_Context;

	sf::SoundBuffer MapBuffer;
	sf::Sound nextMapSound;
};