
#include "FMOD/inc/fmod.hpp"
#include "FMOD/inc/fmod_errors.h"
#include "baseTypes.h"
#include "AudioManager.h"
#include <windows.h>


AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::CreateInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AudioManager();
	}
	return sInstance;
}

void AudioManager::init()
{

	
	createSound(&themeMusic, "Content/Theme_Music.mp3");
	createSound(&collectedBananaSound, "Content/collectBanana.mp3");
	createSound(&flingePoopSound, "Content/flingPoop.mp3");
	createSound(&jumpSound, "Content/jump.mp3");
	createSound(&grabVine, "Content/grabVine.mp3");
	createSound(&isHitSound, "Content/CompleteHitSound.mp3");
	createSound(&WinSound, "Content/MonkeyWinSound.mp3");


}

void AudioManager::update()
{

}

void AudioManager::shutdown()
{
	// Release sounds
	releaseSound(themeMusic);
}

void AudioManager::playThemeMusic()
{
	playSound(themeMusic, themeChannel, true);
}

void AudioManager::playFlingPoopSound() {
	playSound(flingePoopSound, flingPoopChannel, false);

}

void AudioManager::playerIsHitSound() {
	playSound(isHitSound, isHitChannel, false);

}
void AudioManager::playWinSound()
{
	playSound(WinSound, winSoundChannel, false);
}
void AudioManager::playJumpSound() {
	playSound(jumpSound, jumpChannel ,false);

}
void AudioManager::playCollectedBananaSound() {
	playSound(collectedBananaSound, collectBananasChannel, false);

}

void AudioManager::playGrabVineSound()
{
	playSound(grabVine, grabVineChannel, false);

}

AudioManager::AudioManager() : 
	flingPoopPlayCounter(0),
	jumpSoundPlayCounter(0), 
	collectBananaSoundPlayCounter(0)
{
	if (FMOD::System_Create(&mSystem) != FMOD_OK)
	{
		return;
	}
	// Check if the PC has a sound driver
	int driverCount = 0;
	mSystem->getNumDrivers(&driverCount);
	if (driverCount == 0)
	{
		return;
	}
	// Initialize an instance with 12 channels
	mSystem->init(32, FMOD_INIT_NORMAL, nullptr);
};


void AudioManager::createSound(Sound* pSound, const char* pFile)
{
	mSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
}

void AudioManager::createStream(Sound* pSound, const char* pFile) {
	mSystem->createStream(pFile, FMOD_DEFAULT, 0, pSound);

}


void AudioManager::playSound(Sound pSound, Channel& _channel, bool8_t loop)
{


	if (!loop)
	{
		pSound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}
	FMOD_RESULT result = mSystem->playSound(pSound, 0, false, &_channel);
	if (result != FMOD_OK) {
		int i = 0;
	}
}

void AudioManager::releaseSound(Sound pSound)
{
	pSound->release();
}

void AudioManager::releaseJumpSound()
{
	jumpSound->release();
	
}
void AudioManager::releaseCollectedBananaSound()
{
	collectedBananaSound->release();
}
void AudioManager::releaseFlingPoopSound()
{
	flingePoopSound->release();
}


void AudioManager::releaseIsHitSound()
{
	isHitSound->release();
}
void AudioManager::releaseWinSound()
{
	WinSound->release();

}
void AudioManager::UpdateAudioManager() {
	mSystem->update();
}
