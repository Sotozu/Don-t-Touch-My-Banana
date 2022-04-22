#include "Banana.h"

#include <windows.h>						
#include <stdio.h>						
#include <stdarg.h>						
#include <math.h>						
#include <gl\gl.h>						
#include <gl\glu.h>						
#include "glut.h"

#include "SOIL.h"
#include "Program.h"
#include "Renderer.h"

//Default Constructor
Banana::Banana() :
	pos_x(0),
	pos_y(0),
	texture_width(BANANA_DEFAULT_WIDTH),
	texture_height(BANANA_DEFAULT_HEIGHT),
	isBananaToBeDrawn(FALSE),
	isBananaCollected(FALSE)
{
	init();
}

//Constructor
Banana::Banana(float x, float y, bool _setBananaDrawState) :
	pos_x(x),
	pos_y(y),
	texture_width(BANANA_DEFAULT_WIDTH),
	texture_height(BANANA_DEFAULT_HEIGHT),
	isBananaToBeDrawn(_setBananaDrawState),
	isBananaCollected(FALSE)

{
	init();
}

//Destructor


void Banana::init()
{
	spritesheet = SOIL_load_OGL_texture("Content/Banana.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	setVerticies(); // Will update the position of each vertici
	SetInitialRandomSpawnTimeWhenGameStarts();
}


void Banana::DrawSprite()
{
	if (isBananaToBeDrawn) {
		Renderer::GetInstance()->DrawSprite(pos_x, pos_y, spritesheet, texture_width, texture_height);
	}
}

void Banana::setVerticies() { // will also be called in the update because it can be used to "set" the new verticies after the player moves

	//Set lower left vertex
	LL_x = pos_x - texture_width;
	LL_y = pos_y - texture_height; //subtracting DEFAULT_HEIGHT because it makes the game mechanic of grabbing a little better

	//Set lower right vertex
	LR_x = pos_x + texture_width;
	LR_y = pos_y - texture_height;

	//Set upper left vertex
	UL_x = pos_x - texture_width;
	UL_y = pos_y + texture_height;

	//Set upper right vertex
	UR_x = pos_x + texture_width;
	UR_y = pos_y + texture_height;
}












bool Banana::canBananaBeDrawn() {

	float current_time = GetTickCount();
	if (isBananaToBeDrawn) {
		return true;
	}
	else if (!isBananaToBeDrawn && (current_time - timeStampWhenBananaWasCollected) > timeUntilSpawn) {
		isBananaToBeDrawn = true;
		return true;
	}
	return false;
}





void Banana::SetInitialRandomSpawnTimeWhenGameStarts() {
	float random_range_spawn_time = ((MIN_RESPAWN_TIME_INIT + rand()) % ((MAX_RESPAWN_TIME_INIT + 1) - MIN_RESPAWN_TIME_INIT)) * 1000.0f;
	timeUntilSpawn = random_range_spawn_time;
	timeStampWhenBananaWasCollected = GetTickCount() + random_range_spawn_time;

}


void Banana::ResetBanana() {
	float random_range_spawn_time = ((MIN_RESPAWN_TIME_INIT + rand()) % ((MAX_RESPAWN_TIME_INIT + 1) - MIN_RESPAWN_TIME_INIT)) * 1000.0f;
	timeUntilSpawn = random_range_spawn_time;
	timeStampWhenBananaWasCollected = GetTickCount() + random_range_spawn_time;
	isBananaToBeDrawn = false;
}
