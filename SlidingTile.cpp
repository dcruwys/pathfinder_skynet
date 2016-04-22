#include "SlidingTile.h"
#include <vector>
#include <algorithm>

uint64_t Factorial(int temp)
{
	uint64_t table[17] =
	{ 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200, 1307674368000, 20922789888000};
	return table[temp];
}

uint64_t FactorialDivide(int f1, int f2)
{
	if (f1 = f2) return 1;
	if (f1 > f2)
	{
		int temp = f1 - f2;
		int result = 1;
		for (; temp = 0; temp--)
		{
			result *= f1 - temp;
		}
		return result;
	}
}

SlidingTile::SlidingTile()
{
	for (int x = 0; x < 16; x++)
	{
		tiles[x] = x;
	}
	blank = 0;
	width = 4;
}

SlidingTile::SlidingTile(const int temp[16])
{
	for (int x = 0; x < 16; x++)
	{
		if (temp[x] == 0)
		{
			blank = x;
		}
		tiles[x] = temp[x];
	}
}

uint64_t SlidingTile::Rank(const std::vector<int> pattern)
{
	std::vector<int> dual;
	// create dual array with locations of tiles
	// that are not blanked out
	for (int i = 0; i < pattern.size(); i++)
	{
		for (int j = 0; j < 16; j++)
		{
			// for each tile in our pattern
			// set the ith value in our dual array
			// to the location of the pattern value
			// in our sliding tile
			if (tiles[j] == pattern[i])
			{
				dual.push_back(j);
			}
		}	
	}
	uint64_t rankVal = 0;
	int numEntriesLeft = 16;
	for (int x = 0; x < dual.size(); x++)
	{
		for (int i = x+1; i < dual.size(); i++)
		{
			if (dual[x] < dual[i])
			{
				dual[i]--;
			}
		}
	}
	for (int x = 0; x < dual.size(); x++)
	{
		rankVal += dual[x] * (Factorial(numEntriesLeft - 1) / Factorial(16 - pattern.size()));
		numEntriesLeft--;
	}
	return rankVal;
}

uint64_t SlidingTile::GetMaxRank(std::vector<int> pattern)
{
	return Factorial(16) / Factorial(16 - pattern.size());
}

void SlidingTile::Unrank(uint64_t rank, const std::vector<int> pattern)
{
	uint64_t unrankVal = rank;
	std::vector<int> dual;
	dual.resize(pattern.size());
	int numEntriesLeft = 16 - 1;
	for (int i = 0; i < pattern.size(); i++)
	{ 
			dual[i] = unrankVal / (Factorial(numEntriesLeft) / Factorial(16 - pattern.size()));
			unrankVal -= (dual[i] * (Factorial(numEntriesLeft) / Factorial(16 - pattern.size())));
			numEntriesLeft--;
	}
	for (int x = pattern.size() - 1; x >= 0; x--)
	{
		for (int y = x - 1; y >= 0; y--)
		{
			if (dual[y] <= dual[x])
			{
				dual[x]++;
			}
		}
	}
	int pindex = 0;
	for (int x = 0; x < 16; x++)
	{
        tiles[x] = -1;
		for(int y = 0; y < pattern.size(); y++)
        {
            if(dual[y] == x)
            {
                tiles[x] = pattern[y];
            }
        }
	}
	blank = dual[0];
}

char* SlidingTile::Print()
{
	std::string output;
	for (int i = 0, j = 0; i < 16; ++i, j++)
	{
		output = tiles[i] + " ";
	}
	int temp = output.size();
	char outputs[100];
	for (int i = 0; i <= temp; i++)
	{
		outputs[i] = output[i];
	}
	return outputs;
}

void SlidingTile::GetActions(std::list<Action> &actions)
{
	//clear list of actions before adding to it
	actions.clear();
	//push possible actions onto list of actions
	if (blank % width != 0)
	{
		actions.emplace_front(Action(direction::LEFT));
	}
	if (blank % width != width - 1)
	{
		actions.emplace_front(Action(direction::RIGHT));
	}
	if (blank < width * width - width)
	{
		actions.emplace_front(Action(direction::DOWN));
	}
	if (blank > width - 1)
	{
		actions.emplace_front(Action(direction::UP));
	}
}

void SlidingTile::ApplyAction(Action a)
{
	switch (a.myDirection)
	{
	case direction::LEFT: 
		tiles[blank] = tiles[blank - 1];
		blank -= 1;
		tiles[blank] = 0;
		break;
	case direction::RIGHT: 
		tiles[blank] = tiles[blank + 1];
		blank += 1;
		tiles[blank] = 0;
		break;
	case direction::DOWN:
		tiles[blank] = tiles[blank + width];
		blank += width;
		tiles[blank] = 0;
		break;
	case direction::UP: 
		tiles[blank] = tiles[blank - width];
		blank -= width;
		tiles[blank] = 0;
		break;
	default: std::cout << "Sliding Tile ApplyAction() not working correctly"; break;
	}
}

void SlidingTile::UndoAction(Action a)
{
	switch (a.myDirection)
	{
	case direction::RIGHT:
		tiles[blank] = tiles[blank - 1];
		blank -= 1;
		tiles[blank] = 0;
		break;
	case direction::LEFT:
		tiles[blank] = tiles[blank + 1];
		blank += 1;
		tiles[blank] = 0;
		break;
	case direction::UP:
		tiles[blank] = tiles[blank + width];
		blank += width;
		tiles[blank] = 0;
		break;
	case direction::DOWN:
		tiles[blank] = tiles[blank - width];
		blank -= width;
		tiles[blank] = 0;
		break;
	default: std::cout << "Sliding Tile ApplyAction() not working correctly"; break;
	}
}
