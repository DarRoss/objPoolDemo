#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "poolManager.h"
#include "aimer.h"
#include "slowTarget.h"

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
		poolMgr_ = new PoolManager(PJCTL_LEN);
		aimer_ = new Aimer(ScreenWidth() / 2, ScreenHeight(), PJCTL_SPEED, poolMgr_);
		tgt_ = new SlowTarget(TGT_SPEED);
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

		// calculations

		// update target position
		tgt_->updatePos(GetMouseX(), GetMouseY());
		// send target postion to aimer
		aimer_->updateTargetPos(tgt_->getX(), tgt_->getY());
		// update aimer
		aimer_->update();
		// update pool manager
		poolMgr_->update();

		// rendering
		
		// clear screen
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::VERY_DARK_GREY);
		// draw launching range of aimer
		DrawCircle(ScreenWidth()/2, ScreenHeight(), 400, olc::DARK_RED);
		// draw target
		FillCircle(tgt_->getX(), tgt_->getY(), 5, olc::GREEN);

		// loop through all projectiles living or dead
		for(int i = 0; i < PJCTL_LEN; i++) 
		{
			// check if projectile is living
			if (poolMgr_->getPjctlUsageAt(i))
			{
				// temporarily store this projectile
				tempProjectile_ = poolMgr_->getProjectileAt(i);
			
				// draw the projectile
				DrawLine(tempProjectile_->getX(), tempProjectile_->getY(), tempProjectile_->getX() - tempProjectile_->getXVel() * 3, tempProjectile_->getY() - tempProjectile_->getYVel() * 3, olc::RED);
				FillCircle(tempProjectile_->getX(), tempProjectile_->getY(), 1, olc::YELLOW);
			} 
		}

		// draw the aimer
		DrawLine(aimer_->getX(), aimer_->getY(), aimer_->getX() + cos(aimer_->getCurrRads()) * 20, aimer_->getY() - sin(aimer_->getCurrRads()) * 20, olc::WHITE);

		return true;
	}

private:
	// number of projectiles to use in the pool
	static const int PJCTL_LEN = 16;
	// speed at which projectiles will move
	static const int PJCTL_SPEED = 10;
	// the ideal time between frames
	static constexpr float TGT_FRAME_TIME = 1.0f / 60.0f; // Virtual FPS of 60fps
	// speed at which the target will move
	static const int TGT_SPEED = 3;
	// class instances
	PoolManager* poolMgr_;
	Projectile* tempProjectile_;
	Aimer* aimer_;
	SlowTarget* tgt_;
	// accumulator for time between frames
	float fAccumulatedTime_;
};


int main()
{
	Window window;
	if (window.Construct(768, 512, 1, 1))
	{
		window.Start();
	}

	return 0;
}
