#include <queue>

template <typename state, typename action, typename environement>
class BFS 
{
public:
	int nodesExpanded;
	BFS(){}
	//GetPath return if the goal was found
	bool GetPath(environement &e, state &start, state &goal);
	//GetNodesExpanded returns the total nodes expanded by the last GetPath call
	int GetNodesExpanded();
};

template <typename state, typename action, typename environment>
bool BFS<state, action, environment>::GetPath(environment &e, state &start, state &goal)
{
	nodesExpanded = 0;
	std::queue<state> FIFOq;
	FIFOq.push(start);
	std::vector<action> actions;
	while (!FIFOq.empty())
	{
		state next = FIFOq.front();
		FIFOq.pop();

		e.GetActions(next, actions);
		nodesExpanded++;
		for (auto &i : actions)
		{
			e.ApplyAction(next, i);
			if (next == goal) return true;
			FIFOq.push(next);
			e.UndoAction(next, i);
		}

	}
	return false;
}


template <typename state, typename action, typename environment>
int BFS<state, action, environment>::GetNodesExpanded()
{
	return nodesExpanded;
}