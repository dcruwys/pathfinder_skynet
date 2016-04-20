#include "SlidingTile.h"
#include <vector>
#include <algorithm>

uint64_t Factorial(int temp)
{
	uint64_t table[17] =
	{ 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200, 1307674368000, 20922789888000};
	return table[temp];
}

SlidingTile::SlidingTile()
{
	for (int x = 0; x < 16; x++)
	{
		tiles[x] = x;
	}
	blank = 0;
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
			rankVal += locs[x] * (Factorial(numEntriesLeft - 1) / Factorial(12));
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

uint64_t SlidingTile::GetMaxRank(std::vector<int> &pattern)
{
	return Factorial(16) / Factorial(15 - pattern.size());
}

void SlidingTile::Unrank(uint64_t rank)
{
	int count = 16;
	uint64_t hashVal = rank;
	int dual[16];

	// unrank the locations of the first 16 tiles
	int numEntriesLeft = 1;
	for (int x = 16 - 1; x >= 0; x--)
	{
		dual[x] = hashVal % numEntriesLeft;
		hashVal /= numEntriesLeft;
		numEntriesLeft++;
		for (int y = x + 1; y < 16; y++)
		{
			if (dual[y] >= dual[x])
				dual[y]++;
		}
	}
	for (int i = 0; i < 16; i++)
	{
		std::cout << dual[i] << std::endl;
	}
	// clear puzzle locations
	for (int x = 0; x < 16; x++)
	{
		tiles[x] = -1;
	}
	// revert locations of tiles into positions in the puzzle
	for (int x = 0; x < 16; x++)
	{
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

//void SlidingTile::GetActions(SlidingTile &board, std::vector<Action> &actions)
//{
//	//clear list of actions before adding to it
//	actions.clear();
//	
//	//push possible actions onto list of actions
//	if (board.blankTileX != 0)
//	{
//		actions.push_back(SlidingTile4x4::Action(SlidingTile4x4::direction::LEFT));
//	}
//	if (board.blankTileX != board.cols - 1)
//	{
//		actions.push_back(SlidingTile4x4::Action(SlidingTile4x4::direction::RIGHT));
//	}
//	if (board.blankTileY != 0)
//	{
//		actions.push_back(SlidingTile4x4::Action(SlidingTile4x4::direction::DOWN));
//	}
//	if (board.blankTileY != board.rows - 1)
//	{
//		actions.push_back(SlidingTile4x4::Action(SlidingTile4x4::direction::UP));
//	}
//}
//
//void SlidingTile::ApplyAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a)
//{
//	switch (a.myDirection)
//	{
//	case SlidingTile4x4::direction::LEFT: 
//		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX - 1, s.blankTileY);
//		s.blankTileX -= 1;
//		break;
//	case SlidingTile4x4::direction::RIGHT: 
//		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX + 1, s.blankTileY);
//		s.blankTileX += 1;
//		break;
//	case SlidingTile4x4::direction::DOWN: 
//		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX, s.blankTileY - 1);
//		s.blankTileY -= 1;
//		break;
//	case SlidingTile4x4::direction::UP: 
//		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX , s.blankTileY + 1);
//		s.blankTileY += 1;
//		break;
//	default: std::cout << "Sliding Tile ApplyAction() not working correctly"; break;
//	}
//}
//
//void SlidingTile::UndoAction(SlidingTile4x4::State &s, SlidingTile4x4::Action a)
//{
//	switch (a.myDirection)
//	{
//	case SlidingTile4x4::direction::RIGHT: 
//		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX - 1, s.blankTileY);
//		s.blankTileX -= 1;
//		break;
//	case SlidingTile4x4::direction::LEFT: 
//		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX + 1, s.blankTileY);
//		s.blankTileX += 1;
//		break;
//	case SlidingTile4x4::direction::UP: 
//		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX, s.blankTileY - 1);
//		s.blankTileY -= 1;
//		break;
//	case SlidingTile4x4::direction::DOWN: 
//		s.swapTiles(s.board, s.blankTileX, s.blankTileY, s.blankTileX, s.blankTileY + 1);
//		s.blankTileY += 1;
//		break;
//	default: std::cout << "Sliding Tile ApplyAction() not working correctly"; break;
//	}
