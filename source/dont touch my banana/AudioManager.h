#pragma once

#include "FMOD/inc/fmod.hpp"
#include "FMOD/inc/fmod_errors.h"
#include "baseTypes.h"
#include "AudioManager.h"
#include <windows.h>

typedef FMOD::Sound* Sound;
typedef FMOD::Channel* Channel;

class AudioManager
{
		
public:
	~AudioManager() {};

	static AudioManager* CreateInstance();
	static AudioManager* GetInstance() { return sInstance; }

	void init();
	void update();
	void shutdown();

	void playThemeMusic();
	void playFlingPoopSound();
	void playJumpSound();
	void playCollectedBananaSound();
	void playGrabVineSound();
	void playerIsHitSound();
	void playWinSound();


	void createSound(Sound* pSound, const char* pFile);
	void createStream(Sound* pSoundm, const char* pFile);
	void playSound(Sound pSound, Channel& _channel, bool8_t loop);

	void releaseSound(Sound pSound);
	void releaseJumpSound();
	void releaseCollectedBananaSound();
	void releaseFlingPoopSound();
	void releaseIsHitSound();
	void releaseWinSound();

	void UpdateAudioManager();
	
private:
	FMOD::System* mSystem;
	Channel themeChannel;
	Channel flingPoopChannel;
	Channel jumpChannel;
	Channel collectBananasChannel;
	Channel grabVineChannel;
	Channel isHitChannel;
	Channel winSoundChannel;

	AudioManager();

	int flingPoopPlayCounter, jumpSoundPlayCounter, collectBananaSoundPlayCounter;

	static AudioManager* sInstance;

	Sound flingePoopSound;
	Sound jumpSound;
	Sound themeMusic;
	Sound collectedBananaSound;
	Sound grabVine;
	Sound isHitSound;
	Sound WinSound;
	
};