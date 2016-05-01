#pragma once
#include <vector>

template <typename state, typename action, typename environment, typename heuristic>
class IDAStar
{
public:
	// GetPath returns if the goal was found
	bool GetPath(environment &e, state &start, state &goal, heuristic &h);

	void GetSolution(std::vector<action> &s) { s = solution; }
	// Returns the total nodes expanded by the last GetPath call.
	uint64_t GetNodesExpanded();
private:
	bool BoundedDFS(environment &e, state &s, heuristic &h, int depth);
	uint64_t nodesExpanded;
	int currentBound;
	int nextBound;
	std::vector<action> actionHistory;
	std::vector<std::vector<action>> moveArrays;
	std::vector<action> solution;
	state g;
};

template <typename state, typename action, typename environment, typename heuristic>
bool IDAStar<state, action, environment, heuristic>::GetPath(environment &e, state &start, state &goal, heuristic &h)
{
    std::cout << "starting IDA*" << std::endl;
	nodesExpanded = 0;
	g = goal;
	currentBound = h.hcost(start);
	nextBound = -1;
	while (true)
	{
		if (moveArrays.size() <= currentBound)
			moveArrays.resize(currentBound + 1);
		std::cout << "Bound: " << currentBound;
		std::cout << "; " << nodesExpanded << " nodes expanded thus far\n";
		if (BoundedDFS(e, start, h, 0))
			return true;
		currentBound = nextBound;
		nextBound = -1;
	}
}

template <typename state, typename action, typename environment, typename heuristic>
bool IDAStar<state, action, environment, heuristic>::BoundedDFS(environment &e, state &s, heuristic &h, int depth)
{
	int f = depth + h.hcost(s);
	if (f > currentBound)
	{
		if (nextBound == -1)
			nextBound = f;
		else if (f < nextBound)
			nextBound = f;
		return false;
	}
	if (s == g)
	{
		solution = actionHistory;
		return true;
	}


	std::vector<action> &moves = moveArrays[depth];
	e.GetActions(s, moves);
	nodesExpanded++;
	//std::cout << nodesExpanded << std::endl;
	for (auto a : moves)
	{
		if (actionHistory.size() > 0 && actionHistory.back() == e.InvertAction(a))
			continue;
		e.ApplyAction(s, a);
		actionHistory.push_back(a);
		bool result = BoundedDFS(e, s, h, depth + 1);
		actionHistory.pop_back();
		e.UndoAction(s, a);
		if (result == true)
		{
			return true;
		}
	}
	return false;
}

template <typename state, typename action, typename environment, typename heuristic>
uint64_t IDAStar<state, action, environment, heuristic>::GetNodesExpanded()
{
	return nodesExpanded;
}