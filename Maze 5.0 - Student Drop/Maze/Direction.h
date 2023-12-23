//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DIRECTION_MAZE_H
#define DIRECTION_MAZE_H

enum class Direction
{
	North, 
	East, 
	South, 
	West,
	Uninitialized
};

Direction reverseDir( Direction dir );


class DirectionHelper
{
public:
	static const char *getString( Direction dir );

};

#endif

//--- End of File ------------------------------
