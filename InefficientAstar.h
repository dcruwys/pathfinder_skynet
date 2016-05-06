#pragma once

#include <vector>
#include <iostream>

template <typename coordinate>
struct Node
{
	coordinate c;
	int gcost;
	int hcost;
	int fcost;
};

template <typename coordinate>
inline bool operator==(const Node<coordinate> &c1, const Node<coordinate> &c2)
{
	return c1.c.x == c2.c.x && c1.c.y == c2.c.y;
}

template<typename state, typename action, typename environment, typename heuristic>
class InefficientAstar
{
public:
	int nodesExpanded = 0;
	bool getPath(environment &e, state &start, state &goal, heuristic h);
private:
	void addOpen(state &s);
	void addClosed(state &s);
	bool onClosed(state &s);
	bool onOpen(state &s);
	void updateCost(state &c, int i);
	int getDuplicateIndex(state &s);
	state removeBest();
	std::vector<state> open;
	std::vector<state> closed;
};

template<typename state, typename action, typename environment, typename heuristic>
bool InefficientAstar<state, action, environment, heuristic>::getPath(environment &e, state &start, state &goal, heuristic h)
{
	//initialize actions and state so we dont create them on every iteration
	std::vector<action> actions;
	state s;
	//set up start node
	start.gcost = 0;
	start.hcost = h.hcost(start, goal);
	start.fcost = start.gcost + start.hcost;
	//put start node on the open list
	addOpen(start);
	//keep searching as long as there are nodes on the open list
	while (!open.empty())
	{
		//remove node with lowest fcost from the open list
		s = removeBest();
		nodesExpanded++;
		//if lowest f cost node from open list is goal, return found path
		if (s == goal)
		{
			std::cout << nodesExpanded << std::endl;
			return true;
		}
		//generate successors of best available node from open list
		e.GetActions(s, actions);
		//add node to closed list
		addClosed(s);
		//for each action that can be taken from that node
		for (action &a : actions)
		{
			//apply the action to generate a new state
			e.ApplyAction(s, a);
			if (!onClosed(s) && onOpen(s))
			{
				//if on open already, then update cost if needed
				s.gcost++;
				s.hcost = h.hcost(s, goal);
				s.fcost = s.gcost + s.hcost;
				int i = getDuplicateIndex(s);
				updateCost(s, i);
				e.UndoAction(s, a);
				s.gcost--;
			}
			else if (!onClosed(s) && !onOpen(s))
			{
				//if not on open or closed, its a newly discovered node
				//so set costs and add to open
				s.gcost++;
				s.hcost = h.hcost(s, goal);
				s.fcost = s.gcost + s.hcost;
				addOpen(s);
				e.UndoAction(s, a);
				s.gcost--;
			}
			else
			{
				//node is on closed
				//skip this node
				e.UndoAction(s, a);
			}
		}
	}
	return false;
}

template<typename state, typename action, typename environment, typename heuristic>
void InefficientAstar<state, action, environment, heuristic>::addOpen(state &s)
{
	open.push_back(s);
}

template<typename state, typename action, typename environment, typename heuristic>
void InefficientAstar<state, action, environment, heuristic>::addClosed(state &s)
{
	closed.push_back(s);
}

template<typename state, typename action, typename environment, typename heuristic>
bool InefficientAstar<state, action, environment, heuristic>::onOpen(state &s)
{
	for (int i = 0; i < open.size(); i++)
	{
		if (s == open[i])
		{
			return true;
		}
	}
	return false;
}

template<typename state, typename action, typename environment, typename heuristic>
bool InefficientAstar<state, action, environment, heuristic>::onClosed(state &s)
{
	for (int i = 0; i < closed.size(); i++)
	{
		if (s == closed[i])
		{
			return true;
		}
	}
	return false;
}

template<typename state, typename action, typename environment, typename heuristic>
int InefficientAstar<state, action, environment, heuristic>::getDuplicateIndex(state &s)
{
	for (int i = 0; i < open.size(); i++)
	{
		if (s == open[i])
		{
			return i;
		}
	}
	std::cout << "Error: getDuplicateIndex() couldn't find a duplicate" << std::endl;
	return -1;
}

template<typename state, typename action, typename environment, typename heuristic>
state InefficientAstar<state, action, environment, heuristic>::removeBest()
{
	state best = open[0];
	if (open.size() == 1)
	{
		open.erase(open.begin());
		return best;
	}
	int index = 0;
	for (int i = 1; i < open.size(); i++)
	{
		if (open[i].fcost < best.fcost)
		{
			index = i;
			best = open[i];
		}
		else if (open[i].fcost == best.fcost)
		{
			//ties go to high g cost
			if (open[i].gcost >= best.gcost)
			{
				index = i;
				best = open[i];
			}
		}
	}
	open.erase(open.begin() + index);
	return best;
}

template<typename state, typename action, typename environment, typename heuristic>
void InefficientAstar<state, action, environment, heuristic>::updateCost(state &s, int i)
{
	if (s.fcost < open[i].fcost)
	{
		open[i].fcost = s.fcost;
		open[i].gcost = s.gcost;
		open[i].hcost = s.hcost;
	}
}
