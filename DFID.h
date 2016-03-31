#include <queue>

template <typename state, typename action, typename environment>
class DFID
{
public:
	int nodesExpanded;
	//GetPath return if the goal was found
	bool GetPath(environment &e, state &start, state &goal);
	//GetNodesExpanded returns the total nodes expanded by the last GetPath call
	int GetNodesExpanded();
};

template <typename state, typename action, typename environment>
bool DFID<state, action, environment>::GetPath(environment &e, state &start, state &goal)
{
	nodesExpanded = 0;
	std::queue<state> FIFOq;
	FIFOq.push(start);
	std::vector<action> actions;
	while (!FIFOq.empty())
	{
		state next = FIFOq.front();
		FIFOq.pop();
		nodesExpanded++;
		if (next == goal) return true;
		//replace with code for DFID
		/*e.GetActions(next, actions);
		for (auto &i : actions)
		{
			e.ApplyAction(next, i);
			FIFOq.push(next);
			e.UndoAction(next, i);
		}*/
	}
	std::cout << "DFID didnt work" << std::endl;
	return false;
}

template <typename state, typename action, typename environment>
int DFID<state, action, environment>::GetNodesExpanded()
{
	return nodesExpanded;
}