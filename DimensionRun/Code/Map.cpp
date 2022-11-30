#include "Map.h"
#include "StateManager.h"

//constructor for map class
Map::Map(SharedContext* l_Context, BaseState* l_CurrentState) : 
	m_Context(l_Context), m_DefaultTile(l_Context), m_MaxMapSize(32, 32), m_PlayerId(-1),
	m_TileCount(0), m_TileSetCount(0), m_MapGravity(512.f), 
	m_LoadNextMap(false), m_CurrentState(l_CurrentState)
{
	m_Context->m_GameMap = this;
	//loads tile from file
	LoadTiles("tiles.cfg");
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

void Map::LoadMap(const std::string& l_path) {
	std::ifstream mapFile;
	mapFile.open(Utils::GetWorkingDirectory() + l_path);

	if (!mapFile.is_open()) {
		std::cout << "! Failed loading map file: " << l_path << std::endl;
		return;
	}

	std::string line;
	std::cout << "--- Loading a map: " << l_path << std::endl;

	EntityManager* entityMgr = m_Context->m_EntityManager;
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
				tileCoords.y > m_MaxMapSize.y) {
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
			if (m_BackgroundTexture != "") { 
				continue; 
			}

			keystream >> m_BackgroundTexture;
			if (!m_Context->m_TextureManager->RequireResource(m_BackgroundTexture))
			{
				m_BackgroundTexture = "";
				continue;
			}

			sf::Texture* texture = m_Context->m_TextureManager->GetResource(m_BackgroundTexture);
			m_Background.setTexture(*texture);

			sf::Vector2f viewSize = m_CurrentState->GetView().getSize();
			sf::Vector2u textureSize = texture->getSize();
			sf::Vector2f scaleFactors;
			scaleFactors.x = viewSize.x / textureSize.x;
			scaleFactors.y = viewSize.y / textureSize.y;
			m_Background.setScale(scaleFactors);
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
		//else if (type == "ENTITY") {
		//	// Set up entity here.
		//	std::string name;
		//	keystream >> name;
		//	if (name == "Player" && m_playerId != -1) { continue; }
		//	int entityId = m_context->m_EntityManager->AddEntity(name);
		//	if (entityId < 0) { continue; }
		//	if (name == "Player") { m_playerId = entityId; }
		//	C_Base* position = m_context->m_entityManager->
		//		GetComponent<C_Position>(entityId, Component::Position);
		//	if (position) { keystream >> *position; }
		//}
		else if(type == "Player") {
			if (playerId != -1) {
				continue;
			}

			// set up player position here
			playerId = entityMgr->Add(EntityType::Player);

			if (playerId < 0) {
				continue;
			}

			float playerX = 0;
			float playerY = 0;
			keystream >> playerX >> playerY;

			entityMgr->Find(playerId)->SetPosition(playerX, playerY);
			m_PlayerStart = sf::Vector2f(playerX, playerY);
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
	tileSetFile.open(Utils::GetWorkingDirectory() + l_path);

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
			//tile = nullptr;
		}
	}
	tileSetFile.close();
}

void Map::Update(float l_DeltaTime) {
	if (m_LoadNextMap) {
		PurgeMap();
		m_LoadNextMap = false;

		if (m_NextMap != "") {
			LoadMap("Code/Maps/" + m_NextMap);
		}
		else {
			m_CurrentState->GetStateManager()->SwitchTo(StateType::GameOver);
		}

		m_NextMap = "";
	}

	sf::FloatRect viewSpace = m_Context->m_Wind->GetViewSpace();
	m_Background.setPosition(viewSpace.left, viewSpace.top);
}

void Map::Draw() {
	sf::RenderWindow* l_Wind = m_Context->m_Wind->GetRenderWindow();
	l_Wind->draw(m_Background);
	sf::FloatRect viewSpace = m_Context->m_Wind->GetViewSpace();

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
			sprite.setPosition(x * Sheet::Tile_Size,
				y * Sheet::Tile_Size);
			l_Wind->draw(sprite);
			++count;
		}
	}
}

//converting coords from 2d to single number. Max size of map must be defined.
unsigned int Map::ConvertCoords(const unsigned int l_X, const unsigned int l_Y)
{
	return (l_X * m_MaxMapSize.x) + l_Y; // row-major
}

void Map::PurgeMap() {
	m_TileCount = 0;

	for (auto& itr : m_TileMap) {
		delete itr.second;
	}

	m_TileMap.clear();
	m_Context->m_EntityManager->Purge();

	if (m_BackgroundTexture == "") {
		return;
	}

	m_Context->m_TextureManager->ReleaseResource(m_BackgroundTexture);
	m_BackgroundTexture = "";
}

void Map::PurgeTileSet() {
	for (auto& itr : m_TileSet) {
		delete itr.second;
	}

	m_TileSet.clear();
	m_TileSetCount = 0;
}