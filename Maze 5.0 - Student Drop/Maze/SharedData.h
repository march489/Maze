#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include "Direction.h"

class Position;

struct SharedData
{
	// constructor
	SharedData()
		: collision_point(nullptr),
		topDownSolution(new std::deque<Direction>()),
		bottomUpSolution(new std::deque<Direction>()),
		threads_collided(false),
		solution_found(false),
		topDownGlued(false),
		bottomUpGlued(false)
	{
		assert(topDownSolution);
		assert(bottomUpSolution);
	}

	~SharedData()
	{
		delete topDownSolution;
		topDownSolution = nullptr;

		delete bottomUpSolution;
		bottomUpSolution = nullptr;

		if (collision_point)
		{
			delete collision_point;
			collision_point.store(nullptr);
		}
	}

	// data
	std::atomic<Position*> collision_point;
	std::deque<Direction>* topDownSolution;
	std::deque<Direction>* bottomUpSolution;
	std::atomic_bool threads_collided;
	std::atomic_bool solution_found;
	std::atomic_bool topDownGlued;
	std::atomic_bool bottomUpGlued;
};

#endif // !SHARED_DATA_H