#include <iostream>
#include <cstdint>
#include "Gameboard.h"
#include "BFS.h"
#include "NaryTree.h"

int main(int argc, char* argv[]) {
	
	Gameboard grid;
	BFS<grid::State, grid::Action, Gameboard> searchGrid;
	grid::State start;
	start.agentLoc = 25;
	grid::State goal;
	goal.agentLoc = 20;
	if (searchGrid.GetPath(grid, start, goal))
	{
		std::cout << searchGrid.GetNodesExpanded() << std::endl;
	}

	NaryTree tree;
	BFS<Tree::State, Tree::Action, NaryTree> searchTree;
	Tree::State startTree;
	startTree.nodeID = 0;
	Tree::State goalTree;
	goalTree.nodeID = 8;
	if (searchTree.GetPath(tree, startTree, goalTree))
	{
		std::cout << searchTree.GetNodesExpanded() << std::endl;
	}
	

	

	std::getchar();
	return 0;
}