#include "TopDownSolver.h"

TopDownSolver::TopDownSolver(Maze* _pMaze, SharedData& rData)
	:MazeSolver(_pMaze),
	mThread(),
	data(rData),
	done(false),
	source(pMaze->getStart()),
	target(pMaze->getEnd()) // <-- UPDATE
{
}

TopDownSolver::~TopDownSolver()
{
	if (this->mThread.joinable())
	{
		this->mThread.join();
	}
}

void TopDownSolver::Launch()
{
	if (!this->mThread.joinable())
	{
		this->mThread = std::thread(std::ref(*this));
	}
	else
	{
		assert(false);
	}
}

std::vector<Direction>* TopDownSolver::Solve()
{
	std::vector<Choice> pChoiceStack;
	pChoiceStack.reserve(VECTOR_RESERVE_SIZE);  // Optimized allocations...

	Choice ch;
	try
	{
		pChoiceStack.push_back(firstChoice(this->source)); // <-- changed for bottom up

		while (!(pChoiceStack.size() == 0))
		{
			ch = pChoiceStack.back();

			if (data.threads_collided.load())
			{
				throw Student_SolutionFoundSkip(ch.at, ch.from, data);
			}

			StampGround(ch); // <-- testing if stamp works
			if (ch.isDeadend())
			{
				// backtrack.
				pChoiceStack.pop_back();

				if (!(pChoiceStack.size() == 0))
				{
					pChoiceStack.back().pChoices.pop_front();
				}

				continue;
			}

			//#include "MazeSolver.h"
			pChoiceStack.push_back(follow(ch.at, ch.pChoices.front()));

		}
		// No solution found.
		return 0;
	}
	catch (Student_SolutionFoundSkip e)
	{
		while ( !e.data.collision_point.load() )
		{
			std::this_thread::sleep_for(100ms);
		}

		Position curr = *(e.data.collision_point.load());

		while (curr != this->source)
		{
			Direction dir = readPaint(curr);
			assert(pMaze->canMove(curr, dir)); // <-- Remove when working
			e.data.topDownSolution->push_front(reverseDir(dir));
			curr = curr.move(dir);
		}

		e.data.topDownGlued.store(true);

		return nullptr;
	}
}

void TopDownSolver::operator()()
{
	this->Solve();
}

unsigned int TopDownSolver::StampGround(Position& pos, Direction dir)
{
	unsigned int stamp = TOP_SOLVER_STAMP;
	switch (dir)
	{
		case Direction::South:
			stamp |= TOP_FROM_SOUTH;
			break;

		case Direction::East:
			stamp |= TOP_FROM_EAST;
			break;

		case Direction::West:
			stamp |= TOP_FROM_WEST;
			break;

		case Direction::North:
			stamp |= TOP_FROM_NORTH;
			break;

		case Direction::Uninitialized:
		default:
			// do nothing
			break;
	}

	std::atomic_uint& cell = 
		pMaze->poMazeData[pos.row * pMaze->width + pos.col];
	return cell.fetch_or(stamp);
}

unsigned int TopDownSolver::StampGround(Choice& ch)
{
	return StampGround(ch.at, ch.from);
}

Choice TopDownSolver::follow(Position at, Direction dir) 
{
	ListDirection Choices;
	Direction go_to = dir;
	Direction came_from = reverseDir(dir);
	at = at.move(go_to);

	do
	{
		if (data.collision_point.load())
		{
			throw Student_SolutionFoundSkip(at, reverseDir(go_to), data);
			break;
		}

		unsigned int priorStamp = StampGround(at, came_from) & BOTTOM_SOLVER_STAMP;
		if (priorStamp)
		{
			// collision detected!
			Position* pos = new Position(at.row, at.col);
			Position* nullpos = nullptr;
			data.collision_point.compare_exchange_strong(nullpos, pos);
			data.threads_collided.store(true);

			//delete pos;
			//pos = nullptr;
			//throw Student_SolutionFoundSkip(at, reverseDir(go_to), data);
			break;
		}

		if (at == this->source)
		{
			assert(false);
			//throw Student_SolutionFoundSkip(at, reverseDir(go_to), data);

		}

		if (at == target) // <-- TARGET
		{
			Position* pos = new Position(target.row, target.col);
			Position* nullpos = nullptr;
			data.collision_point.compare_exchange_strong(nullpos, pos);
			data.threads_collided.store(true);

			//delete pos;
			//pos = nullptr;

			//throw Student_SolutionFoundSkip(at, reverseDir(go_to), data);
			break;
		}

		Choices = pMaze->getMoves(at);
		Choices.remove(came_from);

		if (Choices.size() == 1)
		{
			go_to = Choices.begin();
			at = at.move(go_to);
			came_from = reverseDir(go_to);
		}

	} while (Choices.size() == 1);

	Choice pRet(at, came_from, Choices);

	return pRet;
}

Choice TopDownSolver::firstChoice(Position pos)
{
	ListDirection Moves = pMaze->getMoves(pos);

	if (Moves.size() == 1)
	{
		Direction tmp = Moves.begin();
		return follow(pos, tmp);
	}
	else
	{
		Choice p(pos, Direction::Uninitialized, Moves);
		return p;
	}
}

Direction TopDownSolver::readPaint(const Position p) const
{
	unsigned int cell = pMaze->poMazeData[p.row * pMaze->width + p.col].load();
	unsigned int directionMask = 0xf00;
	
	Direction retraceDirection = Direction::Uninitialized;
	cell &= directionMask;
	switch (cell)
	{
		case TOP_FROM_SOUTH:
			retraceDirection = Direction::South;
			break;
		case TOP_FROM_EAST:
			retraceDirection = Direction::East;
			break;
		case TOP_FROM_WEST:
			retraceDirection = Direction::West;
			break;
		case TOP_FROM_NORTH:
			retraceDirection = Direction::North;
			break;
		default:
			assert(false);
			break;
	}

	return retraceDirection;
}
