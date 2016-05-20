#include "Heuristic.h"
#include <cstdlib>

struct Random_Heuristic
{
	std::vector<pivot_info> second_pivot_list;
	
	Random_Heuristic(int pivots, char map[180][120])
	{
		srand(time_t(nullptr));
		bool valid = false;
		for (int i = 0; i < 10; i++)
		{
			valid = false;
			while (!valid)
			{
				int x = rand() % 120;
				int y = rand() % 180;
				if (map[x][y] == '.')
				{
					valid = true;
					pivot_info temp;
					temp.pivot.x = x;
					temp.pivot.y = y;
					second_pivot_list.push_back(temp);
				}
			}
		}
		OctileGrid grid1(120, 180);
		Dijkstra<Coordinate, Action, OctileGrid, pivot_info> search1;
		std::vector<pivot_info> temp;
		for (int i = 0; i < 10; i++)
		{
			temp.push_back(second_pivot_list[i]);
			search1.getPath(grid1, temp);
			second_pivot_list[i].costs = temp[0].costs;
			temp.pop_back();
		}

	}
};