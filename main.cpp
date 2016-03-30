#include <iostream>
#include <cstdint>
#include "Gameboard.h"
#include "BFS.h"

int main(int argc, char* argv[]) {
	
	Gameboard grid;
	BFS<State, Action, Gameboard> search;
	State start;
	start.agentLoc = 0;
	State goal;
	goal.agentLoc = 5;
	if (search.GetPath(grid, start, goal))
	{
		std::cout << search.GetNodesExpanded() << std::endl;
	}

	std::getchar();
	return 0;
}