#include "ProjectileManager.h"

#include <windows.h>						
#include <stdio.h>						
#include <stdarg.h>						
#include <math.h>						
#include <gl\gl.h>						
#include <gl\glu.h>						
#include "glut.h"

#include "SOIL.h"
#include "game.h"
#include "Program.h"
#include "Renderer.h"
#include "Platform.h"
#include "PlayerMonkey.h"
#include "AudioManager.h"

#include<iostream>
#include<string>

ProjectileManager* ProjectileManager::_Instance = NULL;

ProjectileManager* ProjectileManager::CreateInstance()
{
	if (_Instance != NULL) return _Instance;
	else _Instance = new ProjectileManager();

	return _Instance;
}

void ProjectileManager::Init()
{
	spritesheet = SOIL_load_OGL_texture("Content/shit.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void InitProjectile(PlayerMonkey& player, Projectile& poop)
{
	if (poop.isActive) return;

	poop.isActive = true;
	poop.pos_x = player.getPosition_X();
	poop.pos_y = player.getPosition_Y();
	poop.velocity_x = player.isLookingLeft() ? -SPEED_PROJECTILE : SPEED_PROJECTILE;
	if (g_keys->keyDown[player.controls->up]) poop.velocity_y = UP_VELOCITY;
	else poop.velocity_y = UP_VELOCITY / 2;
	poop.randomsprite = rand() % 9;
	AudioManager::GetInstance()->playFlingPoopSound();

}

void ProjectileManager::ThrowProjectile(PlayerMonkey& player)
{
	if (player.getPlayerNumber() == 0) InitProjectile(player, p1);
	if (player.getPlayerNumber() == 1) InitProjectile(player, p2);
}

void UpdateProjectile(Projectile& poop)
{
	if (poop.isActive)
	{
		poop.velocity_y -= GRAVITY_PROJECTILE * deltaTime;
		poop.pos_x += deltaTime * poop.velocity_x;
		poop.pos_y += deltaTime * poop.velocity_y;
	}
}

void ProjectileManager::Update()
{
	UpdateProjectile(p1);
	UpdateProjectile(p2);
}

void ProjectileManager::Draw()
{
	if (p1.isActive) Renderer::GetInstance()->DrawSprite(p1.pos_x, p1.pos_y, spritesheet, DEFAULT_SIZE_PROJECTILE, DEFAULT_SIZE_PROJECTILE, p1.randomsprite / 3, p1.randomsprite % 3, 3, 3);
	if (p2.isActive) Renderer::GetInstance()->DrawSprite(p2.pos_x, p2.pos_y, spritesheet, DEFAULT_SIZE_PROJECTILE, DEFAULT_SIZE_PROJECTILE, p2.randomsprite / 3, p2.randomsprite % 3, 3, 3);
}

bool AABBCollision(PlayerMonkey& player, Projectile& poop)
{
	if (!poop.isActive) return false;

	return !(
		(player.getMin_X() > poop.pos_x + DEFAULT_SIZE_PROJECTILE) ||
		(player.getMax_X() < poop.pos_x - DEFAULT_SIZE_PROJECTILE) ||
		(player.getMin_Y() > poop.pos_y + DEFAULT_SIZE_PROJECTILE) ||
		(player.getMax_Y() < poop.pos_y - DEFAULT_SIZE_PROJECTILE)
		);
}

void ProjectileManager::CheckCollision(PlayerMonkey& player)
{
	if (player.getPlayerNumber() == 0)
	{
		if(AABBCollision(player, p2))
		{
			AudioManager::GetInstance()->playerIsHitSound();
			p2.isActive = false;
			player.ProjectileHit();
		}
	}
	if (player.getPlayerNumber() == 1)
	{
		if(AABBCollision(player, p1))
		{
			AudioManager::GetInstance()->playerIsHitSound();
			p1.isActive = false;
			player.ProjectileHit();
		}
	}
}

bool AABBCollision(Platform& platform, Projectile& poop)
{
	if (!poop.isActive) return false;

	float min_x = poop.pos_x - DEFAULT_SIZE_PROJECTILE;
	float max_x = poop.pos_x + DEFAULT_SIZE_PROJECTILE;
	float min_y = poop.pos_y - DEFAULT_SIZE_PROJECTILE;
	float max_y = poop.pos_y + DEFAULT_SIZE_PROJECTILE;

	return !(
		(max_x < platform.getMin_X()) ||
		(min_x > platform.getMax_X()) ||
		(max_y < platform.getMin_Y()) ||
		(min_y > platform.getMax_Y())
		);
}

void ProjectileManager::CheckCollision(Platform platform[])
{
	for (int i = 0; i < NUMBER_OF_PLATFORMS; ++i) 
	{
		if (AABBCollision(platform[i], p1))
		{
			p1.isActive = false;
			break;
		}
	}

	for (int i = 0; i < NUMBER_OF_PLATFORMS; ++i)
	{
		if (AABBCollision(platform[i], p2))
		{
			p2.isActive = false;
			break;
		}
	}
}

void ProjectileManager::CheckCollision()
{
	if (p1.isActive) {
		if ((p1.pos_x < -g_window->init.width / 2) || (p1.pos_x > g_window->init.width / 2) || (p1.pos_y < -g_window->init.height / 2))
		{
			p1.isActive = false;
		}
	}

	if (p2.isActive) {
		if ((p2.pos_x < -g_window->init.width / 2) || (p2.pos_x > g_window->init.width / 2) || (p2.pos_y < -g_window->init.height / 2))
		{
			p2.isActive = false;
		}
	}
}