#include <queue>
#include <iostream>
#include <stack>

template <typename state, typename action, typename environment>
class DFS
{
public:
	int nodesExpanded = 0;
	//GetPath return if the goal was found
	bool GetPath(environment &e, state &start, state &goal, int depth);
	bool IDeep(environment &e, state &start, state &goal);
	//GetNodesExpanded returns the total nodes expanded by the last GetPath call
	int GetNodesExpanded();
};

template <typename state, typename action, typename environment>
bool DFS<state, action, environment>::GetPath(environment &e, state &start, state &goal, int depth)
{
	std::vector<action> actions;

    state next = start;
	if (next == goal)
        return true;
    if(depth <= 0)
        return false;
    nodesExpanded++;
    //replace with code for DFS
    e.GetActions(next, actions);
    for (auto &i : actions) {
        e.ApplyAction(next, i);
        bool found = GetPath(e, next, goal, --depth);
        if (found)
            return true;
        e.UndoAction(next, i);
    }
	//std::cout << "DFID didnt work" << std::endl;
	return false;
}

template <typename state, typename action, typename environment>
int DFS<state, action, environment>::GetNodesExpanded()
{
	return nodesExpanded;
}

template <typename state, typename action, typename environment>
bool DFS<state, action, environment>::IDeep(environment &e, state &start, state &goal){
    bool found = false;
    int depth = 1;
    while(!found){
        found = GetPath(e, start, goal, depth);
        depth++;
    }
    return found;
};

