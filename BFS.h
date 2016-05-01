#pragma once
#include <queue>
#include <vector>
#include "STP.h"
#include <list>
#include <fstream>
#include <iostream>

class BFS 
{
public:
	void BFS_pdb(std::vector<int> pattern, const char *filename);
};

//BFS to create a pattern database for a given pattern
void BFS::BFS_pdb(std::vector<int> pattern, const char *filename)
{
	//create file
	FILE *pfile;
	pfile = fopen(filename, "wb");
	//make a state to start search from
	//constructor initializes to goal
	STP puzzle16;
	STPState s;
	//keep list of legal moves the blank can make
	std::vector<slideDir> moves;
	//keep array big enough to hold every rank
	uint8_t *stateDepths = new uint8_t[puzzle16.GetMaxRank(pattern)];
	//set all values in search array to 255
	memset(stateDepths, 255, puzzle16.GetMaxRank(pattern));
	//put the goal in the search array and set the depth of its rank to zero
	stateDepths[puzzle16.Rank(pattern, s)] = 0;
	//initialize seenstates to 1 because starting at goal
	uint32_t seenStates = 1;
	//set current depth to zero
	int currDepth = 0;
	//loop while we have not seen every possible state
	while (seenStates != puzzle16.GetMaxRank(pattern))
	{
		//loop through array to look for nodes of current depth
		for (int x = 0; x < puzzle16.GetMaxRank(pattern); x++)
		{
			//see if node x is equal to current depth
			//any node of current depth needs to be expanded
			//any node of 255 needs to be ignored and expanded later
			if (stateDepths[x] == currDepth)
			{
				//get state of a particular pattern from rank x
				s = puzzle16.Unrank(x, pattern);
				//outfile << currDepth << " ";
				//generate the children of this state
				puzzle16.GetActions(s, moves);
				//apply and then undo each possible action from that state
				while (moves.empty() == false)
				{
					//apply first move
					puzzle16.ApplyAction(s, moves.back());
					//rank this child state
					uint32_t rank = puzzle16.Rank(pattern, s);
					//undo action to get back to original state
					puzzle16.UndoAction(s, moves.back());
					//remove the action that resulted in the child that we ranked
					moves.pop_back();
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
		std::cout << "depth: " << currDepth << "   Seen States: " << seenStates << "\n";
		currDepth++;
	}
	fwrite(stateDepths, sizeof(uint8_t), puzzle16.GetMaxRank(pattern), pfile);
	fclose(pfile);
}