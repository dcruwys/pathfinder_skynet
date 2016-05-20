#include <iostream>
#include "OctileGrid.h"
#include "Random_Heuristic.h"
#include "Heuristic.h"
#include "InefficientAstar.h"
#include "EfficientAstar.h"
#include "Timer.h"

int main(int argc, char* argv[]) {
    std::cout << "Testing on lak303d.map" << std::endl;
    std::cout << std::endl;
    std::cout << "Octile Distance: " << std::endl;
	int startX = 77;
	int startY = 43;
	int goalX = 115;
	int goalY = 119;
	OctileGrid grid2(194, 194);
	OctileDistance h;
    Timer t;
	//for(auto &i: rh.second_pivot_list){
	//	std::cout << i.pivot.x << " " << i.pivot.y << std::endl;
	//}
    t.StartTimer();
	Coordinate start2;
	start2.x = startX;
	start2.y = startY;
	Coordinate goal2;
	goal2.x = goalX;
	goal2.y = goalY;
	InefficientAstar<Coordinate, Action, OctileGrid, OctileDistance> Astar;
	if (Astar.getPath(grid2, start2, goal2, h))
	{
        t.EndTimer();
		std::cout << "Found goal.  Success!" << std::endl;
        std::cout << "Time elapsed: " << t.GetElapsedTime() << std::endl;
	}
    std::cout << std::endl;
    std::cout << "Random Heuristic: " << std::endl;
    t.StartTimer();
	OctileGrid grid1(194, 194);
	Random_Heuristic rh1(10, grid1);
	//for(auto &i: rh.second_pivot_list){
	//	std::cout << i.pivot.x << " " << i.pivot.y << std::endl;
	//}
	Coordinate start1;
	start1.x = startX;
	start1.y = startY;
	Coordinate goal1;
	goal1.x = goalX;
	goal1.y = goalY;
	InefficientAstar<Coordinate, Action, OctileGrid, Random_Heuristic> RAstar1;
	if (RAstar1.getPath(grid1, start1, goal1, rh1))
	{
        t.EndTimer();
        std::cout << "Found goal.  Success!" << std::endl;
        std::cout << "Time elapsed: " << t.GetElapsedTime() << std::endl;;
	}
    std::cout << std::endl;
    std::cout << "Farthest Distance: " << std::endl;
    t.StartTimer();
	OctileGrid grid(194, 194);
	Heuristic rh(10, grid);
	Coordinate start;
	start.x = startX;
	start.y = startY;
	Coordinate goal;
	goal.x = goalX;
	goal.y = goalY;
	InefficientAstar<Coordinate, Action, OctileGrid, Heuristic> RAstar;
	if (RAstar.getPath(grid, start, goal, rh))
	{
        t.EndTimer();
        std::cout << "Found goal.  Success!" << std::endl;
        std::cout << "Time elapsed: " << t.GetElapsedTime() << std::endl;
	}

	//hold output open
	std::getchar();
	return 0;
}
