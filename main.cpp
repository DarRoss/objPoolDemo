#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "particlePool.h"

class Window : public olc::PixelGameEngine
{
public:
	Window()
	{
		sAppName = "Object Pool Demo";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		pool_ = new ParticlePool(POOL_SIZE);
		// measure length for equidistant divisions
		divSize_ = ScreenWidth() / POOL_SIZE;
		fAccumulatedTime_ = 0;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		fAccumulatedTime_ += fElapsedTime;
		if (fAccumulatedTime_ >= TGT_FRAME_TIME)
		{
			fAccumulatedTime_ -= TGT_FRAME_TIME;
			fElapsedTime = TGT_FRAME_TIME;
		}
		else
		{
			return true; // Don't do anything this frame
		}
        	// Continue as normal

		// processing
		pool_->animate();

		if (IsFocused())
		{
			// check if left mouse button is held down
			if (GetMouse(0).bHeld)
			{
				// create particle at cursor with random velocity
				pool_->create(GetMouseX(), GetMouseY(), (float)rand()/(float)(RAND_MAX/4) - 2, (float)rand()/(float)(RAND_MAX/4) - 2, LIFE_TIME);
			}
		}


		// rendering
		
		// clear screen
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::VERY_DARK_GREY);

		// loop through all particles living or dead
		for(int i = 0; i < POOL_SIZE; i++) 
		{
			// temporarily store this particle
			tempParticle_ = pool_->getParticleAt(i);

			// check if particle is living
			if (tempParticle_->inUse())
			{
				// draw the particle
				FillCircle(tempParticle_->getX(), tempParticle_->getY(), BALL_RADIUS, olc::YELLOW);
				// draw the indicator (green) for the particle
				FillCircle(divSize_ * i + divSize_ / 2, BALL_RADIUS * 2, BALL_RADIUS, olc::GREEN);
				// check if this is the oldest particle alive
				if (tempParticle_ == pool_->getOldestAlive()) 
				{
					// draw the indicator (magenta) for the particle
					DrawCircle(divSize_ * i + divSize_ / 2, BALL_RADIUS * 2, BALL_RADIUS, olc::BLUE);
				}
			} 
			// else particle is dead
			else
			{
				// draw the indicator (red) for the particle
				FillCircle(divSize_ * i + divSize_ / 2, BALL_RADIUS * 2, BALL_RADIUS, olc::DARK_RED);
				// check if this particle is the next to be used
				if (tempParticle_ == pool_->getFirstAvailable())
				{
					// highlight this indicator
					DrawCircle(divSize_ * i + divSize_ / 2, BALL_RADIUS * 2, BALL_RADIUS, olc::YELLOW);
				}
			}
		}

		return true;
	}

private:
	static const int POOL_SIZE = 64;
	static const int BALL_RADIUS = 3;
	static constexpr float TGT_FRAME_TIME = 1.0f / 60.0f; // Virtual FPS of 60fps
	static const int LIFE_TIME = 200;
	ParticlePool* pool_;
	Particle* tempParticle_;
	int divSize_;
	float fAccumulatedTime_;
};


int main()
{
	Window window;
	if (window.Construct(512, 512, 1, 1))
	{
		window.Start();
	}

	return 0;
}
