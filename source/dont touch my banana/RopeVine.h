#pragma once
#include "RopeVineSegment.h"

class RopeVine
{
	//VARIABLES
	//Array of RopeVineSegment
	//Top RopeVineSegment
	//Bottom RopeVineSegment
	//Total Length


	//FUNCTIONS
	
private:
	int pos_x, pos_y;
	int total_segments; //Holds the to
	RopeVineSegment* vine; //we need to create varying sizes of these vines. That is why we will make it an array in the constructor
	//we need to know the dimensions of the vine image so that we can structure their positions on the screen relative to each other in a way that is seemless 
	

public:
	//Default Constructor
	RopeVine();
	//Constructor
	RopeVine(int num_segments); //This will determine the size of the rope
	~RopeVine();


};

