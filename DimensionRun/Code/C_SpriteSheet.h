#pragma once
#include "C_Drawable.h"
#include "SpriteSheet.h" 

class C_SpriteSheet : public C_Drawable {
public:
	C_SpriteSheet() : C_Drawable(Component::SpriteSheet), m_SpriteSheet(nullptr) {}
	~C_SpriteSheet() { 
		if (m_SpriteSheet) { 
			delete m_SpriteSheet; 
		} 
	}

	void ReadIn(std::stringstream& l_stream) {
		l_stream >> m_SheetName;
	}

	void Create(TextureManager* l_textureMgr,
		const std::string& l_name = "")
	{
		if (m_SpriteSheet) { 
			return; 
		}

		m_SpriteSheet = new SpriteSheet(l_textureMgr);
		m_SpriteSheet->LoadSheet("Code/Resources/Media/Spritesheets/" +
			(l_name != "" ? l_name : m_SheetName) + ".sheet");
	}

	SpriteSheet* GetSpriteSheet() { 
		return m_SpriteSheet; 
	}

	void UpdatePosition(const sf::Vector2f& l_vec) {
		m_SpriteSheet->SetSpritePosition(l_vec);
	}

	const sf::Vector2u& GetSize() {
		return m_SpriteSheet->GetSpriteSize();
	}

	void Draw(sf::RenderWindow* l_wind) {
		if (!m_SpriteSheet) { 
			std::cout << "no spritesheet for player" << std::endl;
			return; 
		}
		if(m_SpriteSheet) {
			std::cout << "there is spritesheet for player" << std::endl;
			m_SpriteSheet->Draw(l_wind);
		}
	}
private:
	SpriteSheet* m_SpriteSheet;
	std::string m_SheetName;
};
