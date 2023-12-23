#ifndef TOP_DOWN_SOLVER
#define TOP_DOWN_SOLVER

#include "Direction.h"
#include "SolutionFoundSkipException.h"

class TopDownSolver : public MazeSolver
{
public:
	// Constructors
	TopDownSolver(Maze*, SharedData&);

	TopDownSolver() = delete;
	TopDownSolver(const TopDownSolver&) = delete;
	TopDownSolver& operator=(const TopDownSolver&) = delete;
	virtual ~TopDownSolver();

	// Thread mgmt
	void Launch();
	void operator()();

	std::vector<Direction>* Solve() override;

private:
	unsigned int StampGround(Position&, Direction);
	unsigned int StampGround(Choice&);
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


#endif // !TOP_DOWN_SOLVER_H

