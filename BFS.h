#pragma once
#include <queue>
#include <vector>
#include "SlidingTile.h"
#include <list>

class BFS 
{
public:
	void BFS_pdb(std::vector<int> pattern);
};

void BFS::BFS_pdb(std::vector<int> pattern)
{
	SlidingTile state;
	std::list<Action> moves;
	uint8_t *stateDepths = new uint8_t[state.GetMaxRank(pattern)];

	memset(stateDepths, 255, state.GetMaxRank(pattern));
	uint64_t seenStates = 1;
	stateDepths[state.Rank(pattern)] = 0;
	int currDepth = 0;
	while (seenStates != state.GetMaxRank(pattern))
	{
		int news = 0;
		for (int x = 0; x < state.GetMaxRank(pattern); x++)
		{
			//std::cout << "stateDepths[x] " << stateDepths[x] << " currdepth " << currDepth << std::endl;
			if (stateDepths[x] == currDepth)
			{
				state.Unrank(x, pattern);
				state.GetActions(moves);
				while (moves.empty() == false)
				{
					state.ApplyAction(moves.front());
					uint64_t rank = state.Rank(pattern);
					state.UndoAction(moves.front());
					moves.pop_front();
					//std::cout << rank << "\t";
					if (stateDepths[rank] == 255)
					{
						stateDepths[rank] = currDepth + 1;
						//std::cout << rank << "\t";
						news++;
						seenStates++;
					}
				}
			}
		}
		currDepth++;
		std::cout << currDepth << ": " << seenStates << " news: " << news << "\n";
	}

}