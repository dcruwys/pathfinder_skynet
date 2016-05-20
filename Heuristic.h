#include <cstdlib>
#include "OctileGrid.h"
#include "Dijkstra.h"
#include <vector>

struct pivot_info
{
	Coordinate pivot;
	std::vector<std::vector<int>> costs;
};

struct Heuristic
{
	std::vector<pivot_info> second_pivot_list;

	Heuristic(int pivots, char map[180][120])
	{
		//there are two lists so I didnt have to make 2 different Dijkstra classes
		//the first to label states with gcosts from a single pivot
		//the second to store all pivots and use to find farthest pivot from all other combined pivots
		std::vector<pivot_info> first_pivot_list;
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
				pivot_info temp;
				temp.pivot.x = x;
				temp.pivot.y = y;
				first_pivot_list.push_back(temp);
				second_pivot_list.push_back(temp);
			}
		}
		
		OctileGrid grid1(120, 180);
		Dijkstra<Coordinate, Action, OctileGrid, pivot_info> search1;
		

		//start with 1 pivot
		//use dijkstras
		//last pivot will not have correct costs, so generate 1 more pivot than you want
		//and dont use the last pivot
		for (int i = 0; i < 10; i++)
		{
			//puts costs into costs map
			search1.getPath(grid1, first_pivot_list);

			pivot_info temp;
			temp.pivot = search1.getPath(grid1, second_pivot_list);
			second_pivot_list.push_back(temp);
			second_pivot_list[i].costs = first_pivot_list[0].costs;
			
			first_pivot_list.pop_back();
			first_pivot_list.push_back(temp);
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