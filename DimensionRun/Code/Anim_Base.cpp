#include "Anim_Base.h"
#include "SpriteSheet.h"

Anim_Base::Anim_Base() :
	m_FrameCurrent(0), m_FrameStart(0), m_FrameEnd(0), m_FrameRow(0), m_FrameTime(0.f),
	m_ElapsedTime(0.f), m_FrameActionStart(-1),
	m_FrameActionEnd(-1), m_Loop(false), m_IsPlaying(false) {}

Anim_Base::~Anim_Base(){}

void Anim_Base::SetSpriteSheet(SpriteSheet* l_Sheet) {
	m_SpriteSheet = l_Sheet;
}

void Anim_Base::SetFrame(const unsigned int& l_Frame) {
	if ((l_Frame >= m_FrameStart && l_Frame <= m_FrameEnd) ||
		(l_Frame >= m_FrameEnd && l_Frame <= m_FrameStart)) {
		m_FrameCurrent = l_Frame;
	}
}

void Anim_Base::SetName(const std::string& l_Name) {
	m_Name = l_Name;
}

std::string Anim_Base::GetName() {
	return m_Name;
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