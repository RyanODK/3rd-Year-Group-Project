#include "Map.h"
#include "StateManager.h"
 
//constructor for map class
Map::Map(SharedContext* l_Context, BaseState* l_currentState) :
	m_Context(l_Context), m_DefaultTile(l_Context), m_MaxMapSize(32, 32), m_TileCount(0), 
	m_TileSetCount(0), m_MapGravity(512.f), m_LoadNextMap(false), m_CurrentState(l_currentState)
{
	m_Context->m_GameMap = this;
	//loads tile from file
	LoadTiles("Resources/tiles.cfg.txt");

	MapBuffer.loadFromFile("Code/Resources/Media/Audio/InGameSounds/Sounds/teleport.ogg");
	nextMapSound.setBuffer(MapBuffer);
	nextMapSound.setVolume(50);
}

//desctuctor for map class
Map::~Map() {
	PurgeMap();
	PurgeTileSet();
	m_Context->m_GameMap = nullptr;
}

//converting 2d coords to single number 
Tile* Map::GetTile(unsigned int l_X, unsigned int l_Y){
	auto itr = m_TileMap.find(ConvertCoords(l_X, l_Y));
	return(itr != m_TileMap.end() ? itr->second : nullptr);
}

TileInfo* Map::GetDefaultTile() { 
	return &m_DefaultTile; 
}

float Map::GetGravity() const { 
	return m_MapGravity; 
}

unsigned int Map::GetTileSize() const { 
	return Sheet::Tile_Size;
}

const sf::Vector2u& Map::GetMapSize() const { 
	return m_MaxMapSize; 
}

const sf::Vector2f& Map::GetPlayerStart() const { 
	return m_PlayerStart; 
}

void Map::CreateMap() {
	if (m_LoadNextMap) {
		if (m_MapCount < 5) {
			m_MapCount += 1;
		}
		else if (m_MapCount >= 6) {
			m_MapCount == 1;
		}
	}
	std::ofstream MapFile("Code/Maps/lol" + std::to_string(m_MapCount) + ".map");

	m_MapSize = 40 + (rand() % 60);

	MapFile << "|type|~id|x|y\n";
	MapFile << "BACKGROUND bg" + std::to_string(m_MapCount) +
		"Back bg" + std::to_string(m_MapCount) +
		"Middle bg" + std::to_string(m_MapCount) +
		"Front\n";
	MapFile << "SIZE " + std::to_string(m_MapSize) + " 35\n";
	MapFile << "GRAVITY 512\n";
	MapFile << "PLAYER 100 1300\n";

	if (m_MapCount == 1) {
		MapFile << "ENEMY Cyborg 800 1100\n";
	}
	else if(m_MapCount == 2) {
		MapFile << "ENEMY Alien 300 1300\n";
	}
	else if (m_MapCount == 3) {
		MapFile << "ENEMY Witch 300 1300\n";
	}
	else if (m_MapCount == 4) {
		MapFile << "ENEMY Crab 300 1300\n";
	}
	else if (m_MapCount == 5) {
		MapFile << "ENEMY Ghost 600 1300\n";
	}

	if (m_MapCount != 5) {
		MapFile << "NEXTMAP map" + std::to_string(m_MapCount + 1) + ".map\n";
	}
	else if(m_MapCount == 5){
		MapFile << "NEXTMAP map1.map\n";
	}

	MapFile << "|TILE|ID|x|y\n";
	MapFile << "|FLOOR|\n";

	for (int i = 0; i <= m_MapSize; i++) 
	{

		m_RandomDeadlyTile = 1 + (rand() % 9);

		if (m_RandomDeadlyTile == 2)
		{
			m_DeadlyTile = true;
		}
		else if (m_RandomDeadlyTile == 7)
		{
			m_AirTile = true;
		}

		if (m_DeadlyTile == true)
		{
			m_AirTile = false;
		}
		else if (m_AirTile == true)
		{
			m_DeadlyTile = false;
		}

		if (m_MapCount == 1) {
			if (i == m_MapSize) {
				MapFile << "TILE 16 " + std::to_string(i) + " 31 WARP\n";
			}
			else {
				MapFile << "TILE 16 " + std::to_string(i) + " 31\n";
			}
		}
		else if (m_MapCount == 2) {
			if (i == m_MapSize) {
				MapFile << "TILE 12 " + std::to_string(i) + " 31 WARP\n";
			}
			else {
				if (m_DeadlyTile == true && m_DeadlyInt < 3 && i - m_LastDeadly > 5 && i > 10)
				{
					MapFile << "TILE 14 " + std::to_string(i) + " 31\n";
					m_DeadlyInt++;
					m_Gap = (rand() % 2);
					if (m_DeadlyInt == 3 - m_Gap)
					{
						m_DeadlyTile = false;
						m_DeadlyInt = 0;
						m_LastDeadly = i;
					}
				}
				else if (m_AirTile == true && m_AirInt < 3 && i - m_LastDeadly > 5 && i > 10)
				{
					m_AirInt++;
					m_Gap = (rand() % 2);
					if (m_AirInt == 3 - m_Gap)
					{
						m_AirTile = false;
						m_AirInt = 0;
						//m_LastAir = i;
						m_LastDeadly = i;
					}
				}
				else {
					m_DeadlyTile = false;
					m_AirTile = false;
					MapFile << "TILE 12 " + std::to_string(i) + " 31\n";
				}
			}
		}
		else if (m_MapCount == 3) {
			MapFile << "TILE 16 " + std::to_string(i) + " 31\n";
			if (i == m_MapSize) {
				MapFile << "TILE 16 " + std::to_string(i) + " 31 WARP\n";
			}
			else {
				MapFile << "TILE 16 " + std::to_string(i) + " 31\n";
			}
		}
		else if (m_MapCount == 4) {
			MapFile << "TILE 16 " + std::to_string(i) + " 31\n";
			if (i == m_MapSize) {
				MapFile << "TILE 16 " + std::to_string(i) + " 31 WARP\n";
			}
			else {
				MapFile << "TILE 16 " + std::to_string(i) + " 31\n";
			}
		}
		else if (m_MapCount == 5) {
			MapFile << "TILE 16 " + std::to_string(i) + " 31\n";
			if (i == m_MapSize) {
				MapFile << "TILE 16 " + std::to_string(i) + " 31 WARP\n";
			}
			else {
				MapFile << "TILE 16 " + std::to_string(i) + " 31\n";
			}
		}
	}
}

void Map::LoadMap(const std::string& l_path) {
	std::ifstream mapFile;
	mapFile.open(l_path);

	if (!mapFile.is_open()) {
		std::cout << "! Failed loading map file: " << l_path << std::endl;
		return;
	}

	EntityManager* entityMgr = m_Context->m_EntityManager;
	std::string line;
	std::cout << "--- Loading a map: " << l_path << std::endl;

	int playerId = -1;
	while (std::getline(mapFile, line)) {
		if (line[0] == '|') { 
			continue; 
		}

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;

		if (type == "TILE") {
			int tileId = 0;
			keystream >> tileId;
			if (tileId < 0) {
				std::cout << "! Bad tile id: " << tileId << std::endl;
				continue;
			}

			auto itr = m_TileSet.find(tileId);
			if (itr == m_TileSet.end()) {
				std::cout << "! Tile id(" << tileId << ") was not found in tileset." << std::endl;
				continue;
			}
			sf::Vector2i tileCoords;
			keystream >> tileCoords.x >> tileCoords.y;
			if (tileCoords.x > m_MaxMapSize.x ||
				tileCoords.y > m_MaxMapSize.y)
			{
				std::cout << "! Tile is out of range: " << tileCoords.x << " " << tileCoords.y << std::endl;
				continue;
			}
			Tile* tile = new Tile();
			// Bind properties of a tile from a set.
			tile->m_Properties = itr->second;
			if (!m_TileMap.emplace(ConvertCoords(
				tileCoords.x, tileCoords.y), tile).second)
			{
				// Duplicate tile detected!
				std::cout << "! Duplicate tile! : " << tileCoords.x << " " << tileCoords.y << std::endl;
				delete tile;
				tile = nullptr;
				continue;
			}
			std::string warp;
			keystream >> warp;
			tile->m_Warp = false;

			if (warp == "WARP") { 
				tile->m_Warp = true;
			}
		}
		else if (type == "BACKGROUND") {
			if (m_BackgroundBack != "") { 
				continue; 
			}

			keystream >> m_BackgroundBack >> m_BackgroundMiddle >> m_BackgroundFront;

			if (!m_Context->m_TextureManager->RequireResource(m_BackgroundBack)) {
				m_BackgroundBack = "";
				continue;
			}
			if (!m_Context->m_TextureManager->RequireResource(m_BackgroundMiddle)) {
				m_BackgroundMiddle = "";
				continue;
			}
			if (!m_Context->m_TextureManager->RequireResource(m_BackgroundFront)) {
				m_BackgroundFront = "";
				continue;
			}

			sf::Texture* texture1 = m_Context->m_TextureManager->GetResource(m_BackgroundBack);
			texture1->setRepeated(true);
			sf::Texture* texture2 = m_Context->m_TextureManager->GetResource(m_BackgroundMiddle);
			texture2->setRepeated(true);
			sf::Texture* texture3 = m_Context->m_TextureManager->GetResource(m_BackgroundFront);
			texture3->setRepeated(true);
			sf::FloatRect viewSpace = m_Context->m_Wind->GetViewSpace();
			m_BackgroundSpeed = 40;

			m_Background1.setTexture(*texture1);
			//m_Background1.setTextureRect(sf::IntRect(viewSpace.left, viewSpace.top, 8, 192));
			m_Background2.setTexture(*texture2);
			//m_Background1.setTextureRect(sf::IntRect(viewSpace.left, viewSpace.top, 108, 192));
			m_Background3.setTexture(*texture3);
			//m_Background1.setTextureRect(sf::IntRect(viewSpace.left, viewSpace.top, 908, 192));

			sf::Vector2f viewSize = m_CurrentState->GetView().getSize();
			sf::Vector2u textureSize1 = texture1->getSize();
			sf::Vector2u textureSize2 = texture2->getSize();
			sf::Vector2u textureSize3 = texture3->getSize();
			//textureSize1 = sf::Vector2u(m_Background1.getLocalBounds().width, m_Background1.getLocalBounds().height);
			/*sf::Vector2u textureSize2 = sf::Vector2u(m_Background2.getLocalBounds().width, m_Background2.getLocalBounds().height);
			sf::Vector2u textureSize3 = sf::Vector2u(m_Background3.getLocalBounds().width, m_Background3.getLocalBounds().height);*/
			/*std::cout << "x: " << textureSize1.x << " y: " << textureSize1.y << 
				"x: " << textureSize2.x << " y: " << textureSize2.y << 
				"x: " << textureSize3.x << " y: " << textureSize3.y << std::endl;*/

			m_ScaleFactors.x = viewSize.x / textureSize1.x;
			m_ScaleFactors.y = viewSize.y / textureSize1.y;
			m_Background1.setScale(m_ScaleFactors);

			m_ScaleFactors.x = viewSize.x / textureSize2.x;
			m_ScaleFactors.y = viewSize.y / textureSize2.y;
			m_Background2.setScale(m_ScaleFactors);

			m_ScaleFactors.x = viewSize.x / textureSize3.x;
			m_ScaleFactors.y = viewSize.y / textureSize3.y;
			m_Background3.setScale(m_ScaleFactors);

			textureSize1 = sf::Vector2u(0, 0);
			textureSize2 = sf::Vector2u(0, 0);
			textureSize3 = sf::Vector2u(0, 0);
		}
		else if (type == "SIZE") {
			keystream >> m_MaxMapSize.x >> m_MaxMapSize.y;
		}
		else if (type == "GRAVITY") {
			keystream >> m_MapGravity;
		}
		else if (type == "DEFAULT_FRICTION") {
			keystream >> m_DefaultTile.m_Friction.x >> m_DefaultTile.m_Friction.y;
		}
		else if (type == "NEXTMAP") {
			keystream >> m_NextMap;
		}
		else if (type == "PLAYER") {
			if (playerId != -1) { 
				continue; 
			}
			// Set up the player position here.
			playerId = entityMgr->AddEntity(EntityType::Player);
			m_PlayerId = playerId;
			if (playerId < 0) { 
				continue; 
			}

			float playerX = 0; 
			float playerY = 0;

			keystream >> playerX >> playerY;
			entityMgr->Find(playerId)->SetPosition(playerX, playerY);
			m_PlayerStart = sf::Vector2f(playerX, playerY);
		}
		else if (type == "ENEMY") {
			std::string enemyName;
			keystream >> enemyName;
			int enemyId = entityMgr->AddEntity(EntityType::Enemy, enemyName);

			if (enemyId < 0) { 
				continue; 
			}

			float enemyX = 0; 
			float enemyY = 0;

			keystream >> enemyX >> enemyY;
			entityMgr->Find(enemyId)->SetPosition(enemyX, enemyY);
		}
		else {
			// Something else.
			std::cout << "! Unknown type \"" << type << "\"." << std::endl;
		}
	}
	mapFile.close();
	std::cout << "--- Map Loaded! ---" << std::endl;
}

void Map::LoadNext() {
	m_LoadNextMap = true;
}

void Map::LoadTiles(const std::string& l_path) {
	std::ifstream tileSetFile;
	tileSetFile.open("Code/Resources/tiles.cfg.txt");

	if (!tileSetFile.is_open()) {
		std::cout << "! Failed loading tile set file: " << l_path << std::endl;
		return;
	}

	std::string line;

	while (std::getline(tileSetFile, line)) {
		if (line[0] == '|') { 
			continue; 
		}

		std::stringstream keystream(line);
		int tileId;
		keystream >> tileId;
		if (tileId < 0) {
			continue; 
		}

		TileInfo* tile = new TileInfo(m_Context, "TileSheet", tileId);
		keystream >> tile->m_Name >> tile->m_Friction.x >> tile->m_Friction.y >> tile->m_Deadly;

		if (!m_TileSet.emplace(tileId, tile).second) {
			// Duplicate tile detected!
			std::cout << "! Duplicate tile type: " << tile->m_Name << std::endl;
			delete tile;
			tile = nullptr;
		}
	}
	tileSetFile.close();
}

void Map::Update(float l_DeltaTime) {
	if (m_LoadNextMap) {
		nextMapSound.play();
		PurgeMap();
		m_LoadNextMap = false;

		if (m_NextMap != "") {
			LoadMap("Code/Maps/" + m_NextMap);
		}
		else {
			std::cout << "Cant load map" << std::endl;
			m_CurrentState->GetStateManager()->SwitchTo(StateType::GameOver);
		}

		//m_NextMap = "";
	}

	sf::FloatRect viewSpace = m_Context->m_Wind->GetViewSpace();
	m_Background1.setPosition(viewSpace.left, viewSpace.top);
	m_Background2.setPosition(viewSpace.left, viewSpace.top);
	m_Background3.setPosition(viewSpace.left, viewSpace.top);

	if (m_BackgroundX < viewSpace.width) {
		m_BackgroundX += m_BackgroundSpeed * l_DeltaTime;
	}
	else {
		// this is the reason the background will do that weird resetting thing 
		// 
		// potentially find a different way 
		// than just setting the x straight back to 0 when it hits the full width
		m_BackgroundX = 0;
	}

	m_Background1.setTextureRect(sf::IntRect(
		m_BackgroundX,
		m_Background1.getTextureRect().top,
		m_Background1.getTextureRect().width,
		m_Background1.getTextureRect().height));

	m_Background2.setTextureRect(sf::IntRect(
		m_BackgroundX,
		m_Background2.getTextureRect().top,
		m_Background2.getTextureRect().width,
		m_Background2.getTextureRect().height));

	m_Background3.setTextureRect(sf::IntRect(
		m_BackgroundX,
		m_Background3.getTextureRect().top,
		m_Background3.getTextureRect().width,
		m_Background3.getTextureRect().height));
}

void Map::Draw() {
	sf::RenderWindow* l_Wind = m_Context->m_Wind->GetRenderWindow();
	sf::FloatRect viewSpace = m_Context->m_Wind->GetViewSpace();
	l_Wind->draw(m_Background1);
	l_Wind->draw(m_Background2);
	l_Wind->draw(m_Background3);

	sf::Vector2i tileBegin(floor(viewSpace.left / Sheet::Tile_Size), 
						floor(viewSpace.top / Sheet::Tile_Size));

	sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size),
					ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size));

	unsigned int count = 0;
	for (int x = tileBegin.x; x <= tileEnd.x; ++x) {
		for (int y = tileBegin.y; y <= tileEnd.y; ++y) {
			
			if (x < 0 || y < 0) { 
				continue; 
			}

			Tile* tile = GetTile(x, y);
			
			if (!tile) { 
				continue; 
			}

			sf::Sprite& sprite = tile->m_Properties->m_Sprite;
			//sprite.setPosition(((resolution.x / 100) * 0.1) * x * Sheet::Tile_Size, ((resolution.y / 100) * 0.1) * y * Sheet::Tile_Size);
			sprite.setPosition(x * Sheet::Tile_Size, y * Sheet::Tile_Size);
			//sprite.setScale((resolution.x / 100) * 0.1, (resolution.y / 100) * 0.1);
			l_Wind->draw(sprite);
			++count;

			// Debug.
			if (m_Context->m_DebugOverlay.Debug()) {
				if (tile->m_Properties->m_Deadly || tile->m_Warp) {
					sf::RectangleShape* tileMarker = new sf::RectangleShape(
						sf::Vector2f(Sheet::Tile_Size, Sheet::Tile_Size));
					tileMarker->setPosition(x * Sheet::Tile_Size, y * Sheet::Tile_Size);
					if (tile->m_Properties->m_Deadly) {
						tileMarker->setFillColor(sf::Color(255, 0, 0, 100));
					}
					else if (tile->m_Warp) {
						tileMarker->setFillColor(sf::Color(0, 255, 0, 150));
					}
					m_Context->m_DebugOverlay.Add(tileMarker);
				}
			}
			// End debug.
		}
	}
}

//converting coords from 2d to single number. Max size of map must be defined.
unsigned int Map::ConvertCoords(unsigned int l_X, unsigned int l_Y)
{
	return (l_X * m_MaxMapSize.x) + l_Y; // Row-major.
}

void Map::PurgeMap() {
	m_TileCount = 0;
	for (auto& itr : m_TileMap) {
		delete itr.second;
	}
	m_TileMap.clear();
	m_Context->m_EntityManager->Purge();

	if (m_BackgroundBack == "") { 
		return; 
	}
	if (m_BackgroundMiddle == "") {
		return;
	}
	if (m_BackgroundFront == "") {
		return;
	}

	m_Context->m_TextureManager->ReleaseResource(m_BackgroundBack);
	m_BackgroundBack = "";

	m_Context->m_TextureManager->ReleaseResource(m_BackgroundMiddle);
	m_BackgroundMiddle = "";

	m_Context->m_TextureManager->ReleaseResource(m_BackgroundFront);
	m_BackgroundFront = "";
}

void Map::PurgeTileSet() {
	while (m_TileSet.begin() != m_TileSet.end()) {
		delete m_TileSet.begin()->second;
		m_TileSet.erase(m_TileSet.begin());
	}
	m_TileSetCount = 0;
}