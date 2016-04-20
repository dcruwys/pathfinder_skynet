#include <iostream>
#include <cstdint>
#include "SlidingTile.h"

int main(int argc, char* argv[]) {
	////BFS GAMEBOARD
	////to change the size of the grid, edit the boardsize, rows, and cols member variables of the grid::state in Gameboard2.h
	//Gameboard grid;
	//BFS<Grid::State, Grid::Action, Gameboard> searchGrid;
	//Grid::State start;
	//start.agentLocX = 0;
	//start.agentLocY = 0;
	//Grid::State goal;
	//goal.agentLocX = 7;
	//goal.agentLocY = 7;
	//if (searchGrid.GetPath(grid, start, goal))
	//{
	//	std::cout << "GameBoard BFS:" << std::endl
	//		<< "\tGameboard Size = " << start.boardSize << " (" << start.rows << "," << start.cols << ")" << std::endl
	//		<< "\tGameboard Start Location = " << " (" << start.agentLocX << "," << start.agentLocY << ")" << std::endl
	//		<< "\tGameboard Goal Location = " << " (" << goal.agentLocX << "," << goal.agentLocY << ")" << std::endl
	//		<< "\tNodes Expanded to reach Goal = " << searchGrid.GetNodesExpanded() << std::endl;
	//}

	////DFS GAMEBOARD
	////to change the size of the grid, edit the boardsize, rows, and cols member variables of the grid::state in Gameboard2.h
	//Gameboard gridDFS;
	//DFS<Grid::State, Grid::Action, Gameboard> searchGridDFS;
	//Grid::State startDFS;
	//startDFS.agentLocX = 0;
	//startDFS.agentLocY = 0;
	//Grid::State goalDFS;
	//goalDFS.agentLocX = 7;
	//goalDFS.agentLocY = 7;
	//if (searchGridDFS.GetPath(gridDFS, startDFS, goalDFS))
	//{
	//	std::cout << "GameBoard DFS:" << std::endl
	//		<< "\tGameboard Size = " << startDFS.boardSize << " (" << startDFS.rows << "," << startDFS.cols << ")" << std::endl
	//		<< "\tGameboard Start Location = " << " (" << startDFS.agentLocX << "," << startDFS.agentLocY << ")" << std::endl
	//		<< "\tGameboard Goal Location = " << " (" << goalDFS.agentLocX << "," << goalDFS.agentLocY << ")" << std::endl
	//		<< "\tNodes Expanded to reach Goal = " << searchGridDFS.GetNodesExpanded() << std::endl;
	//}


	////bfs narytree
	//NaryTree tree;
	//tree.branchingFactor = 2;
	//BFS<Tree::State, Tree::Action, NaryTree> searchtree;
	//Tree::State starttree;
	//starttree.nodeID = 0;
	//Tree::State goaltree;
	//goaltree.nodeID = 5000;
	//if (searchtree.GetPath(tree, starttree, goaltree))
	//{
	//	std::cout << "nary-tree bfs:" << std::endl
	//		<< "\tbrandching factor = " << tree.branchingFactor << std::endl
	//		<< "\ttree start location = " << starttree.nodeID << std::endl
	//		<< "\ttree goal location = " << goaltree.nodeID << std::endl
	//		<< "\tnodes expanded to reach goal = " << searchtree.GetNodesExpanded() << std::endl;
	//}

	////dfs narytree
	//NaryTree treedfs;
	//treedfs.branchingFactor = 2;
	//DFS<Tree::State, Tree::Action, NaryTree> searchtreedfs;
	//Tree::State starttreedfs;
	//starttreedfs.nodeID = 0;
	//Tree::State goaltreedfs;
	//goaltreedfs.nodeID = 10000;
	//if (searchtreedfs.GetPath(treedfs, starttreedfs, goaltreedfs))
	//{
	//	std::cout << "nary-tree dfs:" << std::endl
	//		<< "\tbrandching factor = " << treedfs.branchingFactor << std::endl
	//		<< "\ttree start location = " << starttreedfs.nodeID << std::endl
	//		<< "\ttree goal location = " << goaltreedfs.nodeID << std::endl
	//		<< "\tnodes expanded to reach goal = " << searchtreedfs.GetNodesExpanded() << std::endl;
	//}

	////IDA* NaryTree
	//IDA<Tree::State, Tree::Action, NaryTree> searchIDA;
	//NaryTree treeIDA;
	//treeIDA.branchingFactor = 2;
	//Tree::State startIDA;
	//Tree::State goalIDA;
	//startIDA.nodeID = 0;
	//goalIDA.nodeID = 10;
	//if(searchIDA.GetPath(treeIDA, startIDA, goalIDA))
	//{
	//	std::cout << "nary-tree ida:" << std::endl
	//	<< "\tbranching factor = " << treeIDA.branchingFactor << std::endl
	//	<< "\ttree start location = " << starttreedfs.nodeID << std::endl
	//	<< "\ttree goal location = " << goaltreedfs.nodeID << std::endl
	//	<< "\tnodes expanded to reach goal = " << searchtreedfs.GetNodesExpanded() << std::endl;

	//}

	std::vector<int> pattern = {0,1,4,5};
	SlidingTile puzzle16;
	uint64_t rank = puzzle16.Rank(pattern);
	std::cout << "MRank = " << puzzle16.GetMaxRank(pattern) << std::endl;
	std::cout << "Rank  = " << rank << std::endl;

	std::cout << "State: " << std::endl;
	puzzle16.Unrank(rank);
	puzzle16.Print();

	


	//hold output open
	std::getchar();
	return 0;
}