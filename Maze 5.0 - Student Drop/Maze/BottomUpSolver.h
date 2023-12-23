#ifndef BOTTOM_UP_SOLVER_H
#define BOTTOM_UP_SOLVER_H

#include "Direction.h"
#include "SolutionFoundSkipException.h"


class BottomUpSolver : public MazeSolver
{
public:
	// Constructors
	BottomUpSolver(Maze*, SharedData&);

	BottomUpSolver() = delete;
	BottomUpSolver(const BottomUpSolver&) = delete;
	BottomUpSolver& operator=(const BottomUpSolver&) = delete;
	virtual ~BottomUpSolver();

	// Thread mgmt
	void Launch();
	void operator()();

	std::vector<Direction>* Solve() override;

//private:
	unsigned int StampGround(Position&, Direction);
	unsigned int StampGround(Choice);
	Choice follow(Position, Direction);
	Choice firstChoice(Position);
	Direction readPaint(const Position) const;

private:
	std::thread mThread;
	SharedData& data;

public:
	std::atomic_bool done;
private:
	Position source;
	Position target;

};


#endif // !BOTTOM_UP_SOLVER_H
