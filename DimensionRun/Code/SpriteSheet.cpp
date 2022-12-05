#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(TextureManager* l_TextMgr) :
	m_TextureManager(l_TextMgr), m_AnimationCurrent(nullptr),
	m_SpriteScale(1.f, 1.f) {}

SpriteSheet::~SpriteSheet() {
	ReleaseSheet();
}

void SpriteSheet::ReleaseSheet() {
	m_TextureManager->ReleaseResource(m_Texture);
	m_AnimationCurrent = nullptr;
	 
	while (m_Animations.begin() != m_Animations.end()) {
		delete m_Animations.begin()->second;
		m_Animations.erase(m_Animations.begin());
	}
}

void SpriteSheet::SetSpriteSize(const sf::Vector2u& l_Size) {
	m_SpriteSize = l_Size;
	m_Sprite.setOrigin(m_SpriteSize.x / 2, m_SpriteSize.y);
}

void SpriteSheet::SetSpritePosition(const sf::Vector2f& l_Pos) {
	m_Sprite.setPosition(l_Pos);
}

void SpriteSheet::CropSprite(const sf::IntRect& l_Rect) {
	m_Sprite.setTextureRect(l_Rect);
}

bool SpriteSheet::LoadSheet(const std::string& l_File) {
	std::ifstream sheet;
	sheet.open(l_File);

	if (sheet.is_open()) {
		ReleaseSheet(); // release current sheet resources
		std::string line;

		while (std::getline(sheet, line)) {
			if (line[0] == '|') {
				continue;
			}

			std::stringstream keystream(line);
			std::string type;
			keystream >> type;

			if (type == "Texture") {
				if (m_Texture != "") {
					std::cerr << "! Duplicate texture entries in: " << l_File << std::endl;
					continue;
				}
				std::string texture;
				keystream >> texture;

				if (!m_TextureManager->RequireResource(texture)) {
					std::cerr << "! Could not set up the texture: " << texture << std::endl;
					continue;
				}
				m_Texture = texture;
				m_Sprite.setTexture(*m_TextureManager->GetResource(m_Texture));
			}
			else if (type == "Size") {
				keystream >> m_SpriteSize.x >> m_SpriteSize.y;
				SetSpriteSize(m_SpriteSize);
			}
			else if (type == "Scale") {
				keystream >> m_SpriteScale.x >> m_SpriteScale.y;
				m_Sprite.setScale(m_SpriteScale);
			}
			/*else if (type == "AnimationType") {
				keystream >> m_AnimType;
			}*/
			else if (type == "Animation") {
				std::string name;
				keystream >> name;

				if (m_Animations.find(name) != m_Animations.end()) {
					std::cerr << "! Duplicate animation(" << name << ") in: " << l_File << std::endl;
					continue;
				}

				Anim_Base* anim = nullptr;
				anim = new Anim_Base();

				keystream >> *anim;
				anim->SetSpriteSheet(this);
				anim->SetName(name);
				anim->Reset();
				m_Animations.emplace(name, anim);

				if (m_AnimationCurrent) {
					continue;
				}

				m_AnimationCurrent = anim;
				m_AnimationCurrent->Play();
			}
		}
		sheet.close();
		return true;
	}
	std::cerr << "! Failed loading spritesheet: " << l_File << std::endl;
	return false;
}

bool SpriteSheet::SetAnimation(const std::string& l_Name, const bool& l_Play, const bool& l_Loop) {
	auto itr = m_Animations.find(l_Name);

	if (itr == m_Animations.end()) {
		return false;
	}

	if (itr->second == m_AnimationCurrent) {
		return false;
	}

	if (m_AnimationCurrent) {
		m_AnimationCurrent->Stop();
	}

	m_AnimationCurrent = itr->second;
	m_AnimationCurrent->SetLooping(l_Loop);

	if (l_Play) {
		m_AnimationCurrent->Play();
	}

	m_AnimationCurrent->CropSprite();
	return true;
}

void SpriteSheet::Update(const float& l_DeltaTime) {
	m_AnimationCurrent->Update(l_DeltaTime);
}

void SpriteSheet::Draw(sf::RenderWindow* l_Window) {
	l_Window->draw(m_Sprite);
}

sf::Vector2u SpriteSheet::GetSpriteSize() const { 
	return m_SpriteSize; 
}

sf::Vector2f SpriteSheet::GetSpritePosition() const { 
	return m_Sprite.getPosition(); 
}

Anim_Base* SpriteSheet::GetCurrentAnim() { 
	return m_AnimationCurrent; 
}