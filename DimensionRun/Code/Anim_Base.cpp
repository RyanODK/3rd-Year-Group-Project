#include "Anim_Base.h"
#include "SpriteSheet.h"

Anim_Base::Anim_Base() :
	m_FrameCurrent(0), m_FrameStart(0), m_FrameEnd(0), m_FrameRow(0), m_FrameTime(0.f),
	m_ElapsedTime(0.f), m_FrameActionStart(-1),
	m_FrameActionEnd(-1), m_Loop(false), m_IsPlaying(false), m_HasMoved(false) {}

Anim_Base::~Anim_Base(){}

void Anim_Base::SetSpriteSheet(SpriteSheet* l_Sheet) {
	m_SpriteSheet = l_Sheet;
}

bool Anim_Base::SetFrame(Frame l_Frame) {
	if ((l_Frame >= m_FrameStart && l_Frame <= m_FrameEnd) ||
		(l_Frame >= m_FrameEnd && l_Frame <= m_FrameStart)) {
		m_FrameCurrent = l_Frame;
		m_HasMoved = true;
		return true;
	}
	return false;
}

void Anim_Base::SetName(const std::string& l_Name) {
	m_Name = l_Name;
}

void Anim_Base::SetLooping(bool l_loop) { 
	m_Loop = l_loop; 
}

std::string Anim_Base::GetName() {
	return m_Name;
}

SpriteSheet* Anim_Base::GetSpriteSheet() { 
	return m_SpriteSheet; 
}

Frame Anim_Base::GetFrame() { 
	return m_FrameCurrent; 
}

bool Anim_Base::IsInAction() {
	if (m_FrameActionStart == -1 || m_FrameActionEnd == -1) {
		return true;
	}

	return (m_FrameCurrent >= m_FrameActionStart && m_FrameCurrent <= m_FrameActionEnd);
}

bool Anim_Base::IsLooping() {
	return m_Loop;
}

bool Anim_Base::IsPlaying() {
	return m_IsPlaying;
}

bool Anim_Base::CheckMoved() {
	bool result = m_HasMoved;
	m_HasMoved = false;
	return result;
}

void Anim_Base::Play() {
	m_IsPlaying = true;
}

void Anim_Base::Pause() {
	m_IsPlaying = false;
}

void Anim_Base::Stop() {
	m_IsPlaying = false;
	Reset();
}

void Anim_Base::Reset() {
	m_FrameCurrent = m_FrameStart;
	m_ElapsedTime = 0.0f;
	CropSprite();
}

void Anim_Base::Update(const float& l_DeltaTime) {
	if (!m_IsPlaying) {
		return;
	}

	m_ElapsedTime += l_DeltaTime;

	if (m_ElapsedTime < m_FrameTime) {
		return;
	}

	FrameStep();
	CropSprite();
	m_ElapsedTime = 0;
}

void Anim_Base::CropSprite() {
	/*sf::IntRect rect(m_SpriteSheet->GetSpriteSize().x * m_FrameCurrent,
		m_SpriteSheet->GetSpriteSize().y * m_FrameRow,
		m_SpriteSheet->GetSpriteSize().x, m_SpriteSheet->GetSpriteSize().y);
	m_SpriteSheet->CropSprite(rect);*/

	sf::IntRect rect((m_SpriteSheet->GetSpriteSize().x * m_FrameCurrent),
		(m_SpriteSheet->GetSpriteSize().y * (m_FrameRow + (short)m_SpriteSheet->GetDirection()))
		+ ((m_FrameRow + (short)m_SpriteSheet->GetDirection())),
		m_SpriteSheet->GetSpriteSize().x, m_SpriteSheet->GetSpriteSize().y);
	m_SpriteSheet->CropSprite(rect);
}

void Anim_Base::FrameStep() {
	bool b = SetFrame(m_FrameCurrent + (m_FrameStart <= m_FrameEnd ? 1 : -1));
	if (b) { 
		return; 
	}
	if (m_Loop) { 
		SetFrame(m_FrameStart); 
	}
	else { 
		SetFrame(m_FrameEnd); Pause(); 
	}
}

void Anim_Base::ReadIn(std::stringstream& l_stream) {
	l_stream >> m_FrameStart >> m_FrameEnd >> m_FrameRow
		>> m_FrameTime >> m_FrameActionStart >> m_FrameActionEnd;
}