#pragma once
#include <SFML/Audio.hpp>

#include <map>
class AudioManager
{
public:

	inline static float GetVolume() { return volume; }
	inline static float GetMaxVolume() { return maxVolume; }
	static void SetVolume(float _volume);
	
	inline static void Loop(const bool& _state) { if (music) music->setLoop(_state); }

	inline static void Pause() { if (music) music->pause(); }
	inline static void Stop() { if(music) music->stop(); }

	static void PlayMusic(const std::string& _key);
	static void PlaySound(const std::string& _key);

	static void AddMusic(const std::string& _key, const std::string& _fileName);
	static void AddSound(const std::string& _key, const std::string& _fileName);

	static void DeleteMusic(const std::string& _key);
	static void DeleteSound(const std::string& _key);

	static void PauseMusic();

	static void ResumeMusic();

	static void StopMusic();

	~AudioManager();

private:
	static float volume;
	static float maxVolume;
	static sf::Music* music;
	static sf::Sound* sound;
	static std::map<std::string, sf::Music*> musics;
	static std::map<std::string, sf::Sound*> sounds;
	static std::map<std::string, sf::SoundBuffer*> soundBuffers;
};

