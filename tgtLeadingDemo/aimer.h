/*
 * Aimer.h
 *
 * Sits in one spot and launches projectiles at a target while calculating necessary deflection / lead. 
 */

#pragma once

#include <algorithm>
#include <math.h>
#include "poolManager.h"
#include <iostream>
#include <cstdlib>

class Aimer
{
private:
	// the rate of angle traverse per frame
	static constexpr double RADS_STEP = 0.05;
	// rightmost traverse angle
	static constexpr double MIN_RADS = 0;
	// leftmost traverse angle
	static constexpr double MAX_RADS = 3.14159;
	// number of frames between launching a projectile
	static const int MAX_COOLDOWN = 5;
	// number of frames in projectile lifetime
	static const int PJCTL_LIFETIME = 120;
	// distance in number of pixels to launch at
	static const int MAX_RANGE = 400;

	// position of the aimer in the world
	double x_;
	double y_;
	// angle that the aimer is currently aiming
	double currRads_;
	// angle that the aimer should be aiming (the necessary deflection)
	double desiredRads_;
	// the number of frames until the next projectile is launched
	int currCooldown_;
	// pointer to pool manager
	PoolManager* poolMgr_;
	// speed of the projectile in pixels per frame
	int pjctlSpeed_;

	// target information
	struct target_
	{
		// position of the target in the world
		double x;
		double y;
		// change in position of the target
		double deltaX;
		double deltaY;
		// distance to target
		double dist;
	} tgt;

public:
	Aimer(double x, double y, int pjctlSpeed, PoolManager* poolMgr);
	void update();
	void updateTargetPos(double x, double y);
	double getX();
	double getY();
	double getCurrRads();
};
