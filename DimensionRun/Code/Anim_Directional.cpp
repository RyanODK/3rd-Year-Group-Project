#include "Anim_Directional.h"
#include "SpriteSheet.h"

void Anim_Directional::CropSprite() {
	sf::Vector2f padding = m_SpriteSheet->GetSheetPadding();
	sf::Vector2f spacing = m_SpriteSheet->GetSpriteSpacing();

	sf::IntRect rect((m_SpriteSheet->GetSpriteSize().x * m_FrameCurrent) + padding.x + (spacing.x * m_FrameCurrent),
		(m_SpriteSheet->GetSpriteSize().y * (m_FrameRow + (short)m_SpriteSheet->GetDirection()))
		+ padding.y + ((m_FrameRow) * spacing.y),
		m_SpriteSheet->GetSpriteSize().x, m_SpriteSheet->GetSpriteSize().y);
	m_SpriteSheet->CropSprite(rect);
}

void Anim_Directional::FrameStep() {
	if (m_FrameStart < m_FrameEnd) { ++m_FrameCurrent; }
	else { --m_FrameCurrent; }

	if ((m_FrameStart < m_FrameEnd && m_FrameCurrent > m_FrameEnd) ||
		(m_FrameStart > m_FrameEnd && m_FrameCurrent < m_FrameEnd))
	{
		if (m_Loop) { m_FrameCurrent = m_FrameStart; return; }
		m_FrameCurrent = m_FrameEnd;
		Pause();
	}
}

void Anim_Directional::ReadIn(std::stringstream& l_stream) {
	l_stream >> m_FrameStart >> m_FrameEnd >> m_FrameRow
		>> m_FrameTime >> m_FrameActionStart >> m_FrameActionEnd;
}