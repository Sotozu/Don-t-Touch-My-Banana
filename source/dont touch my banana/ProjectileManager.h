#pragma once
#include "PlayerMonkey.h"
#include "Platform.h"

#define DEFAULT_SIZE_PROJECTILE 14.f
#define SPEED_PROJECTILE 500.f
#define UP_VELOCITY 1000.f
#define GRAVITY_PROJECTILE 2000.f

class Projectile
{
public:
	bool isActive{ false };
	float pos_x;
	float pos_y;
	float velocity_x;
	float velocity_y;
	int randomsprite;
};

class ProjectileManager
{
public:
	static ProjectileManager* CreateInstance();
	static ProjectileManager* GetInstance() { return _Instance; };

	void Init();

	void ThrowProjectile(PlayerMonkey& player);

	void Update();
	void CheckCollision(PlayerMonkey& player);
	void CheckCollision(Platform platform[]);
	void CheckCollision();
	void Draw();

private:
	static ProjectileManager* _Instance;

	unsigned int spritesheet;

	Projectile p1;
	Projectile p2;
};