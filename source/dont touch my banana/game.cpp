#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <time.h>

#include "glut.h"
#include "game.h"
#include "SOIL.h"
#include "baseTypes.h"
#include "Program.h"
#include "Globals.h"
#include "InputManager.h"
#include "PlayerMonkey.h"
#include "Renderer.h"
#include "RopeVineSegment.h"
#include "ProjectileManager.h"
#include "Renderer.h"

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";
CGame* CGame::sInstance=NULL;
BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);

	CGame::CreateInstance();
	CGame::GetInstance()->init();

	srand(time(NULL));
	return TRUE;
}

CGame::CGame() : isGameWon(FALSE)
{
	//All the main objects int the game should be initialized here.
	//Each object should be in charge of calling the functions it requires to initialise its respective variables.
	player1 = new PlayerMonkey(0, 200.0f, -300.0f, ON_GROUND, new KeysPressed(65, 68, 87, 83, 32));
	player2 = new PlayerMonkey(1, -200.0f, -300.0f, ON_GROUND, new KeysPressed(37, 39, 38, 40, 13));
	

	//Should this be assigned here? Would it be better to encapsulate this in the PlayerMonkey class constructor?
	//unsigned int spriteSheetID = SOIL_load_OGL_texture("Content/monki.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	//player1->setSpriteSheetID(spriteSheetID);

	//vines = new RopeVine[1]{(1)};//initializes the ropes with size
	vines = new RopeVineSegment[NUMBER_OF_ROPEVINES]{ 
		//RopeVineSegment(7, -550.0f, -195.0f), //left vine to get up on first tier platforms
		//RopeVineSegment(7, 550.0f, -195.0f), //right vine to get on first tier platforms

		//RopeVineSegment(5, -300.0f, 115.0f), //left vine to get up on second tier platforms
		//RopeVineSegment(5, 300.0f, 115.0f),  //right vine to get up on second tier platforms

		//RopeVineSegment(14, -150.0f, 200.0f),
		//RopeVineSegment(14, 150.0f, 200.0f)

		RopeVineSegment(22, 500.0f, 64.0f),
		RopeVineSegment(22, -500.0f, 64.0f),

		RopeVineSegment(12, 290.0f, 200.0f),
		RopeVineSegment(12, -290.0f, 200.0f),

		RopeVineSegment(5, -350.0f, -65.0f),
		RopeVineSegment(5, 350.0f, -65.0f),

		RopeVineSegment(15, 0.0f, 150.0f),


	};

	platforms = new Platform[NUMBER_OF_PLATFORMS]{
		Platform(100, 0.0, -360.0f), // bottom most platform

		Platform(6, -470.0f, -100.0f),	// first tier LEFT platform
		Platform(6, 470.0f, -100.0f),	// first tier RIGHT platform

		Platform(7, -300, 0.0f),	// second tier LEFT platform
		Platform(7, 300, 0.0f),	// second tier LEFT platform
				
		Platform(8, 0.0f, -150.0f),		// second tier MIDDLE platform
		Platform(3, 0.0f, 20.0f),		// second tier MIDDLE platform

	};


}

void CGame::init()
{
	Renderer::CreateInstance();
	int loadingTexID = SOIL_load_OGL_texture("Content/loading.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	startOpenGLDrawing();
	Renderer::GetInstance()->DrawSprite(0, 0, loadingTexID, 320, 320);
	SwapBuffers(g_window->hDC);

	BackgroundTextureID = SOIL_load_OGL_texture("Content/Jungle_Background.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	IntroTexID = SOIL_load_OGL_texture("Content/intro.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	WinP1TexID = SOIL_load_OGL_texture("Content/win_p1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	WinP2TexID = SOIL_load_OGL_texture("Content/win_p2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	scoreTexID = SOIL_load_OGL_texture("Content/score.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	score2TexID = SOIL_load_OGL_texture("Content/score2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	monkeyscoreTexID = SOIL_load_OGL_texture("Content/monkeyscore.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	monkeyscore2TexID = SOIL_load_OGL_texture("Content/monkeyscore2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	InputManagerC::CreateInstance();
	InputManagerC::GetInstance()->init();

	
	BananaManager::CreateInstance();
	ProjectileManager::CreateInstance();
	ProjectileManager::GetInstance()->Init();

	AudioManager::CreateInstance();
	AudioManager::GetInstance()->init();
	AudioManager::GetInstance()->playThemeMusic();
}

/*
* ORDER IN WHICH UpdateFrame should be called
* 1.Get User Input
* 2.Update Game
* 3.Draw
*/

void CGame::ResetGame()
{
	delete player1;
	delete player2;
	player1 = new PlayerMonkey(0, 200.0f, -300.0f, ON_GROUND, new KeysPressed(65, 68, 87, 83, 32));
	player2 = new PlayerMonkey(1, -200.0f, -300.0f, ON_GROUND, new KeysPressed(37, 39, 38, 40, 13));

	BananaManager::GetInstance()->ResetAllBananas();
}

void CGame::keyProcess()
{
	if (g_keys->keyDown[VK_ESCAPE])								// Is ESC Being Pressed?
	{
		TerminateApplication(g_window);						// Terminate The Program
	}

	if (g_keys->keyDown[VK_F1])									// Is F1 Being Pressed?
	{
		//ToggleFullscreen(g_window);							// Toggle Fullscreen Mode
	}

	if (!ISGAMESTARTED)
	{
		if (isGameStartKeyPressed)
		{
			if (!g_keys->keyDown[VK_SPACE])
			{
				if (isRestart)
				{
					ResetGame();
				}
				ISGAMESTARTED = true;
				isRestart = true;
			}
		}
		isGameStartKeyPressed = g_keys->keyDown[VK_SPACE];
	}
}

void CGame::UpdateFrame()			
{
	keyProcess();

	if (!ISGAMESTARTED) return;

	AudioManager::GetInstance()->UpdateAudioManager();

	InputManagerC::GetInstance()->update();
	player1->UpdatePlayer();
	player2->UpdatePlayer();

	ProjectileManager::GetInstance()->Update();

	CheckCollision();

	if (player1->player_points >= WIN_POINTS)
	{
		winner = WinP1TexID;
		ISGAMESTARTED = false;
		AudioManager::GetInstance()->playWinSound();

	}
	else if (player2->player_points >= WIN_POINTS)
	{
		winner = WinP2TexID;
		ISGAMESTARTED = false;
		AudioManager::GetInstance()->playWinSound();
	}
}

void CGame::DrawScene(void)
{
	startOpenGLDrawing();

	Renderer::GetInstance()->DrawSprite(0, 0, BackgroundTextureID, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	for (int i = 0; i < NUMBER_OF_ROPEVINES; ++i) {
		vines[i].DrawSprite();
	}

	ProjectileManager::GetInstance()->Draw();

	for (int i = 0; i < NUMBER_OF_PLATFORMS; ++i) {
		platforms[i].DrawSprite();
	}

	if (ISGAMESTARTED)
	{
		BananaManager::GetInstance()->DrawBananas();

		player1->DrawSprite();
		player2->DrawSprite();
		DrawScore();
	}
	else
	{
		Renderer::GetInstance()->DrawSprite(0, 0, (isRestart) ? winner : IntroTexID, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
}

void CGame::DrawScore()
{
	const float scoresize = 64.f;
	const float offset_X = 14.f;
	const float offset_Y = -8.f;
	Renderer::GetInstance()->DrawSprite(-(g_window->init.width / 2) + scoresize + offset_X, (g_window->init.height / 2) - scoresize - offset_Y, scoreTexID, scoresize, scoresize, WIN_POINTS - player1->player_points - 1, 0, 30, 1);
	Renderer::GetInstance()->DrawSprite((g_window->init.width / 2) - scoresize -offset_X, (g_window->init.height / 2) - scoresize - offset_Y, score2TexID, scoresize, scoresize, WIN_POINTS - player2->player_points - 1, 0, 30, 1);

	const float monkeyscoresize = 32.f;
	Renderer::GetInstance()->DrawSprite(-(g_window->init.width / 2) + monkeyscoresize + scoresize * 2 - 12.f, (g_window->init.height / 2) - monkeyscoresize - scoresize + 12.f, monkeyscoreTexID, monkeyscoresize, monkeyscoresize, 0, 0, 1, 1);
	Renderer::GetInstance()->DrawSprite((g_window->init.width / 2) - monkeyscoresize - scoresize * 2 + 12.f, (g_window->init.height / 2) - monkeyscoresize - scoresize + 12.f, monkeyscore2TexID, monkeyscoresize, monkeyscoresize, 0, 0, 1, 1);
}


//Order muse be platforms->vines->air
void CGame::CheckCollision()
{
	//Check each monkey against all vines in the scene

	/*if (AABB_Intersecting_Collision(player1, vines)) {}
	else if (AABB_Intersecting_Collision(player1, platforms)) {}
	else {player1->setPlayerState(IN_AIR);}*/

	ProjectileManager::GetInstance()->CheckCollision(platforms);
	ProjectileManager::GetInstance()->CheckCollision(*player1);
	ProjectileManager::GetInstance()->CheckCollision(*player2);
	ProjectileManager::GetInstance()->CheckCollision();

	if (player1->getPlayerState() != HIT)
	{
		AABB_Intersecting_Collision(*player1, BananaManager::GetInstance()->getBananas());

		if (AABB_Intersecting_Collision(*player1, platforms)) {}
		else if (AABB_Intersecting_Collision(*player1, vines)) {}
		else { 
			if (player1->getPlayerState() != IN_AIR) {
				player1->setPlayerState(IN_AIR);
			}
		}
	}

	if (player2->getPlayerState() != HIT)
	{
		AABB_Intersecting_Collision(*player2, BananaManager::GetInstance()->getBananas());

		if (AABB_Intersecting_Collision(*player2, platforms)) {}
		else if (AABB_Intersecting_Collision(*player2, vines)) {}
		else { 
			if (player2->getPlayerState() != IN_AIR) {
				player2->setPlayerState(IN_AIR);
			}
		}
	}
}

//We need to make a parent class called game environment object.
//This will allow us to not have two functions by passing the parent object as the parameter.
bool CGame::AABB_Intersecting_Collision(PlayerMonkey& _player, RopeVineSegment _vine[])
{
	bool isNotColliding = false;
	for (int i = 0; i < NUMBER_OF_ROPEVINES; ++i) {
		isNotColliding = (_player.getMax_X() < _vine[i].getMin_X()) ||
			   (_vine[i].getMax_X() < _player.getMin_X()) ||
			   (_player.getMax_Y() < _vine[i].getMin_Y()) ||
			   (_vine[i].getMax_Y() < _player.getMin_Y());
		if (!isNotColliding) { //if monkey is colloding with a vine
			if (_player.getPlayerState() != ON_VINE) { //if player is entering the vine for the first time
				AudioManager::GetInstance()->playGrabVineSound();
				_player.setPlayerState(ON_VINE);
				_player.setPlayer_Y_Velocity(0);
				_player.setPlayerGrabbingVine(TRUE);
			}
			return true;

		}

	}

	return false;
}
bool CGame::AABB_Intersecting_Collision(PlayerMonkey& _player, Platform platform[])
{
	bool isNotColliding;
	for (int i = 0; i < NUMBER_OF_PLATFORMS; ++i) {
		isNotColliding = (_player.getMax_X() < platform[i].getMin_X()) ||
			(platform[i].getMax_X() < _player.getMin_X()) ||
			(_player.getMax_Y() < platform[i].getMin_Y()) ||
			(platform[i].getMax_Y() < _player.getMin_Y());

		if (!isNotColliding) {
			if (_player.getPlayerState() != ON_GROUND) { //first time colliding with ground

			}
			if (_player.getPlayerState() == ON_GROUND) { // if the player is already colliding with the ground then just return true
				return true;
			}
			if (_player.Previous_Lower_Y_Collision_Box_Position > platform[i].getMax_Y()) {

				_player.setPosition_Y(platform[i].getMax_Y() + platform[i].getTextureHeight()*2); //This will reset 
				_player.setPlayerState(ON_GROUND);
				_player.setPlayer_Y_Velocity(0);
				return true;
			}			
		}

	}

	return false;
}


bool CGame::AABB_Intersecting_Collision(PlayerMonkey& _player, Banana _banana[]) {
	bool isNotColliding;
	for (int i = 0; i < NUMBER_OF_BANANAS; ++i) {
		isNotColliding = (_player.getMax_X() < _banana[i].getMin_X()) ||
			(_banana[i].getMax_X() < _player.getMin_X()) ||
			(_player.getMax_Y() < _banana[i].getMin_Y()) ||
			(_banana[i].getMax_Y() < _player.getMin_Y());

		if (!isNotColliding) {

			if (_banana[i].getBananaDrawState()) { //if the banana is drawn...

				AudioManager::GetInstance()->playCollectedBananaSound();
				_player.player_points++;
				_banana[i].setBananaDrawState(FALSE);
				_banana[i].setCollectionTimeStamp(GetTickCount());
				_banana[i].setRandomRespawnTime();
				_banana[i].isBananaCollected = true;
			}
				return true;
		}

	}

	return false;

}


CGame *CGame::CreateInstance()
{
	if (sInstance == nullptr) { //if the instance hasn't been created then create it. Otherwise return the instance
		sInstance = new CGame();

	}
	return sInstance;
}
void CGame::shutdown()
{
	// DELETE INSTANCES OF INSTANTIATED OBJECTS WITHIN CLASS
}
void CGame::DestroyGame(void)
{

	delete InputManagerC::GetInstance();
	delete Renderer::GetInstance();
	delete BananaManager::GetInstance();
	delete ProjectileManager::GetInstance();
	delete AudioManager::GetInstance();
}

bool CGame::isGameWOn() {
	//player1.getPlayer
	return true;
}
