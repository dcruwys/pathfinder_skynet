#pragma once
#include <queue>
#include <vector>
#include "SlidingTile.h"
#include <list>
#include <fstream>
#include <iostream>

class BFS 
{
public:
	void BFS_pdb(std::vector<int> pattern, std::string filename);
};

//BFS to create a pattern database for a given pattern
void BFS::BFS_pdb(std::vector<int> pattern, std::string filename)
{
	//create file
	std::ofstream outfile;
	outfile.open(filename);
	//make a state to start search from
	//constructor initializes to goal
	SlidingTile state;
	//keep list of legal moves the blank can make
	std::list<Action> moves;
	//keep array big enough to hold every rank
	uint8_t *stateDepths = new uint8_t[state.GetMaxRank(pattern)];
	//set all values in search array to 255
	memset(stateDepths, 255, state.GetMaxRank(pattern));
	//put the goal in the search array and set the depth of its rank to zero
	stateDepths[state.Rank(pattern)] = 0;
	//initialize seenstates to 1 because starting at goal
	uint64_t seenStates = 1;
	//set current depth to zero
	int currDepth = 0;
	//loop while we have not seen every possible state
	while (seenStates != state.GetMaxRank(pattern))
	{
		//loop through array to look for nodes of current depth
		for (int x = 0; x < state.GetMaxRank(pattern); x++)
		{
			//see if node x is equal to current depth
			//any node of current depth needs to be expanded
			//any node of 255 needs to be ignored and expanded later
			if (stateDepths[x] == currDepth)
			{
				//get state of a particular pattern from rank x
				state.Unrank(x, pattern);
				outfile << currDepth << " ";
				//generate the children of this state
				state.GetActions(moves);
				//apply and then undo each possible action from that state
				while (moves.empty() == false)
				{
					//apply first move
					state.ApplyAction(moves.front());
					//rank this child state
					uint64_t rank = state.Rank(pattern);
					//undo action to get back to original state
					state.UndoAction(moves.front());
					//remove the action that resulted in the child that we ranked
					moves.pop_front();
					//if the search array value (depth) at the child's rank was 255
					//set it to the depth of its parent + 1
					if (stateDepths[rank] == 255)
					{
						stateDepths[rank] = currDepth + 1;
						//increment seen states because we just
						//found a NEW child and assigned it a depth
						seenStates++;
					}
				}
			}
		}
		//increment current depth
		currDepth++;
		std::cout << "depth: " << currDepth << "   Seen States: " << seenStates << "\n";
	}
	outfile.close();
}