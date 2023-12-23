//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MAZE_H
#define MAZE_H

#include <atomic>
#include <list>
#include <memory>

#include "Position.h"
#include "Direction.h"
#include "Choice.h"

#define DEBUG_PRINT 0

// Maze cells are (row,col) starting at (0,0)
// Linear storage of integers 0 to (width*height - 1)
// Upper Upper corner (0,0) or index 0
// Lower Left corner (width-1, height-1) or (width*height - 1)

class Maze
{
public:

	Maze();
	Maze( int _width, int _height);
	~Maze();

	void Load( const char * const fileName );

	ListDirection getMoves(Position pos);
	bool canMove( Position pos, Direction dir );
	bool checkSolution( std::vector<Direction> &soln );

	Position getStart();
	Position getEnd() ;;

	void setEast(Position pos);
	void setSouth(Position pos);
	unsigned int getCell(Position pos);
	void setCell(Position pos, unsigned int val);

// data:
	std::atomic_uint *poMazeData;
	int height;
	int width;
	int solvable;
};

#endif

//--- End of File ------------------------------
