//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef POSITION_MAZE_H
#define POSITION_MAZE_H

#include "Direction.h"

class Position 
{
public:
	
	Position(int row, int col) 
	{
		this->row = row;
		this->col = col;
	}

	// added the following
	Position(const Position& p)
		: row(p.row), col(p.col)
	{

	}

	Position()
	{
		this->row = 0;
		this->col = 0;
	}

	bool operator ==( const Position &p ) const 
	{
		return ( (this->row == p.row) && (this->col == p.col));
	}

	// added the following
	bool operator !=(const Position& p) const
	{
		return !(*this == p);
	}

	// added the following
	Position& operator=(const Position& p) 
	{
		this->row = p.row;
		this->col = p.col;
		return *this;
	}

	Position move(Direction dir) 
	{
		Position tmp;

		switch(dir) 
		{
		case Direction::North:
			tmp = Position(row-1,col);
			break;

		case Direction::South:			
			tmp = Position(row+1,col);
			break;

		case Direction::East:
			tmp = Position(row,col+1);
			break;

		case Direction::West:
			tmp = Position(row,col-1);
			break;

		case Direction::Uninitialized:
		default:
			assert(false);
			break;
		}

		return tmp;
	}
		
	public: 
		// data
		int row;
		int col;
};

#endif

//--- End of File ------------------------------
