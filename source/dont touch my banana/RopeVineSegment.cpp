#include "RopeVineSegment.h"
#include <SOIL.h>
#include <Renderer.h>


//Defualt Constructor
RopeVineSegment::RopeVineSegment() :
	ropeVineSize(1),
	texture_width(ROPVINESEG_DEFAULT_WIDTH),
	texture_height(ROPVINESEG_DEFAULT_HEIGHT),
	pos_x(0),
	pos_y(0),
	spritesheet(0)
{
	init();
}

RopeVineSegment::RopeVineSegment(float _rope_size, float _pos_x, float _pos_y) :
	ropeVineSize(_rope_size),
	texture_width(ROPVINESEG_DEFAULT_WIDTH),
	texture_height(ROPVINESEG_DEFAULT_HEIGHT * _rope_size),
	pos_x(_pos_x), 
	pos_y(_pos_y), 
	spritesheet(0)
{
	init();
}

RopeVineSegment::RopeVineSegment(float _rope_size, float _texture_width, float _texture_height, float _pos_x, float _pos_y) :
	ropeVineSize(_rope_size),
	texture_width(_texture_width),
	texture_height(_texture_height),
	pos_x(_pos_x),
	pos_y(_pos_y),
	spritesheet(0)
{
	init();
}


const float RopeVineSegment::getPosition_X()
{
	return pos_x;
}
const float RopeVineSegment::getPosition_Y()
{
	return pos_y;
}
const unsigned int RopeVineSegment::getSpriteSheetID()
{
	return spritesheet;
}
void RopeVineSegment::init()
{
	spritesheet = SOIL_load_OGL_texture("Content/vine.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
	setVerticies();
}
void RopeVineSegment::DrawSprite()
{
	Renderer::GetInstance()->DrawSprite(pos_x, pos_y, spritesheet, texture_width, texture_height, 0, 0, 1, 1, ropeVineSize);
}
void RopeVineSegment::setVerticies() {

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

//Created for functional programming purposes. Used in AABB collision detection
const float RopeVineSegment::getMax_X()
{
	return UR_x; //upper right x
}
const float RopeVineSegment::getMax_Y()
{
	return UR_y; //upper right y
}
const float RopeVineSegment::getMin_X()
{
	return LL_x; //lower left x
}
const float RopeVineSegment::getMin_Y()
{
	return LL_y; //lower right x
}

const float RopeVineSegment::getTextureWidth() {
	return texture_width;
}
const float RopeVineSegment::getTextureHeight() {
	return texture_height;
}