#pragma once

#define PLATFORM_DEFAULT_WIDTH  16
#define PLATFORM_DEFAULT_HEIGHT  16

class Platform
{
private:

	unsigned int spritesheet;

	float pos_x;
	float pos_y;

	//This is what defines the rope boundries
	float UR_x, UR_y,// upper right x,y
		UL_x, UL_y,// upper left x,y
		LR_x, LR_y,// lower left x,y
		LL_x, LL_y;// lower right x,y

	float platformSize;

	float texture_width;
	float texture_height;

	void setVerticies();

public:

	//Constructors
	Platform();
	Platform(float _platform_size, float _pos_x, float _pos_y); //This constructor is the best for quick implementation
	Platform(float _platform_size, float _texture_width, float _texture_height, float _pos_x, float _pos_y);

	//Accessors
	const float getPosition_X();
	const float getPosition_Y();
	const unsigned int getSpriteSheetID();

	//Mutators
	void init();
	void DrawSprite();

	const float getMax_X();
	const float getMax_Y();
	const float getMin_X();
	const float getMin_Y();

	const float getTextureWidth();
	const float getTextureHeight();

};



