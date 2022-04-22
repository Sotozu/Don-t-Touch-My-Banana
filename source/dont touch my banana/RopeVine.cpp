#include "RopeVine.h"

RopeVine::RopeVine():
	pos_x(0),
	pos_y(0),
	total_segments(0), 
	vine(new RopeVineSegment[0])
{}

RopeVine::RopeVine(int num_segments) :
	pos_x(0),
	pos_y(0),
	total_segments(num_segments), 
	vine(new RopeVineSegment[num_segments]) 
{}

RopeVine::~RopeVine() {
	delete[]vine;
}
