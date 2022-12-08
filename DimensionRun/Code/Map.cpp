#include "Map.h"
#include "StateManager.h"
 
//constructor for map class
Map::Map(SharedContext* l_Context) : 
	m_Context(l_Context), m_DefaultTile(l_Context), m_MaxMapSize(32, 32), m_PlayerId(-1)
{
	m_Context->m_GameMap = this;
	//loads tile from file
	LoadTiles("Resources/tiles.cfg.txt");
}

//desctuctor for map class
Map::~Map() {
	PurgeMap();
	PurgeTileSet();
	m_Context->m_GameMap = nullptr;
}

//converting 2d coords to single number 
Tile* Map::GetTile(unsigned int l_X, unsigned int l_Y, unsigned int l_Layer){
	if (l_X < 0 || l_Y < 0 || l_X >= m_MaxMapSize.x ||
		l_Y >= m_MaxMapSize.y || l_Layer < 0 ||
		l_Layer >= Sheet::Num_Layers)
	{
		return nullptr;
	}
	auto itr = m_TileMap.find(ConvertCoords(l_X, l_Y, l_Layer));
	if (itr == m_TileMap.end()) { 
		return nullptr; 
	}
	return itr->second;
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

int Map::GetPlayerId() const { 
	return m_PlayerId; 
}

void Map::LoadMap(const std::string& l_path) {
	std::ifstream mapFile;
	mapFile.open(l_path);

	if (!mapFile.is_open()) {
		std::cout << "! Failed loading map file: " << l_path << std::endl;
		return;
	}

	std::string line;
	std::cout << "--- Loading a map: " << l_path << std::endl;

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
			unsigned int tileLayer = 0;
			unsigned int tileSolidity = 0;
			keystream >> tileCoords.x >> tileCoords.y >> tileLayer >> tileSolidity;
			if (tileCoords.x > m_MaxMapSize.x ||
				tileCoords.y > m_MaxMapSize.y ||
				tileLayer >= Sheet::Num_Layers)
			{
				std::cout << "! Tile is out of range: " << tileCoords.x << " " << tileCoords.y << std::endl;
				continue;
			}
			Tile* tile = new Tile();
			// Bind properties of a tile from a set.
			tile->m_Properties = itr->second;
			tile->m_Solid = (bool)tileSolidity;
			if (!m_TileMap.emplace(ConvertCoords(
				tileCoords.x, tileCoords.y, tileLayer), tile).second)
			{
				// Duplicate tile detected!
				std::cout << "! Duplicate tile! : " << tileCoords.x << " " << tileCoords.y << std::endl;
				delete tile;
				continue;
			}
			std::string warp;
			keystream >> warp;
			tile->m_Warp = false;

			if (warp == "WARP") { 
				tile->m_Warp = true;
			}
		}
		//else if (type == "BACKGROUND") {
		//	if (m_BackgroundTexture1 != "") {
		//		continue; 
		//	}

		//	keystream >> m_BackgroundTexture1;
		//	if (!m_Context->m_TextureManager->RequireResource(m_BackgroundTexture1))
		//	{
		//		m_BackgroundTexture1 = "";
		//		continue;
		//	}

		//	sf::Texture* texture = m_Context->m_TextureManager->GetResource(m_BackgroundTexture1);
		//	m_Background1.setTexture(*texture);

		//	sf::Vector2f viewSize;
		//	viewSize.x = sf::VideoMode::getDesktopMode().width;
		//	viewSize.y = sf::VideoMode::getDesktopMode().height;
		//	sf::Vector2u textureSize = texture->getSize();
		//	sf::Vector2f scaleFactors;
		//	scaleFactors.x = viewSize.x / textureSize.x;
		//	scaleFactors.y = viewSize.y / textureSize.y;
		//	m_Background1.setScale(scaleFactors);
		//}
		//else if (type == "BACKGROUND2") {
		//	if (m_BackgroundTexture2 != "") {
		//		continue;
		//	}

		//	keystream >> m_BackgroundTexture2;
		//	if (!m_Context->m_TextureManager->RequireResource(m_BackgroundTexture2))
		//	{
		//		m_BackgroundTexture2 = "";
		//		continue;
		//	}

		//	sf::Texture* texture = m_Context->m_TextureManager->GetResource(m_BackgroundTexture2);
		//	m_Background2.setTexture(*texture);

		//	//sf::Vector2f viewSize = m_CurrentState->GetView().getSize();
		//	sf::Vector2f viewSize;
		//	viewSize.x = sf::VideoMode::getDesktopMode().width;
		//	viewSize.y = sf::VideoMode::getDesktopMode().height;
		//	sf::Vector2u textureSize = texture->getSize();
		//	sf::Vector2f scaleFactors;
		//	scaleFactors.x = viewSize.x / textureSize.x;
		//	scaleFactors.y = viewSize.y / textureSize.y;
		//	m_Background2.setScale(scaleFactors);
		//}
		//else if (type == "BACKGROUND3") {
		//	if (m_BackgroundTexture3 != "") {
		//		continue;
		//	}

		//	keystream >> m_BackgroundTexture3;
		//	if (!m_Context->m_TextureManager->RequireResource(m_BackgroundTexture3))
		//	{
		//		m_BackgroundTexture3 = "";
		//		continue;
		//	}

		//	sf::Texture* texture = m_Context->m_TextureManager->GetResource(m_BackgroundTexture3);
		//	m_Background3.setTexture(*texture);

		//	//sf::Vector2f viewSize = m_CurrentState->GetView().getSize();
		//	sf::Vector2f viewSize;
		//	viewSize.x = sf::VideoMode::getDesktopMode().width;
		//	viewSize.y = sf::VideoMode::getDesktopMode().height;
		//	sf::Vector2u textureSize = texture->getSize();
		//	sf::Vector2f scaleFactors;
		//	scaleFactors.x = viewSize.x / textureSize.x;
		//	scaleFactors.y = viewSize.y / textureSize.y;
		//	m_Background3.setScale(scaleFactors);
		//}
		else if (type == "SIZE") {
			keystream >> m_MaxMapSize.x >> m_MaxMapSize.y;
		}
		else if (type == "DEFAULT_FRICTION") {
			keystream >> m_DefaultTile.m_Friction.x >> m_DefaultTile.m_Friction.y;
		}
		else if (type == "NEXTMAP") {
			keystream >> m_NextMap;
		}
		else if (type == "ENTITY") {
			// Set up entity here.
			std::string name;
			keystream >> name;
			if (name == "Player" && m_PlayerId != -1) { 
				continue; 
			}
			int entityId = m_Context->m_EntityManager->AddEntity(name);

			if (entityId < 0) { 
				continue; 
			}
			if (name == "Player") {
				m_PlayerId = entityId; 
			}

			C_Base* position = m_Context->m_EntityManager->
				GetComponent<C_Position>(entityId, Component::Position);
			if (position) { 
				keystream >> *position; 
			} 
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
	/*if (m_LoadNextMap) {
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
	m_Background1.setPosition(viewSpace.left, viewSpace.top);
	m_Background2.setPosition(viewSpace.left, viewSpace.top);
	m_Background3.setPosition(viewSpace.left, viewSpace.top);*/
}

void Map::Draw(unsigned int l_layer) {
	if (l_layer >= Sheet::Num_Layers) { 
		return; 
	}

	sf::RenderWindow* l_Wind = m_Context->m_Wind->GetRenderWindow();
	/*l_Wind->draw(m_Background1);
	l_Wind->draw(m_Background2);
	l_Wind->draw(m_Background3);*/
	sf::FloatRect viewSpace = m_Context->m_Wind->GetViewSpace();

	sf::Vector2i tileBegin(floor(viewSpace.left / Sheet::Tile_Size), 
						floor(viewSpace.top / Sheet::Tile_Size));

	sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size),
					ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size));

	unsigned int count = 0;
	for (int x = tileBegin.x; x <= tileEnd.x; ++x) {
		for (int y = tileBegin.y; y <= tileEnd.y; ++y) {
			Tile* tile = GetTile(x, y, l_layer);
			
			if (!tile) { 
				continue; 
			}

			sf::Sprite& sprite = tile->m_Properties->m_Sprite;
			sprite.setPosition(x * Sheet::Tile_Size, y * Sheet::Tile_Size);
			l_Wind->draw(sprite);
			++count;
		}
	}
}

//converting coords from 2d to single number. Max size of map must be defined.
unsigned int Map::ConvertCoords(unsigned int l_X, unsigned int l_Y, unsigned int l_Layer)const
{
	return ((l_Layer * m_MaxMapSize.y + l_Y) * m_MaxMapSize.x + l_X);
}

void Map::PurgeMap() {
	//m_TileCount = 0;

	//for (auto& itr : m_TileMap) {
	//	delete itr.second;
	//	m_TileMap.erase(m_TileMap.begin());
	//}

	//m_TileMap.clear();
	//m_Context->m_EntityManager->Purge();

	//if (m_BackgroundTexture1 == "") {
	//	return;
	//}
	//if (m_BackgroundTexture2 == "") {
	//	return;
	//}
	//if (m_BackgroundTexture3 == "") {
	//	return;
	//}

	//m_Context->m_TextureManager->ReleaseResource(m_BackgroundTexture1);
	//m_Context->m_TextureManager->ReleaseResource(m_BackgroundTexture2);
	//m_Context->m_TextureManager->ReleaseResource(m_BackgroundTexture3);
	//m_BackgroundTexture1 = "";
	//m_BackgroundTexture2 = "";
	//m_BackgroundTexture3 = "";

	while (m_TileMap.begin() != m_TileMap.end()) {
		delete m_TileMap.begin()->second;
		m_TileMap.erase(m_TileMap.begin());
	}
	m_TileCount = 0;
	m_Context->m_EntityManager->Purge();
}

void Map::PurgeTileSet() {
	while (m_TileSet.begin() != m_TileSet.end()) {
		delete m_TileSet.begin()->second;
		m_TileSet.erase(m_TileSet.begin());
	}
	m_TileSetCount = 0;
}