#pragma once

#include <stdlib.h>     /* srand, rand */

#define BANANA_DEFAULT_WIDTH 32
#define BANANA_DEFAULT_HEIGHT 32

#define MIN_RESPAWN_TIME 10
#define MAX_RESPAWN_TIME 30

#define MIN_RESPAWN_TIME_INIT 1
#define MAX_RESPAWN_TIME_INIT 15

class Banana {
private:
	unsigned int spritesheet;

	float pos_x;
	float pos_y;


	//This is what defines the bananas boundries the collision box verticies
	float UR_x, UR_y,// upper right x,y
		UL_x, UL_y,// upper left x,y
		LR_x, LR_y,// lower left x,y
		LL_x, LL_y;// lower right x,y


	//Need to determine what the actual width and height of the sprite.
	//Need to send the Renderer::DrawSprite() function already processed section of the sprite (width/height)
	float texture_width;
	float texture_height;

	//Destructor
	bool isBananaToBeDrawn;
	//Mutators
	void setVerticies();

	float timeStampWhenBananaWasCollected;
	float timeUntilSpawn;
	
protected:

public:

	bool isBananaCollected;


	//Default Constructor
	Banana();

	//Constructor
	Banana(float x, float y, bool _setBananaDrawState);


	//Accessors

	const float getPosition_X(){return pos_x;}
	const float getPosition_Y(){return pos_y;} 
	const unsigned int getSpriteSheetID(){return spritesheet;}
	const float getMax_X(){return UR_x;}
	const float getMax_Y(){return UR_y;}
	const float getMin_X(){return LL_x;}
	const float getMin_Y(){return LL_y;}
	const float getTextureWidth(){ return texture_width; }
	const float getTextureHeight(){ return texture_height; }
	const bool getBananaDrawState(){return isBananaToBeDrawn;}


	//Mutators

	void setSpriteSheetID(unsigned int id){spritesheet = id;}
	void setPosition_X(float _pos_x) { pos_x = _pos_x; }
	void setPosition_Y(float _pos_y) { pos_y = _pos_y; }
	void setBananaDrawState(bool state){isBananaToBeDrawn = state;}
	void setCollectionTimeStamp(float _time_stamp){timeStampWhenBananaWasCollected = _time_stamp;}
	void setRandomRespawnTime(){timeUntilSpawn = ((MIN_RESPAWN_TIME + rand()) % ((MAX_RESPAWN_TIME + 1) - MIN_RESPAWN_TIME)) * 1000.0f;}
	void SetInitialRandomSpawnTimeWhenGameStarts();




	//Functions
	void init();
	bool canBananaBeDrawn();
	void DrawSprite();

	void ResetBanana();


};