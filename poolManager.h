#pragma once

#include "genericPool.h"
#include "particle.h"

using namespace std;

class PoolManager
{
public:
	PoolManager(int particlesLen);
	Particle* getParticleAt(int index);
	void createParticle(double x, double y, double xVel, double yVel, int lifetime);
	void update();
	Particle* getFirstAvailablePtcl();
	Particle* getOldestLivingPtcl();
	bool getPtclUsageAt(int index);

private:
	GenericPool<Particle>* particlePool_;
};
