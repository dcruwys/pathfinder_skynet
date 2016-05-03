#ifndef Astar_h
#define Astar_h

#include <vector>

template<typename state, typename action, typename environment, typename list, typename heurstic>
class Astar
{
public:
	bool getPath(environment &e, state &start, state &goal, heurstic h);
private:
};

//TODO
//A node needs to have info about its coordinates in grid, f cost, g cost, h cost, parent

template<typename state, typename action, typename environment, typename list, typename heurstic>
bool Astar<state, action, environment, list, heurstic>::getPath(environment &e, state &start, state &goal, heurstic h)
{
	list ocList;
	ocList.addOpen(start);

	while (!ocList.OpenEmpty())
	{
		//find node, q, with least f cost on the open list
		//pop q off the open list
		state s = ocList.removeBest();
		//generate q's 8 successors and set their parents to q
		std::vector<action> actions;
		e.GetActions(s, actions);
		//for each successor
		for (auto a : actions)
		{
			std::cout << "Test" << std::endl;
            e.ApplyAction(s, a);
			//if successor is goal, stop search
			if(s == goal)
				return true;

			//successors gcost = q.gcost + distance between q and successor
			s.gcost++;
			//successors hcost = heuristic cost from successor to goal
			s.hcost = h.hcost(s, goal);
			//successors fcost = gcost + hcost
			s.fcost = s.gcost + s.hcost;
            //Check for duplicates
            if(!ocList.checkDuplicates(s))
				std::cout << "Added new node" << std::endl;
            e.UndoAction(s, a);
			s.gcost--;
		}

		//end for each
		//put q on the closed list
	}

}

#endif