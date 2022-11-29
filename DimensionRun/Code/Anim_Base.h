#pragma once
#include <string>

class SpriteSheet;
using Frame = unsigned int;

class Anim_Base {
	friend class SpriteSheet;

public:
	Anim_Base();
	virtual ~Anim_Base();

	void SetSpriteSheet(SpriteSheet* l_Sheet);

	void SetFrame(const unsigned int& l_Frame);
	void SetName(const std::string& l_Name);
	void SetLooping(bool l_loop);

	bool IsLooping();
	bool IsInAction();
	bool IsPlaying();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	std::string GetName();

	virtual void Update(const float& l_deltaTime);

	friend std::stringstream& operator >>(std::stringstream& l_Stream, Anim_Base& a) {
		a.ReadIn(l_Stream);
		return l_Stream;
	}

protected:
	virtual void FrameStep() = 0;
	virtual void CropSprite() = 0;
	virtual void ReadIn(std::stringstream& l_Stream) = 0;

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

	std::string m_Name;
	SpriteSheet* m_SpriteSheet;
};