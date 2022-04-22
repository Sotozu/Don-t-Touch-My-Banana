#pragma once
#include "Banana.h"
#define NUMBER_OF_BANANAS 12


class BananaManager
{


private:
	Banana* bananas;
	int numberOfBananas;
	bool* bananaIsWaitingToSpawn;
	static BananaManager* sInstance;

public:
	static BananaManager* CreateInstance();
	static BananaManager* GetInstance() { return sInstance; };
	void init() {};
	void update() {};

	BananaManager();

	//Functions
	void DrawBananas();

	//Accessors
	const int getNumberOfBananas();
	Banana* getBananas();

	void ResetAllBananas();

	//Mutators

};

