#include "Dijkstra_label.h"
#include <cstdlib>
#include <time.h>
#include <cmath>

struct Random_Heuristic
{
	std::vector<pivot_info> second_pivot_list;
	
	Random_Heuristic(int pivots, OctileGrid grid)
	{
		srand(time(nullptr));
		//create 10 random pivots
        while (second_pivot_list.size() < pivots)
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
		//run a dijkstras on those pivots to record costs to each grid space from pivot
		for (int i = 0; i < 10; i++)
		{
			Dijkstra_label<Coordinate, Action, OctileGrid> labelSearch;
			labelSearch.getPath(grid, second_pivot_list[i]);
		}
	}

	int diffMax(Coordinate &start, Coordinate &goal)
	{
		std::vector<int> diffs;
		int dsp;
		int dpg;
		//find each differential heuristic
		for (int i = 0; i < second_pivot_list.size(); i++)
		{

			dsp = second_pivot_list[i].costs[start.y][start.x];
			dpg = second_pivot_list[i].costs[goal.y][goal.x];
			//std::cout << dsp << std::endl;
			//std::cout << dpg << std::endl;
			diffs.push_back(abs(dsp - dpg));
		}
		OctileDistance od;
		int odcost = od.hcost(start, goal);
		diffs.push_back(odcost);
		//return the max of them
		//add octile distance
		int max = 0;
		for (int i = 0; i < diffs.size(); i++)
		{
			
			if (diffs[i] > max)
			{
				max = diffs[i];
			}
		}
		
		return max;
	}

	int hcost(Coordinate &start, Coordinate &goal)
	{
		return diffMax(start, goal);
	}
};