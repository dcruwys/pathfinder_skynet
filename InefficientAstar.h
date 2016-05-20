#pragma once

#include <vector>
#include <iostream>

//template <typename state>
//struct Node
//{
//	state c;
//	int gcost;
//	int hcost;
//	int fcost;
//};

template<typename state, typename action, typename environment, typename heuristic>
class InefficientAstar
{
public:
	int nodesExpanded = 0;
	bool getPath(environment &e, state &start, state &goal, heuristic h);
private:
	void addOpen(Node<state> &s);
	void addClosed(Node<state> &s);
	bool onClosed(Node<state> &s);
	bool onOpen(Node<state> &s);
	void updateCost(Node<state> &c, int i);
	int getDuplicateIndex(Node<state> &s);
	Node<state> removeBest();
	std::vector<Node<state>> open;
	std::vector<Node<state>> closed;
};

template<typename state, typename action, typename environment, typename heuristic>
bool InefficientAstar<state, action, environment, heuristic>::getPath(environment &e, state &start, state &goal, heuristic h)
{
	//initialize actions and state so we dont create them on every iteration
	std::vector<action> actions;
	Node<state> s;
	s.c = start;
	//set up start node
	s.gcost = 0;
	s.hcost = h.hcost(start, goal);
	s.fcost = s.gcost + s.hcost;
	//put start node on the open list
	addOpen(s);
	//keep searching as long as there are nodes on the open list
	while (!open.empty())
	{
		//remove node with lowest fcost from the open list
		s = removeBest();
		nodesExpanded++;
		//std::cout << nodesExpanded << std::endl;
		//std::cout << "X: " << s.c.x << " Y: " << s.c.y << std::endl;
		//if lowest f cost node from open list is goal, return found path
		if (s.c == goal)
		{
			std::cout << nodesExpanded << std::endl;
			return true;
		}
		//generate successors of best available node from open list
		e.GetActions(s.c, actions);
		//add node to closed list
		addClosed(s);
		//for each action that can be taken from that node
		for (action &a : actions)
		{
			//apply the action to generate a new state
			e.ApplyAction(s.c, a);
			if (!onClosed(s) && onOpen(s))
			{
				//if on open already, then update cost if needed
				s.gcost++;
				s.hcost = h.hcost(s.c, goal);
				s.fcost = s.gcost + s.hcost;
				int i = getDuplicateIndex(s);
				updateCost(s, i);
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
				e.UndoAction(s.c, a);
			}
		}
	}
	return false;
}

template<typename state, typename action, typename environment, typename heuristic>
void InefficientAstar<state, action, environment, heuristic>::addOpen(Node<state> &s)
{
	open.push_back(s);
}

template<typename state, typename action, typename environment, typename heuristic>
void InefficientAstar<state, action, environment, heuristic>::addClosed(Node<state> &s)
{
	closed.push_back(s);
}

template<typename state, typename action, typename environment, typename heuristic>
bool InefficientAstar<state, action, environment, heuristic>::onOpen(Node<state> &s)
{
	for (int i = 0; i < open.size(); i++)
	{
		if (s.c == open[i].c)
		{
			return true;
		}
	}
	return false;
}

template<typename state, typename action, typename environment, typename heuristic>
bool InefficientAstar<state, action, environment, heuristic>::onClosed(Node<state> &s)
{
	for (int i = 0; i < closed.size(); i++)
	{
		if (s.c == closed[i].c)
		{
			return true;
		}
	}
	return false;
}

template<typename state, typename action, typename environment, typename heuristic>
int InefficientAstar<state, action, environment, heuristic>::getDuplicateIndex(Node<state> &s)
{
	for (int i = 0; i < open.size(); i++)
	{
		if (s.c == open[i].c)
		{
			return i;
		}
	}
	std::cout << "Error: getDuplicateIndex() couldn't find a duplicate" << std::endl;
	return -1;
}

template<typename state, typename action, typename environment, typename heuristic>
Node<state> InefficientAstar<state, action, environment, heuristic>::removeBest()
{
	Node<state> best = open[0];
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
void InefficientAstar<state, action, environment, heuristic>::updateCost(Node<state> &s, int i)
{
	if (s.fcost < open[i].fcost)
	{
		open[i].fcost = s.fcost;
		open[i].gcost = s.gcost;
		open[i].hcost = s.hcost;
	}
}
