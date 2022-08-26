#include "poolManager.h"

/*
 * Constructor
 */
PoolManager::PoolManager(int particlesLen)
{
	particlePool_ = new GenericPool<Particle>(particlesLen);
}

/*
 * Getter for the particle at a given index. 
 */
Particle* PoolManager::getParticleAt(int index)
{
	return particlePool_->getObjectAt(index);
}

/*
 * Create a particle with the given parameters.
 */
void PoolManager::createParticle(double x, double y, double xVel, double yVel, int lifetime)
{
	// take a particle from the particle pool and initialize it
	particlePool_->create(lifetime)->init(x, y, xVel, yVel);
}

/*
 * Update all pools within the manager.
 */
void PoolManager::update()
{
	particlePool_->update();
}

/*
 * Get the first dead particle that will turn into a living particle.
 */
Particle* PoolManager::getFirstAvailablePtcl()
{
	return particlePool_->getFirstAvailable();
}

/*
 * Get the first living particle that will turn into a dead particle. 
 */
Particle* PoolManager::getOldestLivingPtcl()
{
	return particlePool_->getOldestLiving();
}

/*
 * Get the status of the particle at a given index. 
 */
bool PoolManager::getPtclUsageAt(int index)
{
	return particlePool_->getUsageAt(index);
}
