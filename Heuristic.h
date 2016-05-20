#include <cstdlib>
#include "Dijkstra_label.h"
#include "Dijkstra_Find.h"
#include <vector>
#include <time.h>

struct Heuristic
{
	std::vector<pivot_info> pivot_list;

	Heuristic(int pivots, OctileGrid grid)
	{
		//there are two lists so I didnt have to make 2 different Dijkstra classes
		//the first to label states with gcosts from a single pivot
		//the second to store all pivots and use to find farthest pivot from all other combined pivots
		bool valid = false;
		srand(time(nullptr));
		
		//randomly pick a valid grid location for first pivot
		while (!valid)	
		{
			int x = rand() % 194;
			int y = rand() % 194;
			if (grid.map[x][y] == '.')
			{
				valid = true;
				pivot_info temp;
				temp.pivot.x = x;
				temp.pivot.y = y;
				pivot_list.push_back(temp);
			}
		}
		
		OctileGrid grid1(194, 194);
		
		

		//start with 1 pivot
		//use dijkstras
		for (int i = 0; i < pivots; i++)
		{
			//generate costs for first pivot
			Dijkstra_label<Coordinate, Action, OctileGrid> search1;
			search1.getPath(grid1, pivot_list[i]);

			pivot_info tempPivot;
			Dijkstra_find<Coordinate, Action, OctileGrid> search2;
			tempPivot.pivot = search2.getPath(grid1, pivot_list);
			pivot_list.push_back(tempPivot);
		}

		//do a dijkstra search from the pivot until you have searched the whole map
		//for each node expanded in the dijkstra, record the g costs of that node 
		//from the pivot in a 2D array of the map for that pivot
		//so each pivot will have its own 2D array of costs to each grid space on the map from that pivot
		//choose the node that is the farthest away from all existing pivots to be next pivot
		//by putting all pivots on open list at the beginning
		//of the dijstrak search so its the farthest from the combined pivots
		//rinse and repeat for desired number of pivots
	}

	int diffMax(Coordinate &start, Coordinate &goal)
	{
		std::vector<int> diffs;
		int dsp;
		int dpg;
		for (int i = 0; i < pivot_list.size(); i++)
		{
			dsp = pivot_list[i].costs[start.y][start.x];
			dpg = pivot_list[i].costs[goal.y][goal.x];
			diffs.push_back(abs(dsp - dpg));
		}
		OctileDistance od;
		int odcost = od.hcost(start, goal);
		diffs.push_back(odcost);
		int max = 0;
		for (int i = 0; i < diffs.size(); i++)
		{
			if (diffs[i] > max)
			{
				max = diffs[i];
			}
		}
		return max;
		return 0;
	}

	int hcost(Coordinate &start, Coordinate &goal)
	{
		return diffMax(start, goal);
	}
};