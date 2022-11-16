#include "TextureHolder.h"
#define NDEBUG
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename, bool repeat) {
	// get reference to m_Texture using m_s_Instance
	// auto is equivalent of map<string, Texture>::iterator
	auto& m = m_s_Instance->m_Texture;

	// using iterator to hold key-value-pair
	// which will search for required key-value-pair
	// using passed in filename
	auto keyValuePair = m.find(filename);

	// if found match
	if (keyValuePair != m.end()) {
		// return texture (second value in key-value-pair)
		return keyValuePair->second;
	}
	else {
		// no filename found
		// so create a new key value pair using this filename
		auto& texture = m[filename];

		// load texture from file in usual way
		texture.loadFromFile(filename);

		if (repeat) {
			texture.setRepeated(true);
		}
		else {
			texture.setRepeated(false);
		}

		// return texture
		return texture;
	}
}