#pragma once
#include "SlidingTile.h"
#include <cmath>

class Heuristic
{
public:
	Heuristic(){};
	int manhattanDistanceSlidingTile(SlidingTile4x4::State &s)
	{
		//h = heuristic value to return for state s
		int h = 0;
		//loop through the sliding tile grid
		//using index, keep track of what tile value is supposed to be at a given i,j location
		for (int i = 0, j = 0, index = 0; i < s.rows; ++i)
		{
			for(j = 0; j < s.cols; ++j, ++index)
			{
				//if the value at board[i][j] is out of place, store it in a temp
				if (s.board[i][j] != index)
				{
					int temp_search = s.board[i][j];
					
					//loop through the grid again
					//using iindex, keep track of what tile value is supposed to be at a given ii,jj location
					for (int ii = 0, jj = 0, iindex = 0; ii < s.rows; ++ii)
					{
						for (jj = 0; jj < s.cols; ++jj, ++iindex)
						{
							//find where temp value is supposed to be positioned
							if (temp_search == iindex)
							{
								//absolute value of value location - goal location = manhattan distance
								//h is the sum of all the displaced tiles manahattan distances = manhattan distance for a state
								std::cout << temp_search << ":" << iindex << std::endl;
								std::cout << i << "y" << j << ":" <<  ii << "x" << jj << std::endl;
								std::cout << abs(i - ii) << " + " << abs(j - jj) << "+" << std::endl;
								h = h + abs(i - ii) + abs(j - jj);
							}
						}
					}
				}					
			}
		}
		return h;
	}
};