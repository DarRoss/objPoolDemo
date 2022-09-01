/*
 * SlowTarget.h
 * 
 * A target that moves at a capped speed. 
 */

#pragma once

#include <algorithm>
#include <math.h>

using namespace std;

class SlowTarget
{
private:
	// the speed to move at
	int speed_;
	// the coordinates of the target
	double x_;
	double y_;
public:
	SlowTarget(int speed);
	void updatePos(double x, double y);
	double getX();
	double getY();
};
