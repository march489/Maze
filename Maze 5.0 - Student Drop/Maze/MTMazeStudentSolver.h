//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MT_Maze_Student_Solver_H
#define MT_Maze_Student_Solver_H

#include <list>
#include <vector>

#include "TopDownSolver.h"
#include "BottomUpSolver.h"
#include "SharedData.h"

class MTMazeStudentSolver : public MazeSolver
{
public: 
	MTMazeStudentSolver(Maze *maze) 
	: MazeSolver( maze )
	{
		assert(pMaze);
	}

	std::vector<Direction>* Solve() override
	{
		SharedData data;

		BottomUpSolver mBUS(this->pMaze, data);
		mBUS.Launch();
		//while (!data.solution_found.load()) {}

		TopDownSolver mTDS(this->pMaze, data);
		mTDS.Launch();
		while (!data.bottomUpGlued.load() || !data.topDownGlued.load()) {}

		std::vector<Direction>* answer = new std::vector<Direction>();
		answer->reserve(VECTOR_RESERVE_SIZE);
		for (auto it = data.topDownSolution->begin(); it != data.topDownSolution->end(); it++)
		{
			answer->push_back(*it);
		}
		for (auto it = data.bottomUpSolution->begin(); it != data.bottomUpSolution->end(); it++)
		{
			answer->push_back(*it);
		}

		return answer;
	}
};

#endif

//--- End of File ------------------------------
