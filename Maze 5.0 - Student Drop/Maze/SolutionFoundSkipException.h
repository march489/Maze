#ifndef SOLUTION_FOUND_SKIP_EXCEPTION_H
#define SOLUTION_FOUND_SKIP_EXCEPTION_H

// Algorithm & Maze generation - refactored and modified from material on the internet
//    Influenced by many different solvers and maze categories
//    Purpose of the maze is to create a concurrent problem set for C++ concurrency class
//    Maze solving algorithm and generators were derived from University of Maryland - Java Development

#include <exception>
#include "MazeSolver.h"
#include "Position.h"
#include "Choice.h"
#include "SharedData.h"

#define VECTOR_RESERVE_SIZE 400000

// stamps
#define BOTTOM_SOLVER_STAMP 0x4
#define TOP_SOLVER_STAMP 0x8

#define BOTTOM_FROM_SOUTH 0x80
#define BOTTOM_FROM_EAST 0x40
#define BOTTOM_FROM_WEST 0x20
#define BOTTOM_FROM_NORTH 0x10

#define TOP_FROM_SOUTH 0x800
#define TOP_FROM_EAST 0x400
#define TOP_FROM_WEST 0x200
#define TOP_FROM_NORTH 0x100

class Student_SolutionFoundSkip : public std::exception
{
public:

	Student_SolutionFoundSkip(Position _pos, Direction _from, SharedData& _rdata)
		: pos(_pos), from(_from), data(_rdata)
	{

	}

	Position pos;
	Direction from;
	SharedData& data;
};


#endif