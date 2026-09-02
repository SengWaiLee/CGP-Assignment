#pragma once
#include <fmod.hpp>

class AudioManager
{
public:
	static FMOD::System* system; //virtual sound card
	static FMOD::Sound* mainMenuSound;
	static FMOD::Sound* level1Sound;
	static FMOD::Sound* level2Sound;
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
	static void PlayLevel1Sound();
	static void PlayLevel2Sound();
	static void PlayJumpSound();
	static void PauseSound();
	static void PlayLandSound();
	static void PlayVictorySound();
	static void PlaySelectSound();
	static void StopBackgroundMusic();
	static void StopVictorySound();
	void PlaySoundTrack();
	void LoadSound();
	void updateSound();
	static void VolumeControl(float volume);
	static float SOUND_VOLUME;
	static bool isMuted;

	AudioManager();
	~AudioManager();
};