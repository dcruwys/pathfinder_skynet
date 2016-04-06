#pragma once
#include <queue>

template <typename state, typename action, typename environment>
class BFS 
{
public:
	int nodesExpanded;
	BFS(){}
	//GetPath return if the goal was found
	bool GetPath(environment &e, state &start, state &goal);
	//GetNodesExpanded returns the total nodes expanded by the last GetPath call
	int GetNodesExpanded();
};

template <typename state, typename action, typename environment>
bool BFS<state, action, environment>::GetPath(environment &e, state &start, state &goal)
{
	nodesExpanded = 0;
	//make a queue and add the starting state to it
	std::queue<state> FIFOq;
	FIFOq.push(start);
	std::vector<action> actions;
	//while the queue has stuff in it, keep expanding nodes
	while (!FIFOq.empty())
	{
		state next = FIFOq.front();
		FIFOq.pop();
		//get the possible actions of the next state and increment the nodes expanded
		e.GetActions(next, actions);
		nodesExpanded++;
		for (auto &i : actions)
		{
			//for each action, apply the action, see if its the goal, add the new state to the queue and then undo the action
			e.ApplyAction(next, i);
			if (next == goal) return true;
			FIFOq.push(next);
			e.UndoAction(next, i);
		}
	}
	std::cout << "BFS could not return a path" << std::endl;
	return false;
}


template <typename state, typename action, typename environment>
int BFS<state, action, environment>::GetNodesExpanded()
{
	return nodesExpanded;
}