#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Utilities.h"
#include "Anim_Directional.h"
#include <unordered_map>

using Animations = std::unordered_map<std::string, Anim_Base*>;

class SpriteSheet {
public:
    SpriteSheet(TextureManager* l_textMgr);
    ~SpriteSheet();

    void SetSpriteSize(const sf::Vector2u& l_Size);
    void SetSpritePosition(const sf::Vector2f& l_Pos);
    void CropSprite(const sf::IntRect& l_rect);
    void SetDirection(const Direction& l_dir);

    Direction GetDirection();
    sf::Vector2u GetSpriteSize() const;
    sf::Vector2f GetSpritePosition() const;

    void SetSheetPadding(const sf::Vector2f& l_padding);
    void SetSpriteSpacing(const sf::Vector2f& l_spacing);
    const sf::Vector2f& GetSheetPadding()const;
    const sf::Vector2f& GetSpriteSpacing()const;

    bool LoadSheet(const std::string& l_file);
    void ReleaseSheet();

    Anim_Base* GetCurrentAnim();
    bool SetAnimation(const std::string& l_name, bool l_play = false, bool l_loop = false);

    void Update(float l_dT);
    void Draw(sf::RenderWindow* l_wnd);
private:
    std::string m_Texture;
    sf::Sprite m_Sprite;
    sf::Vector2u m_SpriteSize;
    sf::Vector2f m_SpriteScale;
    Animations m_Animations;
    Anim_Base* m_AnimationCurrent;
    TextureManager* m_TextureManager;
    Direction m_Direction;
    std::string m_AnimType;

    sf::Vector2f m_SheetPadding;
    sf::Vector2f m_SpriteSpacing;
};
