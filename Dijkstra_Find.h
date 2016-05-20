#pragma once

#include <vector>
#include <iostream>
#include "Dijkstra_label.h"

//template <typename state>
//struct Node
//{
//	state c;
//	int gcost;
//	int hcost;
//	int fcost;
//	uint64_t rank;
//};


template<typename state, typename action, typename environment>
class Dijkstra_find
{
public:
	int nodesExpanded = 0;
	state getPath(environment &e, std::vector<pivot_info> &pivots);
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

template<typename state, typename action, typename environment>
state Dijkstra_find<state, action, environment>::getPath(environment &e, std::vector<pivot_info> &pivots)
{
	Node<state> s;
	for (auto &i : pivots)
	{
		s.c = i.pivot;
		//set up start node
		s.gcost = 0;
		s.hcost = 0;
		s.fcost = s.gcost + s.hcost;
		//put start node on the open list
		addOpen(s);
	}
	//initialize actions and state so we dont create them on every iteration
	std::vector<action> actions;
	
	//keep searching as long as there are nodes on the open list
	while (!open.empty())
	{
		//remove node with lowest fcost from the open list
		s = removeBest();
		nodesExpanded++;

		//generate successors of best available node from open list
		e.GetActions(s.c, actions);
		//add node to closed list
		addClosed(s);
		//for each action that can be taken from that node
		for (action &a : actions)
		{
			//apply the action to generate a new state
			e.ApplyAction(s.c, a);
			//if (!onClosed(s) && onOpen(s))
			//{
			//	//if on open already, then update cost if needed
			//	s.gcost++;
			//	s.hcost = 0;
			//	s.fcost = s.gcost + s.hcost;
			//	int i = getDuplicateIndex(s);
			//	updateCost(s, i);
			//	e.UndoAction(s.c, a);
			//	s.gcost--;
			//}
			if (!onClosed(s) && !onOpen(s))
			{
				//if not on open or closed, its a newly discovered node
				//so set costs and add to open
				s.gcost++;
				s.hcost = 0;
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
	return s.c;
}

template<typename state, typename action, typename environment>
void Dijkstra_find<state, action, environment>::addOpen(Node<state> &s)
{
	open.push_back(s);
}

template<typename state, typename action, typename environment>
void Dijkstra_find<state, action, environment>::addClosed(Node<state> &s)
{
	closed.push_back(s);
}

template<typename state, typename action, typename environment>
bool Dijkstra_find<state, action, environment>::onOpen(Node<state> &s)
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

template<typename state, typename action, typename environment>
bool Dijkstra_find<state, action, environment>::onClosed(Node<state> &s)
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

template<typename state, typename action, typename environment>
int Dijkstra_find<state, action, environment>::getDuplicateIndex(Node<state> &s)
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

template<typename state, typename action, typename environment>
Node<state> Dijkstra_find<state, action, environment>::removeBest()
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

template<typename state, typename action, typename environment>
void Dijkstra_find<state, action, environment>::updateCost(Node<state> &s, int i)
{
	if (s.fcost < open[i].fcost)
	{
		open[i].fcost = s.fcost;
		open[i].gcost = s.gcost;
		open[i].hcost = s.hcost;
	}
}
