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
	int locs[16] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
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
				locs[pattern[i]] = j;
			}
		}	
	}
	uint64_t rankVal = 0;
	int numEntriesLeft = 16;
	// compute the lexographical ranking of the locations
	// of the first 16 tiles
	for (int x = 0; x < 16; x++)
	{
		if (locs[x] != -1)
		{
			rankVal += locs[x] * (Factorial(numEntriesLeft - 1) / Factorial(16 - pattern.size()));
			numEntriesLeft--;
		}
		// decrement locations of remaining items
		// to keep the numbering compact
		if (locs[x] != -1)
		{
			for (int y = x; y < 16; y++)
			{
				if (locs[y] > locs[x])
					locs[y]--;
			}
		}
	}
	return rankVal;
}

uint64_t SlidingTile::GetMaxRank(std::vector<int> pattern)
{
	return Factorial(16) / Factorial(16 - pattern.size());
}

void SlidingTile::Unrank(uint64_t rank, const std::vector<int> pattern)
{
	int count = 16;
	uint64_t unrankVal = rank;
	int dual[16] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	// unrank the locations of the first 16 tiles
	int pindex = pattern.size();
	int numEntriesLeft = 16 - pindex + 1;
	int base = 16;
	for (int x = 16 - 1; x >= 0; x--)
	{
		if (std::find(pattern.begin(), pattern.end(), x) != pattern.end())
		{
			dual[x] = unrankVal % numEntriesLeft;
			unrankVal /= numEntriesLeft;
			numEntriesLeft++;
			for (int y = x + 1; y < 16; y++)
			{
				if (dual[y] >= dual[x])
					dual[y]++;
			}
		}
	}
	//clear puzzle locations
	// revert locations of tiles into positions in the puzzle
	for (int x = 0; x < 16; x++)
	{
		tiles[x] = -1;
		tiles[x] = dual[x];
	}
	// reset the cache of the blanks location
	blank = dual[0];
}

void SlidingTile::Print()
{
	for (int i = 0, j = 0; i < 16; ++i, j++)
	{
		std::cout << tiles[i] << "\t";
		if (j == 3){ std::cout << std::endl; j = -1; }
	}
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
