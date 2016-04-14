//
// Created by Dan Cruwys on 4/5/16.
// IDA* Algorithm
//

#ifndef HW1_IDA_H
#define HW1_IDA_H

#include "Heuristic.h"
#include <vector>

template <typename state, typename action, typename environment>
struct IDA {
    int nodesExpanded = 0;
    int f;
    int g;
	std::vector<state> path;
	std::vector<action> pathActions;
    IDA(){
        f=0;
        g=0;
        std::vector<state> path;
        std::vector<action> pathActions;
    }
    Heuristic h;
    //GetPath return if the goal was found
    int GetPath(environment &e, state &start, state &goal);
    //GetNodesExpanded returns the total nodes expanded by the last GetPath call
    int GetNodesExpanded();
    //Cost limited depth first search
    int CLDFS(environment &e, state &start, state &goal, int &bound, action &lastAction);
};

template <typename state, typename action, typename environment>
int IDA<state, action, environment>::GetNodesExpanded()
{
    return nodesExpanded;
}

template <typename state, typename action, typename environment>
int IDA<state, action, environment>::GetPath(environment &e, state &start, state &goal) {
   // path.push_back(start);
    state tempStart = start;
    int bound = h.getHeuristic(start, goal);
    bool found = false;
    action temp;
    while (!found){
            f = CLDFS(e, start, goal, bound, temp);
        if (f == -1)
            found = true;
        if (f == std::numeric_limits<int>::max())
            return false;
        bound = f;
        //std::cout << bound << std::endl;
    }
    path.push_back(tempStart);
    for(action &i : pathActions)
    {
        e.ApplyAction(tempStart, i);
        path.push_back(tempStart);
    }
    return pathActions.size();
};

template <typename state, typename action, typename environment>
int IDA<state, action, environment>::CLDFS(environment &e, state &start, state &goal, int &bound, action &lastAction) {
    std::vector<action> actions;
    f = g + h.getHeuristic(start, goal);

    if(f > bound)
        return f;
    if(start == goal)
        return -1;
    int min = std::numeric_limits<int>::max();
    e.GetActions(start, actions);
    nodesExpanded++;
    for (auto &i : actions){
        if(i != lastAction) {
            e.ApplyAction(start, i);
            pathActions.push_back(i);
            g++;
            f = CLDFS(e, start, goal, bound, i);
            if (f == -1)
                return f;
            if (f < min)
                min = f;
            e.UndoAction(start, i);
            g--;
            pathActions.pop_back();
        }
    }
    return min;


};

#endif //HW1_IDA
