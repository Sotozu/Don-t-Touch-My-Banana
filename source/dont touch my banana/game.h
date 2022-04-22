#pragma once
#include "baseTypes.h"
#include "PlayerMonkey.h"
#include "Platform.h"
#include "RopeVineSegment.h"
#include "Banana.h"
#include "BananaManager.h"
#include "AudioManager.h"

#define NUMBER_OF_ROPEVINES 7
#define NUMBER_OF_PLATFORMS 7

#define WIN_POINTS 20
#define GAME_TIMER 1000.f

class CGame
{
public:
	const char8_t *GetGameTitle(){return mGameTitle;}
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	~CGame();
	void DrawScene();
	void CheckCollision();
	bool AABB_Intersecting_Collision(PlayerMonkey& ,RopeVineSegment[]);
	bool AABB_Intersecting_Collision(PlayerMonkey& ,Platform[]);
	bool AABB_Intersecting_Collision(PlayerMonkey&, Banana[]);

	//bool AABB_Intersecting_Collision(PlayerMonkey*, Projectile*);

	void UpdateFrame();
	void DestroyGame();
	void init();
	void shutdown();
	static const uint32_t mScreenWidth = 1024;
	static const uint32_t mScreenHeight = 768;
	static const uint32_t mBitsPerPixel = 32;
	bool isGameWOn();

private:
	static const char8_t mGameTitle[20];
	static CGame *sInstance;
	PlayerMonkey* player1;
	PlayerMonkey* player2;
	RopeVineSegment* vines;
	Platform* platforms;
	int BackgroundTextureID;
	bool isGameWon;
	CGame();

	int IntroTexID;
	int WinP1TexID, WinP2TexID;

	int scoreTexID;
	int score2TexID;
	int monkeyscoreTexID;
	int monkeyscore2TexID;
	void DrawScore();

	void keyProcess();

	void ResetGame();

	bool ISGAMESTARTED{ false };
	bool isGameStartKeyPressed{ false };
	bool isRestart{ false };
	int winner;

};

