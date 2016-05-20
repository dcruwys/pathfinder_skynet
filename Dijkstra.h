#pragma once

#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <cstdint>

template <typename state>
struct NodeD
{
	state c;
	int gcost;
	int fcost;
	int pivot_num;
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

template<typename state, typename action, typename environment, typename pivotinfo>
class Dijkstra
{
public:
	int nodesExpanded = 0;
	state getPath(environment &e, std::vector<pivotinfo> &pivots);
private:
	void addOpen(NodeD<state> &s);
	void addClosed(NodeD<state> &s);
	bool onClosed(NodeD<state> &s);
	bool onOpen(NodeD<state> &s);
	void updateCost(NodeD<state> &c);
	NodeD<state> removeBest();
	std::priority_queue<tupler> queue;
	std::map<uint64_t, NodeD<state>> open;
	std::map<uint64_t, NodeD<state>> closed;
};

template<typename state, typename action, typename environment, typename pivotinfo>
state Dijkstra<state, action, environment, pivotinfo>::getPath(environment &e, std::vector<pivotinfo> &pivots)
{
	//initialize actions and state so we dont create them on every iteration
	std::vector<action> actions;
	//add all the pivots to the open list at the beginning
	int counter = 0;
	for (auto &i : pivots)
	{
		NodeD<state> s;
		//set node coordinate to pivot coordinate
		s.c = pivots[counter].pivot;
		//keep track of which pivot it is
		s.pivot_num = counter;
		//set up pivot node
		s.gcost = 0;
		s.fcost = s.gcost;
		s.rank = e.Rank(s.c);
		//put pivot node on the open list
		addOpen(s);
		counter++;
	}

	NodeD<state> s;
	//keep searching as long as there are nodes on the open list
	while (!queue.empty())
	{

		s.rank = e.Rank(s.c);
		//remove node with lowest fcost from the open list
		s = removeBest();
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
				//record gcost from state's respective pivot into a map of gcosts for that pivot
				pivots[s.pivot_num].costs[s.c.y][s.c.x] = s.gcost;
				s.fcost = s.gcost;
				updateCost(s);
				e.UndoAction(s.c, a);
				s.gcost--;
			}
			else if (!onClosed(s) && !onOpen(s))
			{
				//if not on open or closed, its a newly discovered node
				//so set costs and add to open
				s.gcost++;
				//record gcost from state's respective pivot into a map of gcosts for that pivot
				pivots[s.pivot_num].costs[s.c.y][s.c.x] = s.gcost;
				s.fcost = s.gcost;
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
				e.UndoAction(s.c, a);
			}
		}
		if (queue.empty())
		{
			return s.c;
		}
	}

	
}

template<typename state, typename action, typename environment, typename pivotinfo>
void Dijkstra<state, action, environment, pivotinfo>::addOpen(NodeD<state> &s)
{
	//create tuple type for queue
	tupler tup(s.fcost, s.rank);
	//insert tuple into queue
	queue.push(tup);
	//insert rank and node into hashmap
	open[s.rank] = s;
}

template<typename state, typename action, typename environment, typename pivotinfo>
void Dijkstra<state, action, environment, pivotinfo>::addClosed(NodeD<state> &s)
{
	//insert rank and node into hashmap
	closed.insert(std::pair<uint64_t, NodeD<state>>(s.rank, s));

}

template<typename state, typename action, typename environment, typename pivotinfo>
bool Dijkstra<state, action, environment, pivotinfo>::onOpen(NodeD<state> &s)
{
	return s.c == open[s.rank].c;
}

template<typename state, typename action, typename environment,typename pivotinfo>
bool Dijkstra<state, action, environment, pivotinfo>::onClosed(NodeD<state> &s)
{
	return s.c == closed[s.rank].c;
}

template<typename state, typename action, typename environment, typename pivotinfo>
NodeD<state> Dijkstra<state, action, environment, pivotinfo>::removeBest()
{
	//get top element, pop
	tupler tup = queue.top();
	queue.pop();
	//get element at that rank and remove from map
	NodeD<state> s = open[tup.rank];
	open.erase(tup.rank);
	//add to closed map
	addClosed(s);
	return s;
}

template<typename state, typename action, typename environment, typename pivotinfo>
void Dijkstra<state, action, environment, pivotinfo>::updateCost(NodeD<state> &s)
{
	//When we assign things to the hashmap, it will overwrite the object there, so thats the update for the hashmaps
	if (onOpen(s) && open[s.rank].fcost > s.fcost)
		open[s.rank] = s;
}
