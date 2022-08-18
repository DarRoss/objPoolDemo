#pragma once

#include "particle.h"
#include <vector>
#include <deque>
#include <algorithm>

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
	// pointer to the first available (dead) particle
	Particle* firstAvailable_;
	// internal clock for keeping track of frames
	unsigned long clock_;
	// struct to be placed in the living queue
	struct queueItem {
		// the pointer to the particle
		Particle* particlePtr;
		// the expiration time of the particle (measured in frames)
		unsigned long expiry;
		// constructor
		queueItem(Particle* ptr, unsigned long exp)
		{
			particlePtr = ptr;
			expiry = exp;
		}
		
		// comparison operator
		bool operator < (const queueItem b) const 
		{
		       return expiry < b.expiry;
		}
	};
	// queue of living particles + expiration times
	deque<queueItem> queue_;

	void queueInsert(Particle* particle, unsigned long expiry);
};

