#include "aimer.h"

/*
 * Constructor
 */
Aimer::Aimer(double x, double y, int pjctlSpeed, PoolManager* poolMgr) : x_(x), y_(y), pjctlSpeed_(pjctlSpeed), poolMgr_(poolMgr)
{}

/*
 * Update the position of the target, as well as change in position.
 */
void Aimer::updateTargetPos(double x, double y)
{
	// update change in position
	tgt.deltaX = x - tgt.x;
	tgt.deltaY = y - tgt.y;

	// update target position
	tgt.x = x;
	tgt.y = y;

}

/*
 * Perform deflection calculations, aim traverse and launching of the projectile.
 */
void Aimer::update()
{
	// update distance to target
	tgt.dist = hypot(tgt.x - x_, tgt.y - y_);
	// udate desired radians (the deflection/lead of the target)
	desiredRads_ = -atan2(tgt.y - y_ + tgt.deltaY * tgt.dist / pjctlSpeed_, tgt.x - x_ + tgt.deltaX * tgt.dist / pjctlSpeed_);

	// move the aimer
	if(currRads_ < desiredRads_)
	{
		currRads_ = min(currRads_ + RADS_STEP, min(desiredRads_, MAX_RADS));
	}
	else if (currRads_ > desiredRads_)
	{
		currRads_ = max(currRads_ - RADS_STEP, max(desiredRads_, MIN_RADS));
	}
	// check if aimer is at correct angle
	if(currRads_ == desiredRads_)
	{
		// check if aimer is ready to launch
		if(currCooldown_ == 0 && tgt.dist <= MAX_RANGE)
		{
			// launch a projectile
			poolMgr_->createProjectile(x_, y_, cos(currRads_) * pjctlSpeed_, -sin(currRads_) * pjctlSpeed_, PJCTL_LIFETIME);
			// start cooldown period of launcher
			currCooldown_ = MAX_COOLDOWN + 1;
		}
	}

	// reduce cooldown period of launcher
	currCooldown_ = max(currCooldown_ - 1, 0);
}

/*
 * Getter for x coordinate of aimer.
 */
double Aimer::getX()
{
	return x_;
}

/*
 * Getter for y coordinate of aimer.
 */
double Aimer::getY()
{
	return y_;
}

/*
 * Getter for current angle/radians of aimer.
 */
double Aimer::getCurrRads()
{
	return currRads_;
}
