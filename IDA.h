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
    int g = 0;
    int f = 0;
    Heuristic heuristic;
    //GetPath return if the goal was found
    bool GetPath(environment &e, state &start, state &goal);
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
bool IDA<state, action, environment>::GetPath(environment &e, state &start, state &goal){
    int bound = heuristic.getHeuristic(start);

    bool found = false;
    do{
    //////
    g = 0;
    f = 0;
    //////
     found = CLDFS(e, start, goal, bound);
     bound = f;
    } while(!found);

    return bound;
};

template <typename state, typename action, typename environment>
bool IDA<state, action, environment>::CLDFS(environment &e, state &start, state &goal, int &bound) {
    std::vector<action> actions;
    f = g + heuristic.getHeuristic(start);
    if(f > bound) return false;
    if(start == goal) return true;
    e.GetActions(start, actions);
    for(auto &i: actions){
        e.ApplyAction(start, i);
        g++;
        CLDFS(e, start, goal, bound);
        e.UndoAction(start, i);
        g--;
    }
}

#endif //HW1_IDA_H
