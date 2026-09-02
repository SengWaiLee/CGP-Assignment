#include "AudioManager.h"

FMOD::System* AudioManager::system; // Virtual sound card
FMOD::Sound* AudioManager::mainMenuSound;
FMOD::Sound* AudioManager::level1Sound;
FMOD::Sound* AudioManager::level2Sound;
FMOD::Sound* AudioManager::jumpSound;
FMOD::Sound* AudioManager::landSound;
FMOD::Sound* AudioManager::UISelectSound;
FMOD::Sound* AudioManager::victory;
FMOD::Channel* AudioManager::channel;
FMOD::Channel* AudioManager::bgmChannel;
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
	channel->setVolume(0.8f);
	channel->setPan(0.0f);
	channel->setPaused(false);
}

void AudioManager::PlayLandSound()
{
	result = system->playSound(landSound, 0, true, &channel);
	channel->setVolume(1.0f);
	channel->setPan(0.0f);
	channel->setPaused(false);
}

void AudioManager::PlayVictorySound()
{
	result = system->playSound(victory, 0, true, &channel);
	channel->setVolume(0.8f);
	channel->setPan(0.0f);
	channel->setPaused(false);
}

void AudioManager::PlaySelectSound()
{
	result = system->playSound(UISelectSound, 0, true, &channel);
	channel->setVolume(0.8f);
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
	if (channel != nullptr)
	{
		channel->stop();
		channel = nullptr;
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
	result = system->createSound("Assets/victory.wav", FMOD_DEFAULT, 0, &victory);
	result = victory->setMode(FMOD_LOOP_OFF);
	result = system->createSound("Assets/UIselect.wav", FMOD_DEFAULT, 0, &UISelectSound);
	result = UISelectSound->setMode(FMOD_LOOP_OFF);
}

AudioManager::AudioManager()
{}

AudioManager::~AudioManager()
{}
