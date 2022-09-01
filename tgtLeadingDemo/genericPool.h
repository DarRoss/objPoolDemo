/*
 * genericPool.h
 *
 * An object pool capable of pooling any generic object. 
 * Note: all template function definitions have been written in genericPool.h to prevent linker errors. 
 */

#pragma once

#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

template <typename T>
class GenericPool
{
private:
	// struct to be placed in the pool
	struct poolItem 
	{
		// the object itself
		T object;
		// true if the object is in use
		bool inUse;
		// points to the next available pool item
		poolItem* next;
		// number of frames the object will live
		unsigned int lifetime;

		poolItem() : inUse(false), next(nullptr), lifetime(0) {}
	};

	// struct to be placed in the living queue
	struct queueItem 
	{
		// pointer to the pool item
		struct poolItem* poolItemPtr;
		// expiration time of the object (measured in frames)
		unsigned long expiry;
		// constructor
		queueItem(struct poolItem* ptr, unsigned long exp)
		{
			poolItemPtr = ptr;
			expiry = exp;
		}
		
		// comparison operator
		bool operator < (const queueItem b) const 
		{
		       return expiry < b.expiry;
		}
	};

	// size of the pool
	int poolSize_;
	// vector of objects
	vector<struct poolItem> pool_;
	// pointer to the first available (dead) pool item
	struct poolItem* firstAvailable_;
	// internal clock for keeping track of frames
	unsigned long clock_;
	// queue of living objects + expiration times
	deque<struct queueItem> livingQueue_;

	/*
	 * Insert the object to the living queue. 
	 * Param object: the object to insert. 
	 * Param expiry: the expiration time of the object.
	 */
	void queueInsert(poolItem* object, unsigned long expiry)
	{
		// create a queueItem consisting of parameters
		queueItem item = queueItem(object, expiry);
		// perform a sorted insert to the living queue
		livingQueue_.insert(upper_bound(livingQueue_.begin(), livingQueue_.end(), item), item);
	}

public:

	/*
	 * Constructor.
	 * Param size: the size of the pool.
	 */
	GenericPool(int size) : pool_(size_t(size)), clock_(0), poolSize_(size)
	{
		// the first object is the first available
		firstAvailable_ = &pool_.at(0);
	
		// each object points to the next
		for (int i = 0; i < poolSize_ - 1; i++) 
		{
			pool_.at(i).next = &pool_.at(i + 1);
		}
	
		// the last one terminates the list
		pool_.at(poolSize_ - 1).next = nullptr;
	}

	T* create(unsigned int lifetime)
	{
		// variable for storing the new living pool item
		poolItem* newPoolItem = nullptr;
		// check if all objects are living
		if (firstAvailable_ == nullptr)
		{
			// kill the oldest living object to use as the new object
			newPoolItem = livingQueue_.front().poolItemPtr;
			livingQueue_.pop_front();
		}
		// else there is an available object
		else
		{
			// remove this object from the availablility list
			newPoolItem = firstAvailable_;
			// the next object in the dead list becomes the first available
			firstAvailable_ = newPoolItem->next;
		}
	
		// object is now in use
		newPoolItem->inUse = true;

		// object lifetime updated
		newPoolItem->lifetime = lifetime;
	
		// add this particle to the living queue
		queueInsert(newPoolItem, clock_ + lifetime);
		
		return &newPoolItem->object;
	}
	
	
	/* 
	 * Animate objects one by one. 
	 * Add object to the availablility list upon death. 
	 * Called once per update/frame.
	 */
	void update()
	{
		// loop through all objects
		for (int i = 0; i < poolSize_; i++) 
		{
			// check if object is active
			if(pool_.at(i).inUse)
			{
				// update object
				pool_.at(i).object.update();
				// comment above line if update() is not present
	
				// reduce lifetime and check if object has died
				if(--pool_.at(i).lifetime == 0)
				{
					// object is no longer in use
					pool_.at(i).inUse = false;
					
					// add this object to the front of the availability list
					pool_.at(i).next = firstAvailable_;
					firstAvailable_ = &pool_.at(i);
			
					// remove this object from the living queue
					livingQueue_.pop_front();
				}
			}
		}
	
		// increment internal clock (assuming that animate() runs once per frame)
		++clock_;
	}
	
	/*
	 * Getter for size of particle.
	 */
	int getSize()
	{
		return poolSize_;
	}
	
	/*
	 * Retrieve the particle at the given index. 
	 * Param index: the index to retrieve from.
	 * Return: The object at this index. 
	 */
	T* getObjectAt(int index)
	{
		T* output = nullptr;
	
		// check if the given index is within array bounds
		if(index >= 0 && index < poolSize_)
		{
			output = &pool_.at(index).object;
		}
	
		return output;
	}
	
	/*
	 * Getter for first available object.
	 */
	T* getFirstAvailable()
	{
		return &firstAvailable_->object;
	}
	
	/*
	 * Getter for oldest living object. 
	 */
	T* getOldestLiving()
	{
		return &livingQueue_.front().poolItemPtr->object;
	}
	
	/*
	 * Retrieve the particle at the given index. 
	 * Param index: the index to retrieve from.
	 * Return: The object at this index. 
	 */
	bool getUsageAt(int index)
	{
		bool output = false;
	
		// check if the given index is within array bounds
		if(index >= 0 && index < poolSize_)
		{
			output = pool_.at(index).inUse;
		}
	
		return output;
	}
};

