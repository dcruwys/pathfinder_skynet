#pragma once
#include <queue>
#include <iostream>
#include <stack>

template <typename state, typename action, typename environment>
class DFS
{
public:
	int nodesExpanded = 0;
	//GetPath return if the goal was found
	bool IDeep(environment &e, state &start, state &goal, int depth);
	bool GetPath(environment &e, state &start, state &goal);
	//GetNodesExpanded returns the total nodes expanded by the last GetPath call
	int GetNodesExpanded();
};

template <typename state, typename action, typename environment>
bool DFS<state, action, environment>::IDeep(environment &e, state &start, state &goal, int depth)
{
	//list of actions
	std::vector<action> actions;
    //if at goal, return
	if (start == goal && depth == 0)
        return true;
    if(depth <= 0)
        return false;
	//get actions for current state and incrememnt nodes expanded
    e.GetActions(start, actions);
    nodesExpanded++;
    for (auto &i : actions) {
		//for each action, apply the action, recursively search with the new state, if it doesnt find it, undo the action
        e.ApplyAction(start, i);
        bool found = IDeep(e, start, goal, depth-1);
        if (found)
            return true;
        e.UndoAction(start, i);
    }
	return false;
}

template <typename state, typename action, typename environment>
int DFS<state, action, environment>::GetNodesExpanded()
{
	return nodesExpanded;
}

template <typename state, typename action, typename environment>
bool DFS<state, action, environment>::GetPath(environment &e, state &start, state &goal){
    bool found = false;
    int depth = 1;
	//just keep search, just keep searching... until its found
    while(!found){
        found = IDeep(e, start, goal, depth);
        depth++;
    }
    return found;
};

