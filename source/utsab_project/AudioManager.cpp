#include "AudioManager.h"
#include "baseTypes.h"
#include "SoundSystem.h"

AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AudioManager();
	}
	return sInstance;
}

void AudioManager::init()
{
	mSoundSystem = new SoundSystem();
	mSoundSystem->createSound(&fireSound, "Sounds/20mm.wav");
	mSoundSystem->createSound(&airRaid, "Sounds/AirRaid.wav");
	
}

void AudioManager::update()
{

}

void AudioManager::shutdown()
{
	// Release sounds
	mSoundSystem->releaseSound(fireSound);
}

void AudioManager::playFiringSound()
{
	mSoundSystem->playSound(fireSound, FALSE);
}

void AudioManager::playAirRaidSound()
{
	mSoundSystem->playSound(airRaid, FALSE);
}
