#pragma once

#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <cstdint>

template <typename state>
struct Node
{
    state c;
    int gcost;
    int hcost;
    int fcost;
    uint64_t rank;
};

struct tupler{
    int fcost;
    uint64_t rank;
    tupler(int f, uint64_t r){
        fcost = f;
        rank = r;
    }
    inline bool operator<(const tupler &c1) const
    {
        return this->fcost > c1.fcost;
    }
};

template<typename state, typename action, typename environment, typename heuristic>
class EfficientAstar
{
public:
    int nodesExpanded = 0;
    bool getPath(environment &e, state &start, state &goal, heuristic h);
private:
    void addOpen(Node<state> &s);
    void addClosed(Node<state> &s);
    bool onClosed(Node<state> &s);
    bool onOpen(Node<state> &s);
    void updateCost(Node<state> &c);
    Node<state> removeBest();
    std::priority_queue<tupler> queue;
    std::map<uint64_t, Node<state>> open;
    std::map<uint64_t, Node<state>> closed;
};

template<typename state, typename action, typename environment, typename heuristic>
bool EfficientAstar<state, action, environment, heuristic>::getPath(environment &e, state &start, state &goal, heuristic h)
{
    //initialize actions and state so we dont create them on every iteration
    std::vector<action> actions;
    Node<state> s;
    s.c = start;
    //set up start node
    s.gcost = 0;
    s.hcost = h.hcost(start, goal);
    s.fcost = s.gcost + s.hcost;
    s.rank = e.Rank(s.c);
    //put start node on the open list
    addOpen(s);
    //keep searching as long as there are nodes on the open list
    while (!queue.empty())
    {

        s.rank = e.Rank(s.c);
        //remove node with lowest fcost from the open list
        s = removeBest();
        //if lowest f cost node from open list is goal, return found path
        if (s.c == goal)
        {
            std::cout << "Nodes Expanded: "<< nodesExpanded << std::endl;
            return true;
        }
        //generate successors of best available node from open list
        e.GetActions(s.c, actions);
        nodesExpanded++;
        //for each action that can be taken from that node
        for (action &a : actions)
        {
            //apply the action to generate a new state
            e.ApplyAction(s.c, a);
            s.rank = e.Rank(s.c);
            if (!onClosed(s) && onOpen(s))
            {
                //if on open already, then update cost if needed
                s.gcost++;
                s.hcost = h.hcost(s.c, goal);
                s.fcost = s.gcost + s.hcost;
                updateCost(s);
                e.UndoAction(s.c, a);
                s.gcost--;
            }
            else if (!onClosed(s) && !onOpen(s))
            {
                //if not on open or closed, its a newly discovered node
                //so set costs and add to open
                s.gcost++;
                s.hcost = h.hcost(s.c, goal);
                s.fcost = s.gcost + s.hcost;
                addOpen(s);
                e.UndoAction(s.c, a);
                s.gcost--;
            }
            else
            {
                //node is on closed
                //skip this node
				//the hashmap is initialized with the goal at the 0th element
				//so, goal is always on closed
				//have to check if element is goal before we skip it
                if(s.c == goal) {
                    std::cout << nodesExpanded << std::endl;
                    return true;
                }
                e.UndoAction(s.c, a);
            }
        }
    }
    return false;
}

template<typename state, typename action, typename environment, typename heuristic>
void EfficientAstar<state, action, environment, heuristic>::addOpen(Node<state> &s)
{
    //create tuple type for queue
    tupler tup(s.fcost, s.rank);
    //insert tuple into queue
    queue.push(tup);
    //insert rank and node into hashmap
    open[s.rank] = s;
}

template<typename state, typename action, typename environment, typename heuristic>
void EfficientAstar<state, action, environment, heuristic>::addClosed(Node<state> &s)
{
    //insert rank and node into hashmap
    closed.insert(std::pair<uint64_t , Node<state>>(s.rank, s));

}

template<typename state, typename action, typename environment, typename heuristic>
bool EfficientAstar<state, action, environment, heuristic>::onOpen(Node<state> &s)
{
    return s.c == open[s.rank].c;
}

template<typename state, typename action, typename environment, typename heuristic>
bool EfficientAstar<state, action, environment, heuristic>::onClosed(Node<state> &s)
{
    return s.c == closed[s.rank].c;
}

template<typename state, typename action, typename environment, typename heuristic>
Node<state> EfficientAstar<state, action, environment, heuristic>::removeBest()
{
    //get top element, pop
    tupler tup = queue.top();
    queue.pop();
    //get element at that rank and remove from map
    Node<state> s = open[tup.rank];
    open.erase(tup.rank);
    //add to closed map
    addClosed(s);
    return s;
}

template<typename state, typename action, typename environment, typename heuristic>
void EfficientAstar<state, action, environment, heuristic>::updateCost(Node<state> &s)
{
    //When we assign things to the hashmap, it will overwrite the object there, so thats the update for the hashmaps
    if(onOpen(s) && open[s.rank].fcost > s.fcost)
        open[s.rank] = s;
}
