#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <SFML/Audio.hpp>
#include "AudioManager.h"

struct SoundProps {
	SoundProps(const std::string& l_Name) : m_AudioName(l_Name), m_Volume(100), m_Pitch(1.f),
		m_MinDistance(10.f), m_Attenuation(10.f) {}
	std::string m_AudioName;
	float m_Volume;
	float m_Pitch;
	float m_MinDistance;
	float m_Attenuation;
};

using SoundID = int;
enum class StateType;

struct SoundInfo {
	SoundInfo(const std::string& l_Name) : m_Name(l_Name),
		m_ManualPaused(false) {}
	std::string m_Name;
	bool m_ManualPaused;
};

using SoundProperties = std::unordered_map<std::string, SoundProps>;
using SoundContainer = std::unordered_map<SoundID, std::pair<SoundInfo, sf::Sound*>>;
using Sounds = std::unordered_map<StateType, SoundContainer>;
using RecycledSounds = std::vector<std::pair<std::pair<SoundID, std::string>, sf::Sound*>>;
using MusicContainer = std::unordered_map<StateType, std::pair<SoundInfo, sf::Music*>>;

class SoundManager {
public:
	SoundManager(AudioManager* l_AudioMgr);
	~SoundManager();

	void ChangeState(const StateType& l_State);
	void RemoveState(const StateType& l_State);

	void Update(float l_DeltaTime);

	SoundID Play(const std::string& l_Sound,
		const sf::Vector3f& l_Position,
		bool l_Loop = false,
		bool l_Relative = false);
	bool Play(const SoundID& l_ID);
	bool Stop(const SoundID& l_ID);
	bool Pause(const SoundID& l_ID);

	bool PlayMusic(const std::string& l_MusicID,
		float l_Volume = 100.f, bool l_Loop = false);
	bool PlayMusic(const StateType& l_State);
	bool StopMusic(const StateType& l_State);
	bool PauseMusic(const StateType& l_State);

	bool SetPosition(const SoundID& l_ID, const sf::Vector3f& l_Pos);
	bool IsPlaying(const SoundID& l_ID);
	SoundProps* GetSoundProperties(const std::string& l_SoundName);

	static const int Max_Sounds = 150;
	static const int Sound_Cache = 75;
private:
	bool LoadProperties(const std::string& l_File);
	void PauseAll(const StateType& l_State);
	void UnpauseAll(const StateType& l_State);

	sf::Sound* CreateSound(SoundID& l_ID, const std::string& l_AudioName);
	void SetUpSound(
		sf::Sound* l_Sound, const SoundProps* l_Props, bool l_Loop = false, bool l_Relative = false);
	void RecycleSound(const SoundID& l_ID, sf::Sound* l_Sound, const std::string& l_Name);

	void CleanUp();

	Sounds m_Audio;
	MusicContainer m_Music;
	RecycledSounds m_Recycled;
	SoundProperties m_Properties;
	StateType m_CurrentState;

	SoundID m_LastID;
	unsigned int m_NumSounds;
	float m_Elapsed;

	AudioManager* m_AudioManager;
};