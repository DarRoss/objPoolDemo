/*
 * poolManager.h
 *
 * Creates pools and handles their functions.
 */

#pragma once

#include "genericPool.h"
#include "projectile.h"

using namespace std;

class PoolManager
{
public:
	PoolManager(int projectilesLen);
	Projectile* getProjectileAt(int index);
	void createProjectile(double x, double y, double xVel, double yVel, int lifetime);
	void update();
	Projectile* getFirstAvailablePjctl();
	Projectile* getOldestLivingPjctl();
	bool getPjctlUsageAt(int index);

private:
	GenericPool<Projectile>* projectilePool_;
};
