#include <iostream>
#include "OctileGrid.h"
#include "Random_Heuristic.h"
#include "Heuristic.h"
#include "InefficientAstar.h"


int main(int argc, char* argv[]) {
	
	OctileGrid grid1(180, 120);
	Random_Heuristic rh1(10, grid1);
	//for(auto &i: rh.second_pivot_list){
	//	std::cout << i.pivot.x << " " << i.pivot.y << std::endl;
	//}
	Coordinate start1;
	start1.x = 58;
	start1.y = 130;
	Coordinate goal1;
	goal1.x = 65;
	goal1.y = 130;
	InefficientAstar<Coordinate, Action, OctileGrid, Random_Heuristic> RAstar1;
	if (RAstar1.getPath(grid1, start1, goal1, rh1))
	{
		std::cout << "Found goal.  Success??" << std::endl;
	}

	OctileGrid grid(180, 120);
	Heuristic rh(10, grid);
	//for(auto &i: rh.second_pivot_list){
	//	std::cout << i.pivot.x << " " << i.pivot.y << std::endl;
	//}
	Coordinate start;
	start.x = 58;
	start.y = 130;
	Coordinate goal;
	goal.x = 65;
	goal.y = 130;
	InefficientAstar<Coordinate, Action, OctileGrid, Heuristic> RAstar;
	if (RAstar.getPath(grid, start, goal, rh))
	{
		std::cout << "Found goal.  Success??" << std::endl;
	}

	//hold output open
	std::getchar();
	return 0;
}
