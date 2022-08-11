#include "particle.h"

Particle::Particle() : framesLeft_(0)
{}

bool Particle::animate()
{
	bool output = false;

	if (inUse()) 
	{
		framesLeft_--;
		state_.live.x += state_.live.xVel;
		state_.live.y += state_.live.yVel;

		output = framesLeft_ == 0;
	}

	return output;
}

void Particle::init(double x, double y, double xVel, double yVel, int lifetime)
{
	state_.live.x = x;
	state_.live.y = y;
	state_.live.xVel = xVel;
	state_.live.yVel = yVel;
	framesLeft_ = lifetime;
}

bool Particle::inUse() const
{
	return framesLeft_ > 0;
}

Particle* Particle::getNext()
{
	return state_.next;
}

void Particle::setNext(Particle* newParticle)
{
	state_.next = newParticle;
}

double Particle::getX()
{
	return state_.live.x;
}

double Particle::getY()
{
	return state_.live.y;
}

double Particle::getXVel()
{
	return state_.live.xVel;
}


double Particle::getYVel()
{
	return state_.live.yVel;
}

