#pragma once

class Particle
{
public:
	Particle();
	void init(double x, double y, double xVel, double yVel, int lifetime);
	bool animate();
	bool inUse() const; 
	Particle* getNext();
	void setNext(Particle* newParticle);
	double getX();
	double getY();
	double getXVel();
	double getYVel();

private:
	int framesLeft_;

	union
	{
		// state for when it's in use
		struct
		{
			// coordinates
			double x;
			double y;
			// velocities
			double xVel;
			double yVel;
		} live;

		// state for when it's available
		Particle* next;
	} state_;
};
