#pragma once
#include <fmod.hpp>

class AudioManager
{
public:
	static FMOD::System* system; // Virtual sound card
	static FMOD::Sound* mainMenuSound;
	static FMOD::Sound* level1Sound;
	static FMOD::Sound* level2Sound;
	static FMOD::Sound* jumpSound;
	static FMOD::Sound* landSound;
	static FMOD::Sound* footstepSound;
	static FMOD::Sound* mouseHoverSound;
	static FMOD::Sound* UISelectSound;
	static FMOD::Sound* collectAsteroidSound;
	static FMOD::Sound* victory;
	static FMOD::Channel* channel; // To manipulate the sound
	static FMOD::Channel* collectChannel;
	static FMOD::Channel* hoverChannel;
	static FMOD::Channel* bgmChannel;
	static FMOD::Channel* victoryChannel;
	static FMOD_RESULT result;
	void* extradriverdata = 0;

	void InitialiseAudio();
	static void PlayMainMenuSound();
	static void PlayLevel1Sound();
	static void PlayLevel2Sound();
	static void PlayJumpSound(float pan);
	static void PauseSound();
	static void PlayLandSound(float pan);
	static void PlayFootstepSound(float pan);
	static void ChangeLevel2Pitch(float pitch);
	static void PlayCollectAsteroidSound(float pan);
	static void PlayMouseHoverSound();
	static void PlaySelectSound();
	static void PlayVictorySound();
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