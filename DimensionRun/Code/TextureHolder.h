#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <sstream>

// using namespace to stop need of sf:: or std::
using namespace sf;
using namespace std;

class TextureHolder
{
public:
	TextureHolder();
	static Texture& GetTexture(string const& filename, bool repeat); // function to get texture from path of filename

private:
	// map container from STL
	// that holds related pairs of strings and Textures
	map<string, Texture> m_Texture;

	// pointer of TextureHolder class itself
	static TextureHolder* m_s_Instance;
};
#endif
