#pragma once
#include <fmod.hpp>
class AudioManager
{
public:
	static FMOD::System* system; //virtual sound card
	static FMOD::Sound* mainMenuSound;
	static FMOD::Sound* jumpSound;
	static FMOD::Sound* landSound;
	static FMOD::Sound* UISelectSound;
	static FMOD::Sound* victory;
	static FMOD::Channel* channel; //to manipulate the sound
	static FMOD::Channel* bgmChannel;
	static FMOD_RESULT result;
	void* extradriverdata = 0;

	void InitialiseAudio();
	static void PlayMainMenuSound();
	static void PlayJumpSound();
	static void PauseSounds();
	static void PlayLandSound();
	static void PlayVictorySounds();
	static void PlaySelectSounds();
	void PlaySoundTrack();
	void LoadSounds();
	void updateSound();
	static void VolumeControl(float volume);
	static float SOUND_VOLUME;

	AudioManager();
	~AudioManager();
};