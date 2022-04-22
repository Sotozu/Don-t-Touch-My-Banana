#include "PlayerMonkey.h"

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
#include "ProjectileManager.h"
#include "AudioManager.h"

//Default Constructor
PlayerMonkey::PlayerMonkey() :
	player_number(0),
	pos_x(0),
	pos_y(0),
	player_state(ON_GROUND),
	controls(new KeysPressed(65, 66, 67, 68, 69)),
	texture_width(PLAYER_DEFAULT_WIDTH),
	texture_height(PLAYER_DEFAULT_HEIGHT),
	vineUpKeyPressed(FALSE),
	vineUpKeyReleased(FALSE),
	timeStampOfUpKeyPress(0.0f),
	timeStampOfUpKeyReleased(0.0f),
	grabbingVine(FALSE),
	player_points(0),
	performedPlatformJump(FALSE),
	performedVineJump(FALSE),
	canAirJump(TRUE)
{
	init();
}

//Constructor
PlayerMonkey::PlayerMonkey(int p_number, float x, float y, PlayerState p_state, KeysPressed* _controls) :
	player_number(p_number),
	pos_x(x),
	pos_y(y),
	player_state(p_state),
	controls(_controls),
	texture_width(PLAYER_DEFAULT_WIDTH),
	texture_height(PLAYER_DEFAULT_HEIGHT),
	vineUpKeyPressed(FALSE),
	vineUpKeyReleased(FALSE),
	timeStampOfUpKeyPress(0.0f),
	timeStampOfUpKeyReleased(0.0f),
	grabbingVine(FALSE),
	player_points(0),
	performedPlatformJump(FALSE),
	performedVineJump(FALSE),
	canAirJump(TRUE)
{
	init();
}
//Mutators
void PlayerMonkey::UpdatePlayer() {
	switch (player_state) {
	case ON_GROUND:
		canAirJump = true;
		updateOnGround();
		sprite_mode = 3;
		break;
	case ON_VINE:
		canAirJump = true;
		updateOnVine();
		sprite_mode = 1;
		break;
	case IN_AIR:
		updateInAir();
		sprite_mode = 2;
		break;
	case HIT:
		updateHit();
		sprite_mode = 0;
		break;
	default:
		break;
		
	}
	ThrowProjectile();

	if (pos_y < PLAYER_LOWERPLATFORM_Y) pos_y = PLAYER_LOWERPLATFORM_Y;
	if (pos_y > g_window->init.height / 2) pos_y = g_window->init.height / 2;
	if (pos_x < -g_window->init.width / 2)pos_x = -g_window->init.width / 2;
	if (pos_x > g_window->init.width / 2)pos_x = g_window->init.width / 2;

	Previous_Lower_Y_Collision_Box_Position = LL_y; //lower left y 
	setVerticies(); // Will update the position of each vertici
	if(player_state != IN_AIR)previouse_state = player_state;

}

void PlayerMonkey::init()
{
	if (player_number == 0)spritesheet = SOIL_load_OGL_texture("Content/monkey.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	else spritesheet = SOIL_load_OGL_texture("Content/monkey2.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	setVerticies(); // Will update the position of each vertici

	Previous_Lower_Y_Collision_Box_Position = LL_y; //lower left y 

	previouse_state = player_state;
}

void PlayerMonkey::updateOnGround()
{
	moveLeft();
	moveRight();
	jump();
}


void PlayerMonkey::updateOnVine() {
	//Check if player has jumped by pressing the upkey twice within a short range of time
	if (!grabbingVine) {
		applyGravity();
	}
	else {
		onVineJump();
	}
	moveUpVine();
	moveDownVine();
	updateJump();
	moveLeft();
	moveRight();
	


}

void PlayerMonkey::updateInAir() {
	airJump();
	moveLeft();
	moveRight();
	updateJump();
	applyGravity();
	//CheckIfTouchingGround();

}

void PlayerMonkey::updateHit()
{
	applyGravity();
	pos_y += velocity_y * deltaTime;

	hitTimer -= deltaTime;
	if (hitTimer < 0) player_state = ON_GROUND;
}

void PlayerMonkey::DrawSprite()
{
	if (sprite_mode == 1 || sprite_mode == 3) {}
	else if (sprite_mode == 2) sprite_itr = (velocity_y > 0) ? 0 : 1;
	else sprite_itr += deltaTime * PLAYER_SPRITE_CHANGERATE;

	if (sprite_itr >= 2) sprite_itr = 0;

	Renderer::GetInstance()->DrawSprite(pos_x, pos_y, spritesheet, texture_width, texture_height, sprite_itr, sprite_mode, 2, 4, 1.f, 1.f, lookingLeft);
}

void PlayerMonkey::setVerticies() { // will also be called in the update because it can be used to "set" the new verticies after the player moves
    
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

void PlayerMonkey::setPlayerState(PlayerState _state) {
	if (player_state == HIT) return;
	player_state = _state;
}


//Mutators - Player Movement
void PlayerMonkey::moveLeft() {
	if (g_keys->keyDown[controls->left])
	{
		pos_x -= (deltaTime * PLAYER_MOVE_SPEED);
		lookingLeft = true;

		sprite_itr += deltaTime * PLAYER_SPRITE_CHANGERATE;
	}
}
void PlayerMonkey::moveRight() {
	if (g_keys->keyDown[controls->right])
	{
		pos_x += (deltaTime * PLAYER_MOVE_SPEED);
		lookingLeft = false;

		sprite_itr += deltaTime * PLAYER_SPRITE_CHANGERATE;
	}
}
void PlayerMonkey::moveUp() {

}
void PlayerMonkey::moveDown() {

}
void PlayerMonkey::jump() {

	if (player_state == HIT) return;

	if (player_state == ON_GROUND && g_keys->keyDown[controls->up])
	{
		AudioManager::GetInstance()->playJumpSound();
		velocity_y = PLAYER_JUMP_HEIGHT;
		player_state = IN_AIR;
		pos_y += velocity_y * deltaTime;
		canAirJump = false;

	}
}

void PlayerMonkey::applyGravity() {
		velocity_y -= PLAYER_GRAVITY * deltaTime;
}


void PlayerMonkey::CheckIfTouchingGround() {
	if (player_state == HIT) return;
	if (pos_y < PLAYER_LOWERPLATFORM_Y) {
		pos_y = PLAYER_LOWERPLATFORM_Y;
		player_state = ON_GROUND;
		isOnGround = true;

	}
	isOnGround = false;
}

void PlayerMonkey::ThrowProjectile()
{
	if (player_state == HIT) return;

	if (isHitKeyPressed)
	{
		if (!g_keys->keyDown[controls->shit])
		{
			ProjectileManager::GetInstance()->ThrowProjectile(*this);
		}
	}

	isHitKeyPressed = g_keys->keyDown[controls->shit];

}


void PlayerMonkey::updateJump() {
	pos_y += velocity_y * deltaTime;
}


void PlayerMonkey::ProjectileHit()
{
	player_state = HIT;
	velocity_y = 0;
	hitTimer = PLAYER_HIT_WAIT;
}



void PlayerMonkey::moveUpVine() {
	if (player_state == ON_VINE && g_keys->keyDown[controls->up])
	{
		pos_y += (deltaTime * PLAYER_MOVE_SPEED);

		sprite_itr += deltaTime * PLAYER_SPRITE_CHANGERATE;
	}

}

void PlayerMonkey::moveDownVine() {
	if (player_state == ON_VINE && g_keys->keyDown[controls->down])
	{
		pos_y -= (deltaTime * PLAYER_MOVE_SPEED);

		sprite_itr += deltaTime * PLAYER_SPRITE_CHANGERATE;
	}


}

bool PlayerMonkey::onVineJump()
{


	if (player_state == ON_VINE && g_keys->keyDown[controls->up]) {
		//clicked the w button once
		if (vineUpKeyReleased == true && (GetTickCount() - timeStampOfUpKeyPress) < 120.0f) {
			//JUMP!
			canAirJump = false;
			velocity_y = PLAYER_JUMP_HEIGHT;
			pos_y += velocity_y * deltaTime;
			grabbingVine = FALSE;
			return true;
		}
		vineUpKeyPressed = true;
		vineUpKeyReleased = false;
	}

	if (player_state == ON_VINE && !g_keys->keyDown[controls->up] && vineUpKeyPressed) { //We only want to run this if statement ONCE.
		vineUpKeyPressed = false;
		vineUpKeyReleased = true;
		//At this point ***ONE*** UP KEY PRESS has been recorded
		//stamp the time
		timeStampOfUpKeyPress = GetTickCount();

	}
	return false;


}

void PlayerMonkey::airJump()
{
	if (!canAirJump)return;
	if (g_keys->keyDown[controls->up] && player_state==IN_AIR) {

		if (previouse_state == ON_GROUND)
		{
			AudioManager::GetInstance()->playJumpSound();
			velocity_y = PLAYER_JUMP_HEIGHT;
			player_state = IN_AIR;
			pos_y += velocity_y * deltaTime;
			canAirJump = false;
		}

		if (previouse_state == ON_VINE) {
			if (grabbingVine == true) { //This is not good code...
				AudioManager::GetInstance()->playJumpSound();
				velocity_y = PLAYER_JUMP_HEIGHT;
				player_state = IN_AIR;
				pos_y += velocity_y * deltaTime;
				canAirJump = false;
			}
		}
	}

}