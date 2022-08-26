#include "particle.h"

void Particle::update()
{
	x_ += xVel_;
	y_ += yVel_;
}

void Particle::init(double x, double y, double xVel, double yVel)
{
	x_ = x;
	y_ = y;
	xVel_ = xVel;
	yVel_ = yVel;
}

double Particle::getX()
{
	return x_;
}

double Particle::getY()
{
	return y_;
}

double Particle::getXVel()
{
	return xVel_;
}


double Particle::getYVel()
{
	return yVel_;
}

