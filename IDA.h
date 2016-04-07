//
// Created by Dan Cruwys on 4/5/16.
// IDA* Algorithm
//

#ifndef HW1_IDA_H
#define HW1_IDA_H

#include "Heuristic.h"

template <typename state, typename action, typename environment>
struct IDA {
    int nodesExpanded = 0;
    int f;
    int g;
    IDA(){
        f=0;
        g=0;
    }
    Heuristic heuristic;
    //GetPath return if the goal was found
    int GetPath(environment &e, state &start, state &goal);
    //GetNodesExpanded returns the total nodes expanded by the last GetPath call
    int GetNodesExpanded();
    //Cost limited depth first search
    bool CLDFS(environment &e, state &start, state &goal, int &bound);
};

template <typename state, typename action, typename environment>
int IDA<state, action, environment>::GetNodesExpanded()
{
    return nodesExpanded;
}

template <typename state, typename action, typename environment>
int IDA<state, action, environment>::GetPath(environment &e, state &start, state &goal){
    int bound = heuristic.getHeuristic(start, goal);
    nodesExpanded = 0;
    bool found = false;
    while (!found)
    {
        g = 0;
        found = CLDFS(e, start, goal, bound);
        if (found) return bound;
        bound = f;
    }
    return bound;
};

template <typename state, typename action, typename environment>
bool IDA<state, action, environment>::CLDFS(environment &e, state &start, state &goal, int &bound) {
    std::vector<action> actions;
    f = g + heuristic.getHeuristic(start, goal);
	if (start == goal)
		return true;
	if(f > bound)
        return false;
    e.GetActions(start, actions);
	std::cout << "node expanded: " << start.nodeID << "\tbound: " << bound << std::endl;
    nodesExpanded++;
    for(auto &i: actions){
        e.ApplyAction(start, i);
        g++;
        bool found = CLDFS(e, start, goal, bound);
        if (found == true)
            return true;
        e.UndoAction(start, i);
        g--;
    }
    return false;
};

#endif //HW1_IDA