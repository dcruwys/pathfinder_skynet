#include <cstdlib>
#include "OctileGrid.h"
#include "Dijkstra.h"
#include <vector>

struct Heuristic
{
	Heuristic(int pivots, int map[][])
	{
		std::vector<Coordinate> pivot_list;
		bool valid = false;
		srand(time_t(nullptr));
		
		//randomly pick a valid grid location for first pivot
		while (!valid)
		{
			int x = rand() % 120;
			int y = rand() % 180;
			if (map[x][y] == '.')
			{
				valid = true;
				Coordinate pivot;
				pivot.x = x;
				pivot.y = y;
				pivot_list.push_back(pivot);
			}
		}
		
		OctileGrid grid1(120, 180);
		Dijkstra<Coordinate, Action, OctileGrid> search1;
		

		//do a dijkstra search from the pivot until you have searched the whole map
		//for each node expanded in the dijkstra, record the g costs of that node 
		//from the pivot in a 2D array of the map for that pivot
		//so each pivot will have its own 2D array of costs to each grid space on the map from that pivot
		//choose the node that is the farthest away from all existing pivots to be next pivot
		//by putting all pivots on open list at the beginning
		//of the dijstrak search so its the farthest from the combined pivots

		//rinse and repeat for desired number of pivots
	}

	//ints need to be states -- placeholders for now
	int calculate(int pivot, int goal)
	{
		//index into 2d array for that pivot and return cost for the goal grid space 
	}

	int octile_h()
	{
		//calculate octile distance
		//copy from other code
	}

	int differential_h(int one, int two, int three)
	{
		//take max of all pivot heuristics and octile distance
	}
};