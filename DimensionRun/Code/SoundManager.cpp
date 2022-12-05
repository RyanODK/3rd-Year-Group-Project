#include "SoundManager.h"
#include "StateManager.h"

SoundManager::SoundManager(AudioManager* l_AudioMgr) : 
	m_LastID(0), m_AudioManager(l_AudioMgr), m_Elapsed(0.f), m_NumSounds(0) {}

SoundManager::~SoundManager() {
	CleanUp();
}

void SoundManager::ChangeState(const StateType& l_State) {
	PauseAll(m_CurrentState);
	UnpauseAll(l_State);
	m_CurrentState = l_State;

	if (m_Music.find(m_CurrentState) != m_Music.end()) {
		return;
	}

	SoundInfo info("");
	sf::Music* music = nullptr;
	m_Music.emplace(m_CurrentState, std::make_pair(info, music));
}

void SoundManager::RemoveState(const StateType& l_State) {
	auto& StateSounds = m_Audio.find(l_State)->second;

	for (auto& itr : StateSounds) {
		RecycleSound(itr.first, itr.second.second, itr.second.first.m_Name);
	}

	m_Audio.erase(l_State);
	auto music = m_Music.find(l_State);

	if (music == m_Music.end()) {
		return;
	}

	if (music->second.second) {
		delete music->second.second;
		--m_NumSounds;
	}
	m_Music.erase(l_State);
}

void SoundManager::CleanUp() {
	for (auto& state : m_Audio) {
		for (auto& sound : state.second) {
			m_AudioManager->ReleaseResource(sound.second.first.m_Name);
			delete sound.second.second;
		}
	}
	m_Audio.clear();

	for (auto& recycled : m_Recycled) {
		m_AudioManager->ReleaseResource(recycled.first.second);
		delete recycled.second;
	}
	m_Recycled.clear();

	for (auto& music : m_Music) {
		if (music.second.second) {
			delete music.second.second;
		}
	}
	m_Music.clear();

	m_Properties.clear();
	m_NumSounds = 0;
	m_LastID = 0;
}

void SoundManager::Update(float l_DeltaTime) {
	m_Elapsed += l_DeltaTime;

	if (m_Elapsed < 0.33f) {
		// run once every 1/3 of a second
		return;
	}
	m_Elapsed = 0;

	auto& container = m_Audio[m_CurrentState];

	for (auto itr = container.begin(); itr != container.end();) {
		if (!itr->second.second->getStatus()) {
			RecycleSound(itr->first, itr->second.second, itr->second.first.m_Name);
			itr = container.erase(itr); // remove sound
			continue;
		}
		itr++;
	}

	auto music = m_Music.find(m_CurrentState);
	if (music == m_Music.end()) {
		return;
	}

	if (!music->second.second) {
		return;
	}

	if (music->second.second->getStatus()) {
		return;
	}

	delete music->second.second;
	music->second.second = nullptr;
	m_NumSounds--;
}

SoundID SoundManager::Play(
	const std::string& l_Sound, const sf::Vector3f& l_Position, 
	bool l_Loop, bool l_Relative) 
{
	SoundProps* props = GetSoundProperties(l_Sound);

	if (!props) {
		return -1; // failed to load sound properties
	}

	SoundID id;

	sf::Sound* sound = CreateSound(id, props->m_AudioName);

	if (!sound) {
		return -1;
	}

	// sound created successfully
	SetUpSound(sound, props, l_Loop, l_Relative);
	sound->setPosition(l_Position);
	SoundInfo info(props->m_AudioName);
	m_Audio[m_CurrentState].emplace(id, std::make_pair(info, sound));
	sound->play();
	return id;
}

bool SoundManager::Play(const SoundID& l_ID) {
	auto& container = m_Audio[m_CurrentState];
	auto sound = container.find(l_ID);

	if (sound == container.end()) {
		return false;
	}

	sound->second.second->play();
	sound->second.first.m_ManualPaused = false;
	return true;
}

bool SoundManager::Stop(const SoundID& l_ID) {
	auto& container = m_Audio[m_CurrentState];
	auto sound = container.find(l_ID);

	if (sound == container.end()) {
		return false;
	}

	sound->second.second->stop();
	sound->second.first.m_ManualPaused = true;
	return true;
}

bool SoundManager::Pause(const SoundID& l_ID) {
	auto& container = m_Audio[m_CurrentState];
	auto sound = container.find(l_ID);

	if (sound == container.end()) { 
		return false; 
	}

	sound->second.second->pause();
	sound->second.first.m_ManualPaused = true;
	return true;
}

bool SoundManager::PlayMusic(const std::string& l_MusicID,
	float l_Volume, bool l_Loop)
{
	auto sound = m_Music.find(m_CurrentState);
	if (sound == m_Music.end()) { 
		return false;
	}

	std::string path = m_AudioManager->GetPath(l_MusicID);
	if (path == "") { 
		return false; 
	}

	if (!sound->second.second) {
		sound->second.second = new sf::Music();
		m_NumSounds++;
	}

	sf::Music* music = sound->second.second;
	if (!music->openFromFile(path)) {
		delete music;
		m_NumSounds--;
		sound->second.second = nullptr;
		std::cerr << "!Failed to load music from file: " << l_MusicID << std::endl;
		return false;
	}

	music->setLoop(l_Loop);
	music->setVolume(l_Volume);
	music->setRelativeToListener(true); // Always relative.
	music->play();
	sound->second.first.m_Name = l_MusicID;
	return true;
}

bool SoundManager::PlayMusic(const StateType& l_State) {
	auto music = m_Music.find(m_CurrentState);

	if (music == m_Music.end()) { 
		return false; 
	}

	if (!music->second.second) { 
		return false; 
	}

	music->second.second->play();
	music->second.first.m_ManualPaused = false;
	return true;
}

bool SoundManager::StopMusic(const StateType& l_State) {
	auto music = m_Music.find(m_CurrentState);

	if (music == m_Music.end()) { 
		return false; 
	}

	if (!music->second.second) { 
		return false;
	}

	music->second.second->stop();
	delete music->second.second;
	music->second.second = nullptr;
	m_NumSounds--;
	return true;
}

bool SoundManager::PauseMusic(const StateType& l_State) {
	auto music = m_Music.find(m_CurrentState);
	if (music == m_Music.end()) {
		return false; 
	}

	if (!music->second.second) { 
		return false; 
	}

	music->second.second->pause();
	music->second.first.m_ManualPaused = true;
	return true;
}

bool SoundManager::SetPosition(const SoundID& l_ID,
	const sf::Vector3f& l_Pos)
{
	auto& container = m_Audio[m_CurrentState];
	auto sound = container.find(l_ID);

	if (sound == container.end()) { 
		return false; 
	}

	sound->second.second->setPosition(l_Pos);
	return true;
}

bool SoundManager::IsPlaying(const SoundID& l_ID) {
	auto& container = m_Audio[m_CurrentState];
	auto sound = container.find(l_ID);

	return (sound != container.end() ? sound->second.second->getStatus() : false);
}

SoundProps* SoundManager::GetSoundProperties(
	const std::string& l_SoundName)
{
	auto properties = m_Properties.find(l_SoundName); // this should have '&' beside auto
	if (properties == m_Properties.end()) {
		if (!LoadProperties(l_SoundName)) { 
			return nullptr;
		}
		properties = m_Properties.find(l_SoundName);
	}
	return &properties->second;
}

bool SoundManager::LoadProperties(const std::string& l_Name) {
	std::ifstream file;
	file.open("media/Sounds/" + l_Name + ".sound");
	if (!file.is_open()) {
		std::cerr << "Failed to load sound: " << l_Name << std::endl;
		return false;
	}

	SoundProps props("");
	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') { 
			continue;
		}

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;

		if (type == "Audio") {
			keystream >> props.m_AudioName;
		}
		else if (type == "Volume") {
			keystream >> props.m_Volume;
		}
		else if (type == "Pitch") {
			keystream >> props.m_Pitch;
		}
		else if (type == "Distance") {
			keystream >> props.m_MinDistance;
		}
		else if (type == "Attenuation") {
			keystream >> props.m_Attenuation;
		}
		else {
			// ?
		}
	}
	file.close();

	if (props.m_AudioName == "") { 
		return false; 
	}
	m_Properties.emplace(l_Name, props);
	return true;
}

void SoundManager::PauseAll(const StateType& l_State) {
	auto& container = m_Audio[l_State];

	for (auto itr = container.begin(); itr != container.end();) {
		if (!itr->second.second->getStatus()) {
			RecycleSound(itr->first, itr->second.second,
				itr->second.first.m_Name);
			itr = container.erase(itr);
			continue;
		}
		itr->second.second->pause();
		++itr;
	}

	auto music = m_Music.find(l_State);
	if (music == m_Music.end()) { 
		return; 
	}

	if (!music->second.second) { 
		return; 
	}
	music->second.second->pause();
}

void SoundManager::UnpauseAll(const StateType& l_State) {
	auto& container = m_Audio[l_State];
	for (auto& itr : container) {
		if (itr.second.first.m_ManualPaused) { 
			continue; 
		}
		itr.second.second->play();
	}

	auto music = m_Music.find(l_State);
	if (music == m_Music.end()) { 
		return;
	}
	if (!music->second.second || music->second.first.m_ManualPaused) {
		return;
	}
	music->second.second->play();
}

sf::Sound* SoundManager::CreateSound(SoundID& l_ID,
	const std::string& l_AudioName)
{
	sf::Sound* sound = nullptr;
	if (!m_Recycled.empty() && (m_NumSounds >= Max_Sounds ||
		m_Recycled.size() >= Sound_Cache))
	{
		auto itr = m_Recycled.begin();
		while (itr != m_Recycled.end()) {
			if (itr->first.second == l_AudioName) { 
				break; 
			}
			++itr;
		}
		if (itr == m_Recycled.end()) {
			// If a sound with the same name hasn't been found!
			auto element = m_Recycled.begin();
			l_ID = element->first.first;
			m_AudioManager->ReleaseResource(element->first.second);
			m_AudioManager->RequireResource(l_AudioName);
			sound = element->second;
			sound->setBuffer(*m_AudioManager->GetResource(l_AudioName));
			m_Recycled.erase(element);
		}
		else {
			l_ID = itr->first.first;
			sound = itr->second;
			m_Recycled.erase(itr);
		}
		return sound;
	}
	if (m_NumSounds < Max_Sounds) {
		if (m_AudioManager->RequireResource(l_AudioName)) {
			sound = new sf::Sound();
			l_ID = m_LastID;
			m_LastID++;
			++m_NumSounds;
			sound->setBuffer(*m_AudioManager->GetResource(l_AudioName));
			return sound;
		}
	}
	std::cerr << "!Failed to create sound" << std::endl;
	return nullptr;
}

void SoundManager::SetUpSound(sf::Sound* l_Sound,
	const SoundProps* l_Props, bool l_Loop, bool l_Relative)
{
	l_Sound->setVolume(l_Props->m_Volume);
	l_Sound->setPitch(l_Props->m_Pitch);
	l_Sound->setMinDistance(l_Props->m_MinDistance);
	l_Sound->setAttenuation(l_Props->m_Attenuation);
	l_Sound->setLoop(l_Loop);
	l_Sound->setRelativeToListener(l_Relative);
}

void SoundManager::RecycleSound(const SoundID& l_ID,
	sf::Sound* l_Sound, const std::string& l_name)
{
	m_Recycled.emplace_back(std::make_pair(l_ID, l_name), l_Sound);
}