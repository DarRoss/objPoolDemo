#include "poolManager.h"

/*
 * Constructor
 */
PoolManager::PoolManager(int projectilesLen)
{
	projectilePool_ = new GenericPool<Projectile>(projectilesLen);
}

/*
 * Getter for the projectile at a given index. 
 */
Projectile* PoolManager::getProjectileAt(int index)
{
	return projectilePool_->getObjectAt(index);
}

/*
 * Create a projectile with the given parameters.
 */
void PoolManager::createProjectile(double x, double y, double xVel, double yVel, int lifetime)
{
	// take a projectile from the projectile pool and initialize it
	projectilePool_->create(lifetime)->init(x, y, xVel, yVel);
}

/*
 * Update all pools within the manager.
 */
void PoolManager::update()
{
	projectilePool_->update();
}

/*
 * Get the first dead projectile that will turn into a living projectile.
 */
Projectile* PoolManager::getFirstAvailablePjctl()
{
	return projectilePool_->getFirstAvailable();
}

/*
 * Get the first living projectile that will turn into a dead projectile. 
 */
Projectile* PoolManager::getOldestLivingPjctl()
{
	return projectilePool_->getOldestLiving();
}

/*
 * Get the status of the projectile at a given index. 
 */
bool PoolManager::getPjctlUsageAt(int index)
{
	return projectilePool_->getUsageAt(index);
}
