#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <sstream>

class TextureHolder
{
public:
	TextureHolder();
	static sf::Texture& GetTexture(std::string const& filename, bool repeat); // function to get texture from path of filename

private:
	// map container from STL
	// that holds related pairs of strings and Textures
	std::map<std::string, sf::Texture> m_Texture;

	// pointer of TextureHolder class itself
	static TextureHolder* m_s_Instance;
};
