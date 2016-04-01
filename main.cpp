#include <iostream>
#include <cstdint>
#include "Gameboard.h"
#include "BFS.h"
#include "NaryTree.h"
#include "DFS.h"

int main(int argc, char* argv[]) {
	//BFS GAMEBOARD
	Gameboard grid;
	BFS<grid::State, grid::Action, Gameboard> searchGrid;
	grid::State start;
	start.agentLoc = 15;
	grid::State goal;
	goal.agentLoc = 20;
	if (searchGrid.GetPath(grid, start, goal))
	{
		std::cout << "GameBoard BFS:" << searchGrid.GetNodesExpanded() << std::endl;
	}
	//BFS NARYTREE
	NaryTree tree;
	tree.branchingFactor = 2;
	BFS<Tree::State, Tree::Action, NaryTree> searchTree;
	Tree::State startTree;
	startTree.nodeID = 0;
	Tree::State goalTree;
	goalTree.nodeID = 20;
	if (searchTree.GetPath(tree, startTree, goalTree))
	{
		std::cout << "NaryTree BFS: " << searchTree.GetNodesExpanded() << std::endl;
	}
	//DFS NARYTREE
	NaryTree treeDFS;
	treeDFS.branchingFactor = 2;
	DFS<Tree::State, Tree::Action, NaryTree> searchTreeDFS;
	Tree::State startTreeDFS;
	startTreeDFS.nodeID = 0;
	Tree::State goalTreeDFS;
	goalTreeDFS.nodeID = 20;
	if (searchTreeDFS.GetPath(treeDFS, startTreeDFS, goalTreeDFS))
	{
		std::cout << "NaryTree DFS: " << searchTreeDFS.GetNodesExpanded() << std::endl;
	}
	

	std::getchar();
	return 0;
}