#ifndef Astar_h
#define Astar_h
#include "OpenClosedList.h"

template<typename state, typename action, typename environment>
class Astar
{
public:
	bool getPath(environment &e, state &start, state &goal);
private:
};

//TODO
//A node needs to have info about its coordinates in grid, f cost, g cost, h cost, parent

template<typename state, typename action, typename environment>
bool Astar<state, action, environment>::getPath(environment &e, state &start, state &goal)
{
	OpenClosedList ocList;
	//TODO put starting node on the open list

	while (!ocList.OpenEmpty())
	{
		//find node, q, with least f cost on the open list
		//pop q off the open list
		//generate q's 8 successors and set their parents to q
		//for each successor
			//if successor is goal, stop search
			//successors gcost = q.gcost + distance between q and successor
			//successors hcost = heuristic cost from successor to goal
			//successors fcost = gcost + hcost

			//if a node on the open list has same coordinates as successor and has a 
			//lower f cost than successor, then skip this successor

			//if a node on the closed list has same coordinates and lower fcost than
			//successor, skip this successor, otherwise add node to open list
		//end for each
		//put q on the closed list
	}
	
}

#endif