#pragma once
#include <vector>
//#define _DEBUG

template<typename state, typename action, typename environment, typename heurstic>
class Astar
{
public:
	int nodesExpanded = 0;
	bool getPath(environment &e, state &start, state &goal, heurstic h);
private:
	void addOpen(state &c);
	void addClosed(state &c);
	bool onClosed(state &c);
	bool onOpen(state &c);
	void updateCost(state &c);
	state getDuplicate(state &c);
	state removeBest();
	bool OpenEmpty();
	std::vector<state> open;
	std::vector<state> closed;
};

template<typename state, typename action, typename environment, typename heurstic>
bool Astar<state, action, environment, heurstic>::getPath(environment &e, state &start, state &goal, heurstic h)
{
	//list of actions for generating successors
	std::vector<action> actions;
	//set up start node
	start.gcost = 0;
	start.hcost = h.hcost(start, goal);
	start.fcost = start.gcost + start.hcost;
	//put starting node on the open list
	addOpen(start);
	state s;
	//keep searching as long as nodes are on open
	while (!OpenEmpty())
	{

		//find node, q, with least f cost on the open list
		//pop q off the open list
		s = removeBest();
		//add node about to expand on to closed
		addClosed(s);
		//if best state off open is goal, return success
		if (s == goal)
			return true;
		//generate q's up to 8 successors and put them in actions list
		e.GetActions(s, actions);
		//for each successor
		std::cout<< "GCost: " << s.gcost << " Nodes: " << nodesExpanded << std::endl;
		for (auto &a : actions)
		{
		#ifdef _DEBUG
            	std::cout << "# of Actions: " << actions.size() << std::endl;
		#endif
			e.ApplyAction(s, a);
			nodesExpanded++;
			//successors gcost = q.gcost + distance between q and successor
			s.gcost++;
			//successors hcost = heuristic cost from successor to goal
			s.hcost = h.hcost(s, goal);
			//successors fcost = gcost + hcost
			s.fcost = s.gcost + s.hcost;
			#ifdef _DEBUG
            	std::cout << "FCost: " << s.fcost << std::endl;
			#endif
			if (!onClosed(s))
			{
				if (!onOpen(s))
				{
					//not on open or closed, must be newly discovered node, so add to open
					addOpen(s);
				}
					//not on closed, but on open.
					//compare fcosts and update costs of duplicate if this fcost is lower
				else
				{
					state temp = getDuplicate(s);
					if (s.fcost < temp.fcost)
					{
						updateCost(s);
					}
				}
			}
			else
			{
				//should only happen if inconsistent heuristic
				//for assignment, assume consistent
			}
			e.UndoAction(s, a);
			//undo/rewind gcost
			s.gcost--;
		}
	}
	return false;
}

template <typename state, typename action, typename environment, typename heurstic>
void Astar<state, action, environment, heurstic>::addOpen(state &c)
{
	open.push_back(c);
}

template <typename state, typename action, typename environment, typename heurstic>
void Astar<state, action, environment, heurstic>::addClosed(state &c)
{
	closed.push_back(c);
}

template <typename state, typename action, typename environment, typename heurstic>
bool Astar<state, action, environment, heurstic>::onClosed(state &c)
{
	for (int i = 0; i < closed.size(); i++)
	{
		if (c == closed[i])
		{
			return true;
		}
	}
	return false;
}

template <typename state, typename action, typename environment, typename heurstic>
bool Astar<state, action, environment, heurstic>::onOpen(state &c)
{
	for (int i = 0; i < open.size(); i++)
	{
		if (c == open[i])
		{
			return true;
		}
	}
	return false;
}

template <typename state, typename action, typename environment, typename heurstic>
bool Astar<state, action, environment, heurstic>::OpenEmpty()
{
	return open.empty();
}

template <typename state, typename action, typename environment, typename heurstic>
state Astar<state, action, environment, heurstic>::getDuplicate(state &c)
{
	for (int i = 0; i < open.size(); i++)
	{
		if (c == open[i])
		{
			return open[i];
		}
	}
	return c;
}

template <typename state, typename action, typename environment, typename heurstic>
state Astar<state, action, environment, heurstic>::removeBest()
{
	if(open.size() == 1){
		return open[0];
	}
	#ifdef _DEBUG
		std::cout << "Removing best... " << open.size() << std::endl;
	#endif
	state best = open[0];
	int index = 0;
	for (int i = 1; i < open.size(); i++)
	{
		if (open[i].fcost < best.fcost)
		{
			index = i;
			best = open[i];
		}
	}
	#ifdef _DEBUG
		std::cout << "Before removal: " << open.size() << std::endl;
	#endif
	open.erase(open.begin() + (index - 1));
	#ifdef _DEBUG
		std::cout << "After removal: " << open.size() << std::endl;
	#endif
	return best;
}

template <typename state, typename action, typename environment, typename heurstic>
void Astar<state, action, environment, heurstic>::updateCost(state &c)
{
	for (int i = 0; i < open.size(); i++)
	{
		if (c == open[i])
		{
		#ifdef _DEBUG
			std::cout << "open[i] fcost: " << open[i].fcost << std::endl;
			std::cout << "c fcost: " << c.fcost << std::endl;
		#endif
			open[i].gcost = c.gcost;
			open[i].hcost = c.hcost;
			open[i].fcost = c.fcost;
		}
	}
}