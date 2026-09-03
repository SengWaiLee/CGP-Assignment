#include "AudioManager.h"
#include <iostream>
using namespace std;

FMOD::System* AudioManager::system; // Virtual sound card
FMOD::Sound* AudioManager::mainMenuSound;
FMOD::Sound* AudioManager::level1Sound;
FMOD::Sound* AudioManager::level2Sound;
FMOD::Sound* AudioManager::jumpSound;
FMOD::Sound* AudioManager::landSound;
FMOD::Sound* AudioManager::footstepSound;
FMOD::Sound* AudioManager::UISelectSound;
FMOD::Sound* AudioManager::mouseHoverSound;
FMOD::Sound* AudioManager::victory;
FMOD::Channel* AudioManager::channel;
FMOD::Channel* AudioManager::hoverChannel;
FMOD::Channel* AudioManager::bgmChannel;
FMOD::Channel* AudioManager::victoryChannel;
FMOD_RESULT AudioManager::result;
float AudioManager::SOUND_VOLUME = 1.0f;
bool AudioManager::isMuted = false;

void AudioManager::InitialiseAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

void AudioManager::PlayMainMenuSound()
{
	StopBackgroundMusic();
	
	result = system->playSound(mainMenuSound, 0, false, &bgmChannel);

	if (isMuted)
	{
		bgmChannel->setVolume(0.0f);
	}
	else
	{
		bgmChannel->setVolume(SOUND_VOLUME);
	}

	bgmChannel->setPan(0.0f);
	bgmChannel->setFrequency(44100);
	bgmChannel->setPaused(false);
}

void AudioManager::PlayJumpSound()
{
	result = system->playSound(jumpSound, 0, true, &channel);

	if (isMuted)
	{
		channel->setVolume(0.0f);
	}
	else
	{
		channel->setVolume(SOUND_VOLUME * 0.8f);
	}

	channel->setPan(0.0f);
	channel->setPaused(false);
}

void AudioManager::PlayLandSound()
{
	result = system->playSound(landSound, 0, true, &channel);

	if (isMuted)
	{
		channel->setVolume(0.0f);
	}
	else
	{
		channel->setVolume(SOUND_VOLUME * 0.8f);
	}

	channel->setPan(0.0f);
	channel->setPaused(false);
}

void AudioManager::PlayFootstepSound()
{
	bool isPlaying = false;

	if (channel != nullptr)
	{
		channel->isPlaying(&isPlaying);
	}

	if (isPlaying)
	{
		return;
	}

	result = system->playSound(footstepSound, 0, false, &channel);

	if (result != FMOD_OK)
	{
		cout << "Footstep error: " << result << endl;
		return;
	}

	if (isMuted)
	{
		channel->setVolume(0.0f);
	}
	else
	{
		channel->setVolume(SOUND_VOLUME * 0.8f);
	}

	channel->setPan(0.0f);
}

void AudioManager::PlayVictorySound()
{
	result = system->playSound(victory, 0, true, &victoryChannel);

	if (isMuted)
	{
		victoryChannel->setVolume(0.0f);
	}
	else
	{
		victoryChannel->setVolume(SOUND_VOLUME * 0.8f);
	}

	victoryChannel->setPan(0.0f);
	victoryChannel->setPaused(false);
}

void AudioManager::PlayMouseHoverSound()
{
	result = system->playSound(mouseHoverSound, 0, true, &hoverChannel);

	if (isMuted)
	{
		hoverChannel->setVolume(0.0f);
	}
	else
	{
		hoverChannel->setVolume(SOUND_VOLUME);
	}

	hoverChannel->setPan(0.0f);
	hoverChannel->setPaused(false);
}

void AudioManager::PlaySelectSound()
{
	result = system->playSound(UISelectSound, 0, true, &channel);

	if (isMuted)
	{
		channel->setVolume(0.0f);
	}
	else
	{
		channel->setVolume(SOUND_VOLUME * 0.8f);
	}

	channel->setPan(0.0f);
	channel->setPaused(false);
}

void AudioManager::PlaySoundTrack()
{}

void AudioManager::PauseSound() {
	channel->setPaused(true);
}


void AudioManager::updateSound()
{
	system->update();
}

void AudioManager::VolumeControl(float volume)
{
	if (volume >= 1.0f)
	{
		volume = 1.0f;
	}
	else if (volume <= 0.0f)
	{
		volume = 0.0f;
	}

	SOUND_VOLUME = volume;

	if (hoverChannel != nullptr)
	{
		if (isMuted)
		{
			hoverChannel->setVolume(0.0f);
		}
	}

	if (bgmChannel != nullptr)
	{
		if (isMuted)
		{
			bgmChannel->setVolume(0.0f);
		}
		else
		{
			bgmChannel->setVolume(SOUND_VOLUME);
		}
	}

	if (channel != nullptr)
	{
		if (isMuted)
		{
			channel->setVolume(0.0f);
		}
	}

	if (victoryChannel != nullptr)
	{
		if (isMuted)
		{
			victoryChannel->setVolume(0.0f);
		}
		else
		{
			victoryChannel->setVolume(SOUND_VOLUME * 0.8f);
		}
	}
}

void AudioManager::StopBackgroundMusic()
{
	if (bgmChannel != nullptr)
	{
		bgmChannel->stop();
		bgmChannel = nullptr;
	}
}

void AudioManager::StopVictorySound()
{
	if (victoryChannel != nullptr)
	{
		victoryChannel->stop();
		victoryChannel = nullptr;
	}
}

void AudioManager::PlayLevel1Sound()
{
	StopBackgroundMusic();

	result = system->playSound(level1Sound, 0, false, &bgmChannel);

	if (isMuted)
	{
		bgmChannel->setVolume(0.0f);
	}
	else
	{
		bgmChannel->setVolume(SOUND_VOLUME);
	}

	bgmChannel->setPan(0.0f);
	bgmChannel->setPaused(false);
}

void AudioManager::PlayLevel2Sound()
{
	StopBackgroundMusic();

	result = system->playSound(level2Sound, 0, false, &bgmChannel);

	if (isMuted)
	{
		bgmChannel->setVolume(0.0f);
	}
	else
	{
		bgmChannel->setVolume(SOUND_VOLUME);
	}

	bgmChannel->setPan(0.0f);
	bgmChannel->setPaused(false);
}

void AudioManager::LoadSound()
{
	result = system->createSound("Assets/mainmenubgm.mp3", FMOD_DEFAULT, 0, &mainMenuSound);
	result = mainMenuSound->setMode(FMOD_LOOP_NORMAL);
	result = system->createSound("Assets/level1bgm.mp3", FMOD_DEFAULT, 0, &level1Sound);
	result = level1Sound->setMode(FMOD_LOOP_NORMAL);
	result = system->createSound("Assets/level2bgm.mp3", FMOD_DEFAULT, 0, &level2Sound);
	result = level2Sound->setMode(FMOD_LOOP_NORMAL);
	result = system->createSound("Assets/jump.mp3", FMOD_DEFAULT, 0, &jumpSound);
	result = jumpSound->setMode(FMOD_LOOP_OFF);
	result = system->createSound("Assets/land.ogg", FMOD_DEFAULT, 0, &landSound);
	result = landSound->setMode(FMOD_LOOP_OFF);
	result = system->createSound("Assets/footsteps.wav", FMOD_DEFAULT, 0, &footstepSound);
	result = footstepSound->setMode(FMOD_LOOP_OFF);
	result = system->createSound("Assets/victory.wav", FMOD_DEFAULT, 0, &victory);
	result = victory->setMode(FMOD_LOOP_OFF);
	result = system->createSound("Assets/UIselect.wav", FMOD_DEFAULT, 0, &UISelectSound);
	result = UISelectSound->setMode(FMOD_LOOP_OFF);
	result = system->createSound("Assets/mousehover.wav", FMOD_DEFAULT, 0, &mouseHoverSound);
	result = mouseHoverSound->setMode(FMOD_LOOP_OFF);
}

AudioManager::AudioManager()
{}

AudioManager::~AudioManager()
{}
