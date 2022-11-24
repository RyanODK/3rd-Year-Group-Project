#include "Floor.h"

void Floor::createFloor(sf::VertexArray& rVA, sf::Vector2f resolution) {
	const int TILE_SIZE_X = 159;
	const int TILE_SIZE_Y = 96;
	const int TILE_TYPES = 1;
	const int VERTS_IN_QUAD = 4;

	float scaleX = (m_Resolution.x / 100) * 0.16;
	float scaleY = (m_Resolution.y / 100) * 0.2;

	int worldWidth = 20;
	int worldHeight = 1;

	// What type of primitive are we using?
	rVA.setPrimitiveType(sf::Quads);

	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Position each vertex in the current quad
			rVA[currentVertex + 0].position = sf::Vector2f((w * TILE_SIZE_X) * 4, ((resolution.y / 100) * 178));
			rVA[currentVertex + 1].position = sf::Vector2f(((w * TILE_SIZE_X) + TILE_SIZE_X) * 4, ((resolution.y / 100) * 178));
			rVA[currentVertex + 2].position = sf::Vector2f(((w * TILE_SIZE_X) + TILE_SIZE_X) * 4, (((resolution.y / 100) * 178) + TILE_SIZE_Y * 2.9));
			rVA[currentVertex + 3].position = sf::Vector2f((w * TILE_SIZE_X) * 4, (((resolution.y / 100) * 178) + TILE_SIZE_Y * 2.9));

			// Define the position in the Texture to draw for current quad
			// Either mud, stone, grass or wall
			//if (h == 8)
			//{
				// Use the wall texture
				rVA[currentVertex + 0].texCoords = sf::Vector2f(0, 0 + TILE_TYPES * TILE_SIZE_Y);
				rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE_X, 0 + TILE_TYPES * TILE_SIZE_Y);
				rVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE_X, TILE_SIZE_Y + TILE_TYPES * TILE_SIZE_Y);
				rVA[currentVertex + 3].texCoords = sf::Vector2f(0, TILE_SIZE_Y + TILE_TYPES * TILE_SIZE_Y);
			//}
			//else
			//{
				// Use a random floor texture
				srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE_Y;

				rVA[currentVertex + 0].texCoords = sf::Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE_X, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE_X, TILE_SIZE_Y + verticalOffset);
				rVA[currentVertex + 3].texCoords = sf::Vector2f(0, TILE_SIZE_Y + verticalOffset);
			//}

			// Position ready for the next for vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
}

sf::Texture Floor::getTexture() {
	return TextureHolder::GetTexture(
		"Graphics/cyberpunk city 2 files/cyberpunk city 2 files/Environmet/tileset3.png", false);
}