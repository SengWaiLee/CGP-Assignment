#include "AudioManager.h"
FMOD::System* AudioManager::system; //virtual sound card
FMOD::Sound* AudioManager::mainMenuSound;
FMOD::Sound* AudioManager::jumpSound;
FMOD::Sound* AudioManager::landSound;
FMOD::Sound* AudioManager::UISelectSound;
FMOD::Sound* AudioManager::victory;
FMOD::Channel* AudioManager::channel;
FMOD::Channel* AudioManager::bgmChannel;
FMOD_RESULT AudioManager::result;
float AudioManager::SOUND_VOLUME = 1.0f;

void AudioManager::InitialiseAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

void AudioManager::PlayMainMenuSound()
{
	result = system->playSound(mainMenuSound, 0, false, &bgmChannel);
	bgmChannel->setVolume(1.0f);
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

void AudioManager::PlayVictorySounds()
{
	result = system->playSound(victory, 0, true, &channel);
	channel->setVolume(0.8f);
	channel->setPan(0.0f);
	channel->setPaused(false);
}

void AudioManager::PlaySelectSounds()
{
	result = system->playSound(UISelectSound, 0, true, &channel);
	channel->setVolume(0.8f);
	channel->setPan(0.0f);
	channel->setPaused(false);
}

void AudioManager::PlaySoundTrack()
{}

void AudioManager::PauseSounds() {
	channel->setPaused(true);
}


void AudioManager::LoadSounds()
{
	result = system->createSound("Napple Tale_ Arsia in Daydream - Snowball (Dreamcast).mp3", FMOD_DEFAULT, 0, &mainMenuSound);
	result = mainMenuSound->setMode(FMOD_LOOP_NORMAL);
	result = system->createSound("jump.mp3", FMOD_DEFAULT, 0, &jumpSound);
	result = jumpSound->setMode(FMOD_LOOP_OFF);
	result = system->createSound("land.ogg", FMOD_DEFAULT, 0, &landSound);
	result = landSound->setMode(FMOD_LOOP_OFF);
	result = system->createSound("victory.wav", FMOD_DEFAULT, 0, &victory);
	result = victory->setMode(FMOD_LOOP_OFF);
	result = system->createSound("UIselect.wav", FMOD_DEFAULT, 0, &UISelectSound);
	result = UISelectSound->setMode(FMOD_LOOP_OFF);
}

void AudioManager::updateSound()
{
	system->update();
}

AudioManager::AudioManager()
{}

AudioManager::~AudioManager()
{}

void AudioManager::VolumeControl(float volume) {
	if (volume >= 1.0f)
	{
		volume = 1.0f;
	}
	else if (volume <= 0.0f) {
		volume = 0.0f;
	}
	bgmChannel->setVolume(volume);
}
