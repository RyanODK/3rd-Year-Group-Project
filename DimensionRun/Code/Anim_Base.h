#pragma once
#include <string>
#include "Directions.h"

class SpriteSheet;
using Frame = unsigned int;

class Anim_Base {
	friend class SpriteSheet;

public:
	Anim_Base();
	virtual ~Anim_Base();

	void SetSpriteSheet(SpriteSheet* l_Sheet);

	bool SetFrame(Frame l_Frame);
	void SetName(const std::string& l_Name);
	void SetLooping(bool l_loop);

	bool IsLooping();
	bool IsInAction();
	bool IsPlaying();
	bool CheckMoved();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	SpriteSheet* GetSpriteSheet();
	std::string GetName();
	Frame GetFrame();

	virtual void Update(const float& l_deltaTime);

	friend std::stringstream& operator >>(std::stringstream& l_Stream, Anim_Base& a) {
		a.ReadIn(l_Stream);
		return l_Stream;
	}

protected:
	void FrameStep();
	void CropSprite();
	void ReadIn(std::stringstream& l_Stream);

	Frame m_FrameCurrent;
	Frame m_FrameStart;
	Frame m_FrameEnd;
	Frame m_FrameRow;

	int m_FrameActionStart; // Frame when specific action begins
	int m_FrameActionEnd; // frame when specific action ends

	float m_FrameTime;
	float m_ElapsedTime;

	bool m_Loop;
	bool m_IsPlaying;
	bool m_HasMoved;

	std::string m_Name;
	SpriteSheet* m_SpriteSheet;
};