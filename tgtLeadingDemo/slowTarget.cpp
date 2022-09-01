#include "slowTarget.h"

/*
 * Constructor
 */
SlowTarget::SlowTarget(int speed) : speed_(speed)
{}

/*
 * Move towards a given pair of coordinates. 
 */
void SlowTarget::updatePos(double x, double y)
{
	// angle towards the given coordinates
	double rads = atan2(y - y_, x - x_);

	// update x coordinate of target
	if(x_ < x)
	{
		x_ = min(x, x_ + cos(rads) * speed_);
	}
	else if(x_ > x)
	{
		x_ = max(x, x_ + cos(rads) * speed_);
	}

	// update y coordinate of target
	if(y_ < y)
	{
		y_ = min(y, y_ + sin(rads) * speed_);
	}
	else if(y_ > y)
	{
		y_ = max(y, y_ + sin(rads) * speed_);
	}
}

/*
 * Getter for target's x coordinate
 */ 
double SlowTarget::getX()
{
	return x_;
}

/*
 * Getter for target's y coordinate
 */ 
double SlowTarget::getY()
{
	return y_;
}
