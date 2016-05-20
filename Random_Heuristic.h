#include "Dijkstra.h"
#include <cstdlib>
#include <time.h>

struct Random_Heuristic
{
	std::vector<pivot_info> second_pivot_list;
	
	Random_Heuristic(int pivots, OctileGrid grid)
	{
		srand(time(nullptr));
        while (second_pivot_list.size() < 10)
        {
            int x = 1 + (int) (120.0 * (rand() / (RAND_MAX + 1.0))) - 1;
            int y = 1 + (int) (180.0 * (rand() / (RAND_MAX + 1.0))) - 1;
            if (grid.map[y][x] == '.')
            {
                bool valid = true;
                pivot_info temp;
                temp.pivot.x = x;
                temp.pivot.y = y;
                if(second_pivot_list.empty())
                    second_pivot_list.push_back(temp);

                for(auto &i: second_pivot_list){
                    if(i.pivot.x == temp.pivot.x && i.pivot.y == temp.pivot.y)
                        valid = false;
                }
                if(valid){
                    second_pivot_list.push_back(temp);
                }
            }
		}

		Dijkstra<Coordinate, Action, OctileGrid, pivot_info> search1;
		std::vector<pivot_info> temp;
		for (int i = 0; i < 10; i++)
		{
			temp.push_back(second_pivot_list[i]);
			search1.getPath(grid, temp);
			second_pivot_list[i].costs = temp[0].costs;
			temp.pop_back();
		}

	}
};