#pragma once

class Projectile
{
public:
	void init(double x, double y, double xVel, double yVel);
	void update();
	double getX();
	double getY();
	double getXVel();
	double getYVel();

private:
	// coordinates
	double x_;
	double y_;
	// velocities
	double xVel_;
	double yVel_;
};

