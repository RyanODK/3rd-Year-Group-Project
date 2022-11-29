#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Utilities.h"
#include "Anim_Base.h"
#include <unordered_map>

using Animations = std::unordered_map<std::string, Anim_Base*>;

class SpriteSheet {
public:
    SpriteSheet(TextureManager* l_textMgr);
    ~SpriteSheet();

    void SetSpriteSize(const sf::Vector2i& l_Size);
    void SetSpritePosition(const sf::Vector2f& l_Pos);
    void CropSprite(const sf::IntRect& l_rect);
    
    sf::Vector2i GetSpriteSize() const;
    sf::Vector2f GetSpritePosition() const;

    bool LoadSheet(const std::string& l_file);
    void ReleaseSheet();

    Anim_Base* GetCurrentAnim();
    bool SetAnimation(const std::string& l_name,
        const bool& l_play = false,
        const bool& l_loop = false);

    void Update(const float& l_dT);
    void Draw(sf::RenderWindow* l_wnd);
private:
    std::string m_Texture;
    sf::Sprite m_Sprite;
    sf::Vector2i m_SpriteSize;
    sf::Vector2f m_SpriteScale;
    //std::string m_AnimType;
    Animations m_Animations;
    Anim_Base* m_AnimationCurrent;
    TextureManager* m_TextureManager;
};
