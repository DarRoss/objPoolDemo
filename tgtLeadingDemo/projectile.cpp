#include "projectile.h"

void Projectile::update()
{
	x_ += xVel_;
	y_ += yVel_;
}

void Projectile::init(double x, double y, double xVel, double yVel)
{
	x_ = x;
	y_ = y;
	xVel_ = xVel;
	yVel_ = yVel;
}

double Projectile::getX()
{
	return x_;
}

double Projectile::getY()
{
	return y_;
}

double Projectile::getXVel()
{
	return xVel_;
}


double Projectile::getYVel()
{
	return yVel_;
}

