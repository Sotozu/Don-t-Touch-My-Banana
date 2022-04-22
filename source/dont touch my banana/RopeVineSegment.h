#pragma once
//The vine.png image is 64x64 which is what this class uses as its sprite sheet

//The texture_width and texture_height will deteremine the overall amount of space that the texture takes up on the screen.
//There needs to be special consideration to the texture_height as it is a key feature of the rope/vine.

//In trying to keep up with best practice when initializing the constructor make the texture height a power of 2 size.
//Remember that the vine.png is a square of 64x64 so keep this in mind when creating a proportional image

#define ROPVINESEG_DEFAULT_WIDTH  16
#define ROPVINESEG_DEFAULT_HEIGHT  16

class RopeVineSegment
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

	float ropeVineSize;

	float texture_width;
	float texture_height;

	void setVerticies();

public:

	//Constructors
	RopeVineSegment();
	RopeVineSegment(float _rope_length, float _pos_x, float _pos_y); //This constructor is the best for quick implementation
	RopeVineSegment(float _rope_length, float _texture_width, float _texture_height, float _pos_x, float _pos_y);

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

