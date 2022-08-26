#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "poolManager.h"

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
		poolMgr_ = new PoolManager(PTCL_LEN);
		// measure length for equidistant divisions
		divSize_ = ScreenWidth() / PTCL_LEN;
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
		poolMgr_->update();

		// check if the window is focused by the user
		if (IsFocused())
		{
			// check if left mouse button is held down
			if (GetMouse(0).bHeld)
			{
				// create particle at cursor with random velocity
				poolMgr_->createParticle(GetMouseX(), GetMouseY(), (float)rand()/(float)(RAND_MAX/4) - 2, (float)rand()/(float)(RAND_MAX/4) - 2, rand() % 100 + 150);
			}
		}


		// rendering
		
		// clear screen
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::VERY_DARK_GREY);

		// loop through all particles living or dead
		for(int i = 0; i < PTCL_LEN; i++) 
		{
			// temporarily store this particle
			tempParticle_ = poolMgr_->getParticleAt(i);

			// check if particle is living
			if (poolMgr_->getPtclUsageAt(i))
			{
				// draw the particle
				FillCircle(tempParticle_->getX(), tempParticle_->getY(), BALL_RADIUS, olc::YELLOW);
				// draw the indicator (green) for the particle
				FillCircle(divSize_ * i + divSize_ / 2, BALL_RADIUS * 2, BALL_RADIUS, olc::GREEN);
				// check if this is the oldest particle alive
				if (tempParticle_ == poolMgr_->getOldestLivingPtcl()) 
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
				if (tempParticle_ == poolMgr_->getFirstAvailablePtcl())
				{
					// highlight this indicator
					DrawCircle(divSize_ * i + divSize_ / 2, BALL_RADIUS * 2, BALL_RADIUS, olc::YELLOW);
				}
			}
		}

		return true;
	}

private:
	static const int PTCL_LEN = 64;
	static const int BALL_RADIUS = 3;
	static constexpr float TGT_FRAME_TIME = 1.0f / 60.0f; // Virtual FPS of 60fps
	PoolManager* poolMgr_;
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
