#pragma once

#include "particle.h"
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

class ParticlePool
{
public:
	ParticlePool(int size);
	void create(double x, double y, double xVel, double yVel, int lifetime);
	void animate();
	int getSize();
	Particle* getParticleAt(int index);
	Particle* getFirstAvailable();
	Particle* getOldestAlive();

private:
	int poolSize_;
	// vector of particles
	vector<Particle> particles_;
	// pointer to the first available dead particle
	Particle* firstAvailable_;
	// deque of living particles
	deque<Particle*> queue_;
};

