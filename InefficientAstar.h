#ifndef PATHFINDER_SKYNET_INEFFICIENTASTAR_H
#define PATHFINDER_SKYNET_INEFFICIENTASTAR_H

#include <vector>
#include <iostream>

template <typename state>
struct node {
    state s;
    double fcost;
    double depth;
};

template<typename state, typename action, typename environment, typename heurstic>
class InefficientAstar
{
public:
    int nodesExpanded = 0;
    bool getPath(environment &e, state &start, state &goal, heurstic h);
private:
    bool onOpen(node<state> &c);
    bool onClosed(node<state> &c);
    void addOpen(node<state> &c);
    void addClosed(node<state> &c);
    void checkDuplicates(node<state> &c);
    node<state> &removeBest();
    std::vector<node<state>> open;
    std::vector<node<state>> closed;
};


template<typename state, typename action, typename environment, typename heurstic>
bool InefficientAstar<state, action, environment, heurstic>::getPath(environment &e, state &start, state &goal, heurstic h)
{
    node<state> n;
    n.depth = 0;
    n.s = start;
    n.fcost =  h.hcost(n.s, goal) + n.depth;
    addOpen(n);
    std::vector<action> actions;
    while(!open.empty()){
        n = removeBest();
        std::cout << n.s << std::endl;
        if (n.s == goal) {
            std::cout << "Found solution gcost: " << n.depth << "\n";
            std::cout << "Nodes Expanded: " << nodesExpanded << "\n";

            return true;
        }
        nodesExpanded++;
        e.GetActions(n.s, actions);
        n.depth++;
        //for each successor
        for (auto &a : actions) {
            e.ApplyAction(n.s, a);
            n.fcost = h.hcost(n.s, goal) + n.depth;
            //std::cout << "Fcost: " << n.fcost << std::endl;
            std::cout << "Depth: " << n.depth << std::endl;
            if(!onClosed(n)){
                if(!onOpen(n)){
                    addOpen(n);
                }
                else{
                    checkDuplicates(n);
                }
            }
            e.UndoAction(n.s, a);
        }
        n.depth--;
    }
    return false;

};

template <typename state, typename action, typename environment, typename heurstic>
void InefficientAstar<state, action, environment, heurstic>::addOpen(node<state> &c)
{
    open.push_back(c);
}

template <typename state, typename  action, typename environment, typename  heurstic>
void InefficientAstar<state, action, environment, heurstic>::checkDuplicates(node<state> &c){
    for (int i = 0; i < open.size(); i++) {
        if (c.s == open[i].s)
        {
            if(c.fcost < open[i].fcost) {
                open[i].fcost = c.fcost;
            }
     }
    }
}

template <typename state, typename action, typename environment, typename heurstic>
void InefficientAstar<state, action, environment, heurstic>::addClosed(node<state> &c)
{
    for (int i = 0; i < closed.size(); i++) {
        if (c.s == closed[i].s) {
            if (c.fcost < closed[i].fcost) {
                closed[i].fcost = c.fcost;
            }
            return;
        }

    }
    closed.push_back(c);
}

template <typename state, typename action, typename environment, typename heurstic>
node<state> &InefficientAstar<state, action, environment, heurstic>::removeBest()
{
    if(open.size() == 1){
        return open[0];
    }
    int index = 0;
    for (int i = 0; i < open.size(); i++)
    {
        if (open[i].fcost < open[index].fcost)
        {
            index = i;
        }
    }
    node<state> best = open[index];
    addClosed(open[index]);
    if(open.size() > 0)
     open.erase(open.begin()+(index-1));
    return best;
}

template <typename state, typename action, typename environment, typename heurstic>
bool InefficientAstar<state, action, environment, heurstic>::onOpen(node<state> &c) {
    for(int i = 0; i < open.size(); i++){
        if(c.s == open[i].s){
            return true;
        }
    }
    return false;
}

template <typename state, typename action, typename environment, typename heurstic>
bool InefficientAstar<state, action, environment, heurstic>::onClosed(node<state> &c) {
    for(int i = 0; i < closed.size(); i++){
        if(c.s == closed[i].s){
            return true;
        }
    }
    return false;
}
#endif //PATHFINDER_SKYNET_INEFFICIENTASTAR_H