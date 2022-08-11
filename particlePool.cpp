#include "particlePool.h"

/*
 * Constructor.
 * Param size: the length of the array.
 */
ParticlePool::ParticlePool(int size) : particles_(size_t(size))
{
	poolSize_ = size;

	// the first one is available
	firstAvailable_ = &particles_.at(0);

	// each particle points to the next
	for (int i = 0; i < poolSize_ - 1; i++) 
	{
		particles_[i].setNext(&particles_[i + 1]);
	}

	// the last one terminates the list
	particles_[poolSize_ - 1].setNext(nullptr);
}

/*
 * Bring a particle to life with given parameters.
 * Param x: the x coordinate of the particle. 
 * Param y: the y coordinate of the particle. 
 * Param xVel: the horizontal velocity of the particle. 
 * Param yVel: the vertical velocity of the particle. 
 */
void ParticlePool::create(double x, double y, double xVel, double yVel, int lifetime)
{
	// variable for storing the new living particle
	Particle* newParticle = nullptr;
	// check if all particles are living
	if (firstAvailable_ == nullptr)
	{
		// kill the oldest living particle to use as the new particle
		newParticle = queue_.front();
		queue_.pop_front();
	}
	// else there is an available particle
	else
	{
		// remove this particle from the availablility list
		newParticle = firstAvailable_;
		// the next particle in the dead list becomes the next available
		firstAvailable_ = newParticle->getNext();
	}

	// bring the new particle to life
	newParticle->init(x, y, xVel, yVel, lifetime);
	// add this particle to the living queue
	queue_.push_back(newParticle);
}

/* 
 * Move particles one by one. 
 * Add particles to the availablility list upon death. 
 */
void ParticlePool::animate()
{
	// loop through all particles
	for (int i = 0; i < poolSize_; i++) 
	{
		// move particle, then check if it has died
		if (particles_[i].animate())
		{
			// add this particle to the front of the availability list
			particles_[i].setNext(firstAvailable_);
			firstAvailable_ = &particles_[i];

			// assume that we have taken the oldest particle
			assert(firstAvailable_ == queue_.front());

			// remove this particle from the living queue
			queue_.pop_front();
		}
	}
}

/*
 * Getter for size of particle.
 */
int ParticlePool::getSize()
{
	return poolSize_;
}

/*
 * Retrieve the particle at the given index. 
 * Param index: the index to retrieve from.
 * Return: The particle at this index. 
 */
Particle* ParticlePool::getParticleAt(int index)
{
	Particle* output = nullptr;

	// check if the given index is within array bounds
	if(index < poolSize_)
	{
		output = &particles_[index];
	}

	return output;
}

/*
 * Getter for first available particle.
 */
Particle* ParticlePool::getFirstAvailable()
{
	return firstAvailable_;
}

/*
 * Getter for oldest living particle. 
 */
Particle* ParticlePool::getOldestAlive()
{
	return queue_.front();
}
