#include <windows.h>											// Header File For Windows
#include "BananaManager.h"
#include "Banana.h"

BananaManager* BananaManager::sInstance = NULL;

BananaManager* BananaManager::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new BananaManager();
	return sInstance;
}

//Default Constructor
BananaManager::BananaManager() : 
	numberOfBananas(NUMBER_OF_BANANAS), 
	bananaIsWaitingToSpawn(new bool[NUMBER_OF_BANANAS]{})
{

	for (int i = 0; i < NUMBER_OF_BANANAS; ++i) {
		bananaIsWaitingToSpawn[i] = true;
	}


	bananas = new Banana[NUMBER_OF_BANANAS]{
	Banana(0,-100, false),
	Banana(0,70, false),

	Banana(-150,0, false),
	Banana(-150,300, false),

	Banana(150,0, false),
	Banana(150,300, false),

	Banana(-310,50, false),

	Banana(300,50, false),

	Banana(-400,230, false),
	Banana(400,230, false),

	Banana(-500,-50, false),
	Banana(500,-50, false)
	};
}

void BananaManager::DrawBananas() {


	for (int i = 0; i < NUMBER_OF_BANANAS; ++i) {
		if (bananas[i].canBananaBeDrawn()) {
			bananas[i].DrawSprite();
		}
	}

}

const int BananaManager::getNumberOfBananas() {
	return numberOfBananas;
}

Banana* BananaManager::getBananas() {
	return bananas;
}

void BananaManager::ResetAllBananas()
{
	for (int i = 0; i < NUMBER_OF_BANANAS; ++i) {
		bananas[i].ResetBanana();
	}
}

